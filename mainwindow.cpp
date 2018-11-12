#include "mainwindow.h"
#include "midiportmodel.h"
#include "patchlistmodel.h"
#include "midievent.h"
#include "patcheditorwidget.h"
#include "progresswidget.h"
#include "patchcopydialog.h"
#include "preferencesdialog.h"

#include "magicstomp.h"

#include <QGroupBox>
#include <QListView>
#include <QTableView>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QLabel>
#include <QSpinBox>
#include <QPushButton>
#include <QDockWidget>
#include <QTimer>
#include <QMessageBox>
#include <QProgressDialog>
#include <QSettings>
#include <QDir>
#include <QStandardPaths>
#include <QItemSelectionModel>
#include <QTabWidget>
#include <QAction>
#include <QDebug>

static const int sysExBulkHeaderLength = 8;
static const unsigned char sysExBulkHeader[sysExBulkHeaderLength] = { 0xF0, 0x43, 0x7D, 0x30, 0x55, 0x42, 0x39, 0x39 };
static const unsigned char dumpRequestHeader[] = { 0xF0, 0x43, 0x7D, 0x50, 0x55, 0x42, 0x30, 0x01 };

static const int parameterSendHeaderLength = 6;
static const unsigned char sysExParameterSendHeader[parameterSendHeaderLength] = { 0xF0, 0x43, 0x7D, 0x40, 0x55, 0x42 };

MainWindow::MainWindow(MidiPortModel *readPortsMod, MidiPortModel *writePortsMod, QWidget *parent)
    : QMainWindow(parent), currentPatchTransmitted(-1), currentPatchEdited(QPair<PatchListType,int>(User,-1)),
      readablePortsModel(readPortsMod), writablePortsModel(writePortsMod),
      cancelOperation(false), isInTransmissionState(false)
{
    newPatchDataList.append(QList<QByteArray>());
    for(int i=0; i<numOfPatches; i++)
    {
        newPatchDataList[0].append( QByteArray());
        tmpPatchDataList.append( QByteArray());
    }

    for(int i=0; i<=(AcousticPreset+1); i++)
    {
        backupPatchesMapList.append(QMap<int, QPair<QByteArray, bool>>());
    }

    tmpPatchListModel = new PatchListModel( tmpPatchDataList, backupPatchesMapList.last(), this);

    newPatchDataList.append(QList<QByteArray>());
    loadPresetPatches( GuitarPreset, QStringLiteral("guitarpresets.ini"));
    newPatchDataList.append(QList<QByteArray>());
    loadPresetPatches( BassPreset, QStringLiteral("basspresets.ini"));
    newPatchDataList.append(QList<QByteArray>());
    loadPresetPatches( AcousticPreset, QStringLiteral("acousticpresets.ini"));

    patchListModelList.append(new PatchListModel( newPatchDataList.at(User), backupPatchesMapList.at(User), this));
    patchListModelList.append(new PatchListModel( newPatchDataList.at(GuitarPreset), backupPatchesMapList.at(GuitarPreset), this));
    patchListModelList.append(new PatchListModel( newPatchDataList.at(BassPreset), backupPatchesMapList.at(BassPreset), this));
    patchListModelList.append(new PatchListModel( newPatchDataList.at(AcousticPreset), backupPatchesMapList.at(AcousticPreset), this));

    timeOutTimer = new QTimer(this);
    timeOutTimer->setInterval(1000);
    timeOutTimer->setSingleShot(true);
    connect(timeOutTimer, SIGNAL(timeout()), this, SLOT(timeout()));

    midiOutTimer = new QTimer(this);
    midiOutTimer->setInterval(70);
    connect(midiOutTimer, SIGNAL(timeout()), this, SLOT(midiOutTimeOut()));

    showPreferencesAction = new QAction(tr("&Preferences"), this);
    //showPreferencesAction->setShortcuts(QKeySequence::);
    //showPreferencesAction->setStatusTip(tr("Create a new file"));
    connect(showPreferencesAction, &QAction::triggered, this, &MainWindow::showPreferences);

    QPushButton *preferencesButton = new QPushButton( tr("Preferences"));
    connect( preferencesButton, SIGNAL(pressed()), showPreferencesAction, SLOT(trigger()));

    QGroupBox *patchListGroupbox = new QGroupBox( tr("Patch List"));

    requestButton = new QPushButton("Request All");
    connect(requestButton, SIGNAL(pressed()), this, SLOT(requestAll()));
    sendButton = new QPushButton("Send All");
    connect(sendButton, SIGNAL(pressed()), this, SLOT(sendAll()));

    QHBoxLayout *patchButtonsLayout = new QHBoxLayout();
    patchButtonsLayout->addWidget(requestButton);
    patchButtonsLayout->addWidget(sendButton);

    patchListLayout = new QVBoxLayout();

    patchTabWidget = new QTabWidget();

    patchListView = new QTableView();
    patchListView->setSelectionBehavior(QAbstractItemView::SelectRows);
    patchListView->setModel(patchListModelList.at(User));
    connect(patchListView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(patchListDoubleClicked(QModelIndex)));
    connect(patchListView->selectionModel(), SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
            this, SLOT(patchListSelectionChanged()));
    patchTabWidget->addTab( patchListView, tr("User"));

    QTableView *guitarPatchListView = new QTableView();
    guitarPatchListView->setSelectionBehavior(QAbstractItemView::SelectRows);
    guitarPatchListView->setModel(patchListModelList.at(GuitarPreset));
    connect(guitarPatchListView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(patchListDoubleClicked(QModelIndex)));
    connect(guitarPatchListView->selectionModel(), SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
            this, SLOT(patchListSelectionChanged()));
    patchTabWidget->addTab( guitarPatchListView, tr("Guitar Presets"));

    QTableView *bassPatchListView = new QTableView();
    bassPatchListView->setSelectionBehavior(QAbstractItemView::SelectRows);
    bassPatchListView->setModel(patchListModelList.at(BassPreset));
    connect(bassPatchListView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(patchListDoubleClicked(QModelIndex)));
    connect(bassPatchListView->selectionModel(), SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
            this, SLOT(patchListSelectionChanged()));
    patchTabWidget->addTab( bassPatchListView, tr("Bass Presets"));

    QTableView *acousticPatchListView = new QTableView();
    acousticPatchListView->setSelectionBehavior(QAbstractItemView::SelectRows);
    acousticPatchListView->setModel(patchListModelList.at(AcousticPreset));
    connect(acousticPatchListView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(patchListDoubleClicked(QModelIndex)));
    connect(acousticPatchListView->selectionModel(), SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
            this, SLOT(patchListSelectionChanged()));
    patchTabWidget->addTab( acousticPatchListView, tr("Acoustic Presets"));
    patchListGroupbox->setLayout(patchListLayout);
    patchListLayout->addLayout(patchButtonsLayout);
    patchListLayout->addWidget(patchTabWidget);

    connect(patchTabWidget, SIGNAL(currentChanged(int)), this, SLOT(patchListSelectionChanged()));

    QHBoxLayout *listEditButtonsLayout = new QHBoxLayout();
    listEditButtonsLayout->addWidget(swapButton = new QPushButton(tr("Swap")));
    connect(swapButton, SIGNAL(pressed()), this, SLOT(swapButtonPressed()));
    swapButton->setEnabled(false);
    listEditButtonsLayout->addWidget(copyButton = new QPushButton(tr("Copy")));
    copyButton->setEnabled(false);
    connect(copyButton, SIGNAL(pressed()), this, SLOT(copyButtonPressed()));

    listEditButtonsLayout->addWidget(undoRedoButton = new QPushButton(tr("Undo")));
    undoRedoButton->setEnabled(false);
    connect(undoRedoButton, SIGNAL(pressed()), this, SLOT(undoRedoButtonPressed()));

    patchListLayout->addLayout( listEditButtonsLayout);

    QVBoxLayout *mainLeftlayout = new QVBoxLayout();
    mainLeftlayout->addWidget( preferencesButton);
    mainLeftlayout->addWidget( patchListGroupbox);

    QWidget *dockWidgetDummy = new QWidget();
    dockWidgetDummy->setMinimumSize(440, 600);
    dockWidgetDummy->setLayout(mainLeftlayout);

    QDockWidget *dockWidget = new QDockWidget();
    dockWidget->setFeatures( QDockWidget::DockWidgetMovable  | QDockWidget::DockWidgetFloatable);
    dockWidget->setObjectName( QStringLiteral("dockWidget"));
    dockWidget->setWidget(dockWidgetDummy);
    addDockWidget(Qt::LeftDockWidgetArea, dockWidget);
    resizeDocks({dockWidget}, {600}, Qt::Horizontal); // workaroud for dock widget resize bug

    PatchEditorWidget *editor = new PatchEditorWidget();
    connect(editor, SIGNAL(parameterAboutToBeChanged(int,int)), this, SLOT(parameterToBeChanged(int,int)));
    connect(editor, SIGNAL(parameterChanged(int,int)), this, SLOT(parameterChanged(int,int)));
    setCentralWidget(editor);

    QSettings cacheSettings(QStandardPaths::writableLocation(QStandardPaths::CacheLocation)+QStringLiteral("/patchcache.ini"), QSettings::IniFormat);
    for(int i=0; i<numOfPatches;i++)
    {
        QByteArray arr;
        arr = cacheSettings.value("Patchdata"+QString::number(i+1).rightJustified(2, '0')).toByteArray();
        if(arr.size() == PatchTotalLength && arr.at(PatchType+1)<EffectTypeNUMBER)
            newPatchDataList[User][i] = arr;
    }
    patchListView->resizeColumnsToContents();
    guitarPatchListView->resizeColumnsToContents();
    bassPatchListView->resizeColumnsToContents();
    acousticPatchListView->resizeColumnsToContents();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    QSettings cacheSettings(QStandardPaths::writableLocation(QStandardPaths::CacheLocation)+QStringLiteral("/patchcache.ini"), QSettings::IniFormat);
    for(int i=0; i<numOfPatches;i++)
    {
        if(newPatchDataList.at(User).at(i).size() == PatchTotalLength)
            cacheSettings.setValue("Patchdata"+QString::number(i+1).rightJustified(2, '0'), newPatchDataList.at(User).at(i));
    }
    QMainWindow::closeEvent(event);
}

void MainWindow::midiEvent(MidiEvent *ev)
{
    if( ev->type()==static_cast<QEvent::Type>(MidiEvent::SysEx))
    {
        const QByteArray *inData = ev->sysExData();
        if( inData->size() < 13)
            return;

        if( inData->left(sysExBulkHeaderLength) != QByteArray(reinterpret_cast<const char*>(&sysExBulkHeader[0]),sysExBulkHeaderLength) )
            return;

        ev->accept();

        if( static_cast<unsigned char>(inData->at( inData->length()-1)) != 0xF7)
            return;

        char checkSum = calcChecksum(inData->constData()+sysExBulkHeaderLength, inData->length()-sysExBulkHeaderLength-2);
        if( checkSum != inData->at( inData->length()-1-1))
        {
            qDebug("Checksum Error!");
            return;
        }

        //Dump message received
        if( inData->at(8)==0x00 && inData->at(9)==0x00)
        {
            //patch dump start message. Lenght(?)==0
            if( inData->at(10)==0x30 && inData->at(11)==0x01)
            {
                qDebug("Patch %d Dump Start Message", inData->at(12));
                currentPatchTransmitted = inData->at(12);
                if(currentPatchTransmitted == 0)
                {
                    for(int i=0; i< numOfPatches; i++)
                        tmpPatchDataList[i].clear();
                }
            }
            else if( inData->at(10)==0x30 && inData->at(11)==0x11)
            {
                //patch dump end message. Lenght(?)==0
                qDebug("Patch %d Dump End Message", inData->at(12));
                timeOutTimer->stop();
                patchListView->scrollTo(patchListView->model()->index(currentPatchTransmitted, 0));
                currentPatchTransmitted = -1;
                requestPatch(inData->at(12)+1);
            }
        }
        else if( inData->at(8)==0x00 &&  inData->at(9)!=0x00)
        {
            int length = inData->at(9);
            qDebug("Patch Dump Message. Length=%d", length);
            if(inData->at(10)==0x20)
            {
                if(inData->at(11)==0x00 && inData->at(12)==0x00)
                { // Patch common data;
                    if(currentPatchTransmitted >=0 && currentPatchTransmitted < numOfPatches && length == PatchCommonLength)
                    {
                        tmpPatchDataList[currentPatchTransmitted] = inData->mid(13, PatchCommonLength);
                        if( tmpPatchDataList[currentPatchTransmitted].size() != PatchCommonLength)
                        {
                            tmpPatchDataList[currentPatchTransmitted].clear();
                            return;
                        }
                    }
                }
                else if(inData->at(11)==0x01 && inData->at(12)==0x00)
                { // Patch effect data;
                    if(currentPatchTransmitted >=0 && currentPatchTransmitted < numOfPatches && length == PatchEffectLength)
                    {
                        tmpPatchDataList[currentPatchTransmitted].append( inData->mid(13, PatchEffectLength));
                        if( tmpPatchDataList[currentPatchTransmitted].size() != PatchTotalLength)
                        {
                            tmpPatchDataList[currentPatchTransmitted].clear();
                            return;
                        }
                        tmpPatchListModel->patchUpdated(currentPatchTransmitted);
                    }
                }
            }
        }
    }

}

void MainWindow::requestAll()
{
    for(int i=0; i< numOfPatches; i++)
        tmpPatchDataList[i].clear();

    patchListView->setModel( tmpPatchListModel);

    patchTabWidget->setCurrentIndex(0);
    putGuiToTransmissionState(true, false);

    currentPatchTransmitted = -1;
    requestPatch(0);
}

void MainWindow::requestPatch(int patchIndex)
{
    if(patchIndex >= numOfPatches || cancelOperation)
    {
        putGuiToTransmissionState(false, false);
        patchListView->scrollTo(patchListView->model()->index( 0, 0));
        if( ! cancelOperation)
        {
            newPatchDataList[User] = tmpPatchDataList;
            QMessageBox::information(this, tr("MagicstimpFrenzy"), tr("Data requested successfully"));
        }
        else
        {
            QMessageBox::information(this, tr("MagicstimpFrenzy"), tr("Oparation was cancelled. Press a button of your Magicstomp."));
        }
        patchListView->setModel( patchListModelList.at(User));
        patchListView->resizeColumnsToContents();
        cancelOperation = false;
        return;
    }
    progressWidget->setValue(patchIndex+1);

    MidiEvent *midiev = new MidiEvent(static_cast<QEvent::Type>(MidiEvent::SysEx));
    QByteArray *reqArr = midiev->sysExData();

    reqArr->append(QByteArray(reinterpret_cast<const char*>(&dumpRequestHeader[0]),std::extent<decltype(dumpRequestHeader)>::value));
    reqArr->append(char(patchIndex));
    reqArr->append(static_cast<char>(0xF7));
    emit sendMidiEvent( midiev);
    timeOutTimer->start();
}

void MainWindow::sendAll()
{
    const QList<QByteArray> &userList = newPatchDataList.at(User);
    for(int i=0; i<userList.size(); i++)
    {
        if(userList.at(i).size() != PatchTotalLength)
        {
            QMessageBox::warning(this, QStringLiteral("MagicstompFrenzy"), tr("Sending data to Magicstomp if User patch list is not complete is not possible."));
            return;
        }
    }

    putGuiToTransmissionState(true, true);

    MidiEvent *midiev = new MidiEvent(static_cast<QEvent::Type>(MidiEvent::SysEx));
    QByteArray *reqArr = midiev->sysExData();

    //Bulk out all start
    reqArr->append(QByteArray(reinterpret_cast<const char*>(&sysExBulkHeader[0]), sysExBulkHeaderLength));
    reqArr->append(static_cast<char>(0x00));
    reqArr->append(static_cast<char>(0x00));
    reqArr->append(static_cast<char>(0x30));
    reqArr->append(static_cast<char>(0x00));
    reqArr->append(char(0));
    reqArr->append( calcChecksum( reqArr->constBegin()+ sysExBulkHeaderLength, reqArr->length()-sysExBulkHeaderLength));
    reqArr->append(static_cast<char>(0xF7));
    midiOutQueue.enqueue( midiev);

    for(int i=0; i<numOfPatches; i++)
        sendPatch(i, false, User);

    //Bulk out all end
    midiev = new MidiEvent(static_cast<QEvent::Type>(MidiEvent::SysEx));
    reqArr = midiev->sysExData();
    reqArr->append(QByteArray(reinterpret_cast<const char*>(&sysExBulkHeader[0]), sysExBulkHeaderLength));
    reqArr->append(static_cast<char>(0x00));
    reqArr->append(static_cast<char>(0x00));
    reqArr->append(static_cast<char>(0x30));
    reqArr->append(static_cast<char>(0x10));
    reqArr->append(char(0));
    reqArr->append( calcChecksum( reqArr->constBegin()+ sysExBulkHeaderLength, reqArr->length()-sysExBulkHeaderLength));
    reqArr->append(static_cast<char>(0xF7));
    midiOutQueue.enqueue( midiev);
    midiOutTimer->start();
}

void MainWindow::sendPatch( int patchIdx, bool sendToTmpArea, PatchListType type )
{
    MidiEvent *midiev = new MidiEvent(static_cast<QEvent::Type>(MidiEvent::SysEx));
    QByteArray *reqArr = midiev->sysExData();
    reqArr->append(QByteArray(reinterpret_cast<const char*>(&sysExBulkHeader[0]), sysExBulkHeaderLength));
    reqArr->append(static_cast<char>(0x00));
    reqArr->append(static_cast<char>(0x00));
    reqArr->append(static_cast<char>(0x30));
    if( sendToTmpArea)
        reqArr->append(static_cast<char>(0x03));
    else
        reqArr->append(static_cast<char>(0x01));
    reqArr->append(char(patchIdx));
    reqArr->append( calcChecksum( reqArr->constBegin()+ sysExBulkHeaderLength, reqArr->length()-sysExBulkHeaderLength));
    reqArr->append(static_cast<char>(0xF7));
    midiOutQueue.enqueue( midiev);

    midiev = new MidiEvent(static_cast<QEvent::Type>(MidiEvent::SysEx));
    reqArr = midiev->sysExData();
    reqArr->append(QByteArray(reinterpret_cast<const char*>(&sysExBulkHeader[0]), sysExBulkHeaderLength));
    reqArr->append(static_cast<char>(0x00));
    reqArr->append(static_cast<char>(PatchCommonLength));
    reqArr->append(static_cast<char>(0x20));
    reqArr->append(static_cast<char>(0x00));
    reqArr->append(static_cast<char>(0x00));
    reqArr->append(newPatchDataList[type][patchIdx].left(PatchCommonLength));
    reqArr->append(calcChecksum( reqArr->constBegin()+ sysExBulkHeaderLength, reqArr->length()-sysExBulkHeaderLength));
    reqArr->append(static_cast<char>(0xF7));
    midiOutQueue.enqueue( midiev);
#if QT_VERSION >= 0x059000
    qDebug() << "send Patch Common :" << reqArr->toHex(',');
#endif
    midiev = new MidiEvent(static_cast<QEvent::Type>(MidiEvent::SysEx));
    reqArr = midiev->sysExData();
    reqArr->append(QByteArray(reinterpret_cast<const char*>(&sysExBulkHeader[0]), sysExBulkHeaderLength));
    reqArr->append(static_cast<char>(0x00));
    reqArr->append(static_cast<char>(PatchEffectLength));
    reqArr->append(static_cast<char>(0x20));
    reqArr->append(static_cast<char>(0x01));
    reqArr->append(static_cast<char>(0x00));
    reqArr->append(newPatchDataList[type][patchIdx].mid(PatchCommonLength, PatchEffectLength));
    reqArr->append(calcChecksum( reqArr->constBegin()+ sysExBulkHeaderLength, reqArr->length()-sysExBulkHeaderLength));
    reqArr->append(static_cast<char>(0xF7));
    midiOutQueue.enqueue( midiev);
#if QT_VERSION >= 0x059000
    qDebug() << "send Patch Effect :" << reqArr->toHex(',');
#endif
    midiev = new MidiEvent(static_cast<QEvent::Type>(MidiEvent::SysEx));
    reqArr = midiev->sysExData();
    reqArr->append(QByteArray(reinterpret_cast<const char*>(&sysExBulkHeader[0]), sysExBulkHeaderLength));
    reqArr->append(static_cast<char>(0x00));
    reqArr->append(static_cast<char>(0x00));
    reqArr->append(static_cast<char>(0x30));
    if( sendToTmpArea)
        reqArr->append(static_cast<char>(0x13));
    else
        reqArr->append(static_cast<char>(0x11));
    reqArr->append(char(patchIdx));
    reqArr->append( calcChecksum( reqArr->constBegin()+ sysExBulkHeaderLength, reqArr->length()-sysExBulkHeaderLength));
    reqArr->append(static_cast<char>(0xF7));
    midiOutQueue.enqueue( midiev);
    midiOutTimer->start();
}

void MainWindow::timeout()
{
    currentPatchTransmitted = -1;
    QMessageBox::warning(this, tr("MIDI communication error"), tr("No response from Magictomp. Check MIDI connection."), QMessageBox::Ok );
    if(isInTransmissionState)
        putGuiToTransmissionState(false, false);
    cancelOperation = false;
    patchListView->setModel( patchListModelList.at(User));
}

void MainWindow::midiOutTimeOut()
{
    if(cancelOperation)
    {
        while ( ! midiOutQueue.isEmpty())
        {
            MidiEvent *ev = midiOutQueue.dequeue();
            delete ev;
        }
        cancelOperation = false;
    }
    if( midiOutQueue.isEmpty())
    {
        midiOutTimer->stop();

        if(isInTransmissionState && !cancelOperation)
        {
            /*QSetIterator<int> iter(dirtyPatches);
            while (iter.hasNext())
                patchListModelList[User]->patchUpdated(iter.next());
            dirtyPatches.clear();*/
        }
        if(isInTransmissionState)
            putGuiToTransmissionState(false, false);
        return;
    }
    MidiEvent *ev = midiOutQueue.dequeue();
    emit sendMidiEvent( ev);
    if(isInTransmissionState)
        progressWidget->setValue( 100 - (midiOutQueue.size() / 4));
}

void MainWindow::parameterToBeChanged(int offset, int length)
{
    Q_UNUSED(offset)
    Q_UNUSED(length)

    if(! backupPatchesMapList.at(currentPatchEdited.first).contains(currentPatchEdited.second))
    {
        backupPatchesMapList[currentPatchEdited.first].insert(currentPatchEdited.second,
                  QPair<QByteArray, bool>(newPatchDataList[currentPatchEdited.first][currentPatchEdited.second], true));
    }
}

void MainWindow::parameterChanged(int offset, int length)
{
    qDebug("parameterChanged(offset=%d,len=%d)", offset, length);

    ArrayDataEditWidget *editWidget = static_cast<ArrayDataEditWidget *>(centralWidget());
    if(editWidget == nullptr)
        return;

    if( offset == PatchName) // Name needs to be sent as single chars
    {
        length = 1;
        patchListModelList[currentPatchEdited.first]->patchUpdated(currentPatchEdited.second);
    }

    MidiEvent *midiev = new MidiEvent(static_cast<QEvent::Type>(MidiEvent::SysEx));
    QByteArray *reqArr = midiev->sysExData();
    reqArr->append(QByteArray(reinterpret_cast<const char*>(&sysExParameterSendHeader[0]), parameterSendHeaderLength));
    reqArr->append(0x20);
    if(offset < PatchCommonLength)
    {
        reqArr->append(static_cast<char>(0x00));
        reqArr->append(static_cast<char>(offset));
    }
    else
    {
        reqArr->append(0x01);
        reqArr->append(static_cast<char>(offset - PatchCommonLength));
    }

    for(int i= 0; i< length; i++)
    {
        reqArr->append( *(editWidget->DataArray()->constData()+offset+i));
    }
    reqArr->append(static_cast<char>(0xF7));
#if QT_VERSION >= 0x059000
    qDebug() << reqArr->toHex(',');
#endif
    emit sendMidiEvent( midiev);

    if( offset == PatchName) // Name needs to be sent as single chars
    {
        for(int i= PatchName + 1; i < PatchNameLast; i++)
        {
            parameterChanged( i, 1);
        }
    }

    if( offset == PatchType)
    {
        QSettings effectiniSettings(QDir::currentPath()+"/effects.ini", QSettings::IniFormat);
        QByteArray initArr;
        int patchId = static_cast<EffectTypeId>( *(editWidget->DataArray()->constData()+PatchType+1));
        QString key = "Type" + (QString::number(patchId, 16).rightJustified(2, '0').toUpper());
        initArr = effectiniSettings.value( key).toByteArray();
        if(initArr.size() == PatchTotalLength && initArr.at(1) == patchId)
        {
            QByteArray &dataArrRef = newPatchDataList[currentPatchEdited.first][currentPatchEdited.second];

            QByteArray oldPatchName = dataArrRef.mid(PatchName, PatchNameLength);
            dataArrRef = initArr;
            dataArrRef.replace(PatchName, PatchNameLength, oldPatchName);
            editWidget->setDataArray(& (newPatchDataList[currentPatchEdited.first][currentPatchEdited.second]));
        }
        else
        {
            QMessageBox::critical(this, tr("Error"), tr("Error loading effect init data. Check if effects.ini is present and if is correct"));
        }
    }
    if(backupPatchesMapList.at(currentPatchEdited.first).value(currentPatchEdited.second).first ==
                newPatchDataList.at(currentPatchEdited.first).at(currentPatchEdited.second) )
    {
            backupPatchesMapList[currentPatchEdited.first].take(currentPatchEdited.second);
    }
    patchListModelList[currentPatchEdited.first]->patchUpdated(currentPatchEdited.second);

}

void MainWindow::putGuiToTransmissionState(bool isTransmitting, bool sending)
{
    if( isTransmitting)
    {
        requestButton->setEnabled(false);
        sendButton->setEnabled(false);
        patchTabWidget->setEnabled(false);
        centralWidget()->setEnabled( false);
        swapButton->setEnabled(false);
        copyButton->setEnabled(false);

        progressWidget = new ProgressWidget();
        connect(progressWidget, SIGNAL(cancel()), this, SLOT(cancelTransmission()));
        progressWidget->setRange(1, 99);
        if(sending)
            progressWidget->setFormat(tr("Sending... %p%"));
        else
            progressWidget->setFormat(tr("Requesting... %p%"));
        patchListLayout->addWidget( progressWidget );
    }
    else
    {
        ArrayDataEditWidget *editWidget = static_cast<ArrayDataEditWidget *>(centralWidget());
        if( editWidget->DataArray() != nullptr )
            editWidget->setEnabled( true);
        requestButton->setEnabled(true);
        sendButton->setEnabled(true);
        patchTabWidget->setEnabled(true);

        patchListSelectionChanged();

        patchListLayout->removeWidget( progressWidget );
        progressWidget->deleteLater();
    }
    isInTransmissionState = isTransmitting;
}

void MainWindow::cancelTransmission()
{
    cancelOperation = true;
}

void MainWindow::patchListDoubleClicked(const QModelIndex &idx)
{
    const PatchListModel *model = static_cast<const PatchListModel *>(idx.model());
    int i;
    for(i=0; i<patchListModelList.size(); i++)
    {
        if(patchListModelList.at(i)==model)
            break;
    }

    if(i >= patchListModelList.size())
        return;

    PatchListType type = static_cast<PatchListType>(i);

    if( newPatchDataList.at(type).at( idx.row()).isEmpty())
        return;

    sendPatch(idx.row(), true, type);
    midiOutTimer->start();
    ArrayDataEditWidget *widget = static_cast<ArrayDataEditWidget *>(centralWidget());
    widget->setDataArray(& newPatchDataList[type][idx.row()]);
    currentPatchEdited = QPair<PatchListType, int>(type, idx.row());
}

void MainWindow::patchListSelectionChanged()
{
    QTableView *tableview = static_cast<QTableView *>(patchTabWidget->currentWidget());
    PatchListType type = getCurrentPatchType();
    QModelIndexList indexes = tableview->selectionModel()->selectedRows(0);

    if(indexes.size() == 0 || indexes.size() > 2)
    {
        swapButton->setEnabled(false);
        copyButton->setEnabled(false);
        undoRedoButton->setEnabled(false);
        undoRedoButton->setText(tr("Undo"));
        return;
    }
    if( indexes.size() == 1)
    {
        copyButton->setEnabled(true);
        for(int x=0; x< backupPatchesMapList.size(); x++)
        {
            QMap<int, QPair<QByteArray, bool>>::const_iterator iter;
            iter = backupPatchesMapList.at(x).constFind(indexes.at(0).row());
            if(iter != backupPatchesMapList.at(x).constEnd() && x==type)
            {
                undoRedoButton->setEnabled(true);
                if(iter.value().second == true)
                    undoRedoButton->setText(tr("Undo"));
                else
                    undoRedoButton->setText(tr("Redo"));
                break;
            }
            else
            {
                undoRedoButton->setEnabled(false);
                undoRedoButton->setText(tr("Undo"));
            }
        }
        swapButton->setEnabled(false);
    }
    else if( indexes.size() == 2 && type==User)
    {
        swapButton->setEnabled(true);
        copyButton->setEnabled(false);
        undoRedoButton->setEnabled(false);
        undoRedoButton->setText(tr("Undo"));
    }
    else
    {
        swapButton->setEnabled(false);
        copyButton->setEnabled(false);
        undoRedoButton->setEnabled(false);
        undoRedoButton->setText(tr("Undo"));
    }
}

void MainWindow::swapButtonPressed()
{
    QModelIndexList selectedRows = patchListView->selectionModel()->selectedRows();
    if(selectedRows.size() != 2)
        return;

    int rowA = selectedRows.at(0).row();
    int rowB = selectedRows.at(1).row();

    QByteArray tmpArr = newPatchDataList.at(User).at(rowA);
    newPatchDataList[User][rowA] = newPatchDataList.at(User).at(rowB);
    newPatchDataList[User][rowB] = tmpArr;

    QMap<int, QPair<QByteArray, bool>>::iterator iterA;
    iterA = backupPatchesMapList[User].find(rowA);
    QMap<int, QPair<QByteArray, bool>>::iterator iterB;
    iterB = backupPatchesMapList[User].find(rowB);

    QPair<QByteArray, bool> tmpPair;
    if(iterA != backupPatchesMapList[User].end())
    {
        tmpPair = *iterA;
    }
    if(iterB != backupPatchesMapList[User].end())
    {
        backupPatchesMapList[User].insert(rowA, iterB.value());
        backupPatchesMapList[User].remove(rowB);
    }
    if(! tmpPair.first.isEmpty())
    {
        backupPatchesMapList[User].insert(rowB, tmpPair);
        if(iterB == backupPatchesMapList[User].end())
            backupPatchesMapList[User].remove(rowA);
    }

    if(QPair<PatchListType, int>( User, rowA) == currentPatchEdited)
    {
        currentPatchEdited =  QPair<PatchListType, int>( User, rowB);
        ArrayDataEditWidget *editWidget = static_cast<ArrayDataEditWidget *>(centralWidget());
        editWidget->setDataArray(& newPatchDataList[User][rowB]);
    }
    else if(QPair<PatchListType, int>( User, rowB)  == currentPatchEdited)
    {
        currentPatchEdited =  QPair<PatchListType, int>( User, rowA);
        ArrayDataEditWidget *editWidget = static_cast<ArrayDataEditWidget *>(centralWidget());
        editWidget->setDataArray(& newPatchDataList[User][rowA]);
    }
    patchListModelList[User]->patchUpdated(rowA);
    patchListModelList[User]->patchUpdated(rowB);
}

void MainWindow::copyButtonPressed()
{
    QTableView *tableview = static_cast<QTableView *>(patchTabWidget->currentWidget());
    PatchListType type = getCurrentPatchType();
    QModelIndexList indexes = tableview->selectionModel()->selectedRows(0);

    QString name = indexes.at(0).data().toString();

    PatchCopyDialog copydialog( patchListModelList[User], name, this);
    if( copydialog.exec() == QDialog::Accepted)
    {
        int targetRow = copydialog.targetPatchIndex();
        newPatchDataList[User][targetRow] = newPatchDataList.at(type).at(indexes.at(0).row());
        patchListModelList[User]->patchUpdated(targetRow);
        if(QPair<PatchListType, int>( User, targetRow) == currentPatchEdited)
        {
            ArrayDataEditWidget *editWidget = static_cast<ArrayDataEditWidget *>(centralWidget());
            editWidget->setDataArray(& (newPatchDataList[User][targetRow]));
            sendPatch(targetRow);
        }
        backupPatchesMapList[User].remove(targetRow);
    }
}

void MainWindow::undoRedoButtonPressed()
{
    QTableView *tableview = static_cast<QTableView *>(patchTabWidget->currentWidget());
    PatchListType type = getCurrentPatchType();
    QModelIndexList indexes = tableview->selectionModel()->selectedRows(0);
    int row = indexes.at(0).row();

    QByteArray tmpArray = newPatchDataList[type][row];
    QPair<QByteArray, bool> pairVal = backupPatchesMapList[type].value(row);
    pairVal.second = !pairVal.second;
    newPatchDataList[type][row] = pairVal.first;
    pairVal.first = tmpArray;
    backupPatchesMapList[type].insert(row, pairVal);

    ArrayDataEditWidget *editWidget = static_cast<ArrayDataEditWidget *>(centralWidget());
    editWidget->setDataArray(& (newPatchDataList[type][row]));
    sendPatch(row);

    patchListModelList[type]->patchUpdated(row);
    patchListSelectionChanged();
}

void MainWindow::loadPresetPatches(int index, const QString &filename)
{
    QString dir = QCoreApplication::applicationDirPath();
    QSettings cacheSettings(dir + "/"+ filename, QSettings::IniFormat);
    for(int i=0; i<numOfPatches;i++)
    {
        QByteArray arr;
        arr = cacheSettings.value("Patchdata"+QString::number(i+1).rightJustified(2, '0')).toByteArray();
        if(arr.size() == PatchTotalLength && arr.at(PatchType+1)<EffectTypeNUMBER)
            newPatchDataList[index].append(arr);
    }
}

MainWindow::PatchListType MainWindow::getCurrentPatchType() const
{
    QTableView *tableview = static_cast<QTableView *>(patchTabWidget->currentWidget());
    const PatchListModel *model = static_cast<const PatchListModel *>(tableview->model());

    int i;
    for(i=0; i<patchListModelList.size(); i++)
    {
        if(patchListModelList.at(i)==model)
            break;
    }

//    if(i >= patchListModelList.size())
//        return;

    return static_cast<PatchListType>(i);
}

void MainWindow::showPreferences()
{
    MidiApplication *thisMidiApp = static_cast<MidiApplication *>(qApp);

    PreferencesDialog prefDialog(readablePortsModel, writablePortsModel, this);
    connect( &prefDialog, SIGNAL(midiInPortStatusChanged( MidiClientPortId, bool)), thisMidiApp, SLOT(changeReadableMidiPortStatus(MidiClientPortId,bool)) );
    connect( &prefDialog, SIGNAL(midiOutPortStatusChanged( MidiClientPortId, bool)), thisMidiApp, SLOT(changeWritebleeMidiPortStatus(MidiClientPortId,bool)) );
    prefDialog.exec();

    prefDialog.disconnect(thisMidiApp);
}

char MainWindow::calcChecksum(const char *data, int dataLength)
{
    char checkSum = 0;
    for (int i = 0; i < dataLength; ++i)
    {
        checkSum += *data++;
    }
    return ((-checkSum) & 0x7f);
}
