#include "mainwindow.h"
#include "midiportmodel.h"
#include "patchlistmodel.h"
#include "midievent.h"
#include "patcheditorwidget.h"
#include "progresswidget.h"

#include "magicstomp.h"

#include <QGroupBox>
#include <QComboBox>
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
#include <QDebug>

static const int sysExBulkHeaderLength = 8;
static const unsigned char sysExBulkHeader[sysExBulkHeaderLength] = { 0xF0, 0x43, 0x7D, 0x30, 0x55, 0x42, 0x39, 0x39 };
static const unsigned char dumpRequestHeader[] = { 0xF0, 0x43, 0x7D, 0x50, 0x55, 0x42, 0x30, 0x01 };

static const int parameterSendHeaderLength = 6;
static const unsigned char sysExParameterSendHeader[parameterSendHeaderLength] = { 0xF0, 0x43, 0x7D, 0x40, 0x55, 0x42 };

MainWindow::MainWindow(MidiPortModel *readableportsmodel, MidiPortModel *writableportsmodel, QWidget *parent)
    : QMainWindow(parent), currentPatchTransmitted(-1), currentPatchEdited(-1),
      cancelOperation(false), isInTransmissionState(false)
{
    for(int i=0; i<numOfPatches; i++)
        patchDataList.append( QByteArray());
    patchListModel = new PatchListModel( patchDataList, dirtyPatchesIndexSet, this);

    timeOutTimer = new QTimer(this);
    timeOutTimer->setInterval(1000);
    timeOutTimer->setSingleShot(true);
    connect(timeOutTimer, SIGNAL(timeout()), this, SLOT(timeout()));

    midiOutTimer = new QTimer(this);
    midiOutTimer->setInterval(70);
    connect(midiOutTimer, SIGNAL(timeout()), this, SLOT(midiOutTimeOut()));

    portsInCombo = new QComboBox();
    portsInCombo->setModel(readableportsmodel);
    connect(portsInCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(portsInComboChanged(int)));
    portsOutCombo = new QComboBox();
    portsOutCombo->setModel(writableportsmodel);
    connect(portsOutCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(portsOutComboChanged(int)));
    //QSpinBox *deviceIdSpinbox = new QSpinBox();
    //deviceIdSpinbox->setMinimum(1);
    //deviceIdSpinbox->setMaximum(16);

    QGroupBox *settingsGroupbox = new QGroupBox( tr("Settings"));
    QFormLayout *settingsLayout = new QFormLayout();
    settingsLayout->addRow( new QLabel(tr("Midi In Port:")), portsInCombo);
    settingsLayout->addRow( new QLabel(tr("Midi Out Port:")), portsOutCombo);
    //settingsLayout->addRow( new QLabel(tr("Device ID:")), deviceIdSpinbox);
    settingsGroupbox->setLayout(settingsLayout);

    QGroupBox *patchListGroupbox = new QGroupBox( tr("Patch List"));

    requestButton = new QPushButton("Request All");
    connect(requestButton, SIGNAL(pressed()), this, SLOT(requestAll()));
    sendButton = new QPushButton("Send All");
    connect(sendButton, SIGNAL(pressed()), this, SLOT(sendAll()));

    QHBoxLayout *patchButtonsLayout = new QHBoxLayout();
    patchButtonsLayout->addWidget(requestButton);
    patchButtonsLayout->addWidget(sendButton);

    patchListLayout = new QVBoxLayout();
    patchListView = new QTableView();
    patchListView->setSelectionBehavior(QAbstractItemView::SelectRows);
    patchListView->setModel(patchListModel);
    connect(patchListView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(patchListDoubleClicked(QModelIndex)));
    patchListLayout->addWidget(patchListView);
    patchListGroupbox->setLayout(patchListLayout);

    patchListLayout->addLayout(patchButtonsLayout);
    patchListLayout->addWidget(patchListView);

    QVBoxLayout *mainLeftlayout = new QVBoxLayout();
    mainLeftlayout->addWidget( settingsGroupbox);
    mainLeftlayout->addWidget( patchListGroupbox);

    QWidget *dockWidgetDummy = new QWidget();
    dockWidgetDummy->setLayout(mainLeftlayout);

    QDockWidget *dockWidget = new QDockWidget();
    dockWidget->setFeatures( QDockWidget::DockWidgetMovable  | QDockWidget::DockWidgetFloatable);
    dockWidget->setObjectName( QStringLiteral("dockWidget"));
    dockWidget->setWidget(dockWidgetDummy);
    addDockWidget(Qt::LeftDockWidgetArea, dockWidget);

    PatchEditorWidget *editor = new PatchEditorWidget();
    connect(editor, SIGNAL(parameterChanged(int,int)), this, SLOT(parameterChanged(int,int)));
    setCentralWidget(editor);

#ifdef QT_DEBUG
    QSettings tmpsettings("/tmp/magicstompfrenzy.ini", QSettings::NativeFormat);
    QByteArray arr;
    arr = tmpsettings.value("Patch0data").toByteArray();
    if(arr.size() == PatchTotalLength)
        patchDataList[0] = arr;
    arr = tmpsettings.value("Patch1data").toByteArray();
    if(arr.size() == PatchTotalLength)
        patchDataList[1] = arr;
    patchListView->update();
#endif
}

MainWindow::~MainWindow()
{
#ifdef QT_DEBUG
    QSettings tmpsettings("/tmp/magicstompfrenzy.ini", QSettings::NativeFormat);
    tmpsettings.setValue( "Patch0data", patchDataList.at(0));
    tmpsettings.setValue( "Patch1data", patchDataList.at(1));
#endif
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
                        patchDataList[currentPatchTransmitted] = inData->mid(13, PatchCommonLength);
                        if( patchDataList[currentPatchTransmitted].size() != PatchCommonLength)
                        {
                            patchDataList[currentPatchTransmitted].clear();
                            return;
                        }
                    }
                }
                else if(inData->at(11)==0x01 && inData->at(12)==0x00)
                { // Patch effect data;
                    if(currentPatchTransmitted >=0 && currentPatchTransmitted < numOfPatches && length == PatchEffectLength)
                    {
                        patchDataList[currentPatchTransmitted].append( inData->mid(13, PatchEffectLength));
                        if( patchDataList[currentPatchTransmitted].size() != PatchTotalLength)
                        {
                            patchDataList[currentPatchTransmitted].clear();
                            return;
                        }
                        patchListModel->patchUpdated(currentPatchTransmitted);
                    }
                }
            }
        }
    }

}

void MainWindow::requestAll()
{
    putGuiToTransmissionState(true, false);

    currentPatchTransmitted = -1;
    requestPatch(0);
}

void MainWindow::requestPatch(int patchIndex)
{
    if(patchIndex >= numOfPatches || cancelOperation)
    {
        putGuiToTransmissionState(false, false);
        cancelOperation = false;
        return;
    }
    progressWidget->setValue(patchIndex+1);

    MidiEvent *midiev = new MidiEvent(static_cast<QEvent::Type>(MidiEvent::SysEx));
    QByteArray *reqArr = midiev->sysExData();

    reqArr->append(QByteArray(reinterpret_cast<const char*>(&dumpRequestHeader[0]),std::extent<decltype(dumpRequestHeader)>::value));
    reqArr->append(char(patchIndex));
    reqArr->append(0xF7);
    emit sendMidiEvent( midiev);
    timeOutTimer->start();
}

void MainWindow::sendAll()
{
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
    reqArr->append(0xF7);
    midiOutQueue.enqueue( midiev);

    for(int i=0; i<numOfPatches; i++)
        sendPatch(i, false);

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
    reqArr->append(0xF7);
    midiOutQueue.enqueue( midiev);

    midiOutTimer->start();
}

void MainWindow::sendPatch( int patchIdx, bool sendToTmpArea )
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
    reqArr->append(0xF7);
    midiOutQueue.enqueue( midiev);

    midiev = new MidiEvent(static_cast<QEvent::Type>(MidiEvent::SysEx));
    reqArr = midiev->sysExData();
    reqArr->append(QByteArray(reinterpret_cast<const char*>(&sysExBulkHeader[0]), sysExBulkHeaderLength));
    reqArr->append(static_cast<char>(0x00));
    reqArr->append(static_cast<char>(PatchCommonLength));
    reqArr->append(static_cast<char>(0x20));
    reqArr->append(static_cast<char>(0x00));
    reqArr->append(static_cast<char>(0x00));
    reqArr->append(patchDataList[patchIdx].left(PatchCommonLength));
    reqArr->append( calcChecksum( reqArr->constBegin()+ sysExBulkHeaderLength, reqArr->length()-sysExBulkHeaderLength));
    reqArr->append(0xF7);
    midiOutQueue.enqueue( midiev);

    midiev = new MidiEvent(static_cast<QEvent::Type>(MidiEvent::SysEx));
    reqArr = midiev->sysExData();
    reqArr->append(QByteArray(reinterpret_cast<const char*>(&sysExBulkHeader[0]), sysExBulkHeaderLength));
    reqArr->append(static_cast<char>(0x00));
    reqArr->append(static_cast<char>(PatchEffectLength));
    reqArr->append(static_cast<char>(0x20));
    reqArr->append(static_cast<char>(0x01));
    reqArr->append(static_cast<char>(0x00));
    reqArr->append(patchDataList[patchIdx].mid(PatchCommonLength, PatchEffectLength));
    reqArr->append( calcChecksum( reqArr->constBegin()+ sysExBulkHeaderLength, reqArr->length()-sysExBulkHeaderLength));
    reqArr->append(0xF7);
    midiOutQueue.enqueue( midiev);

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
    reqArr->append(0xF7);
    midiOutQueue.enqueue( midiev);
}

void MainWindow::timeout()
{
    currentPatchTransmitted = -1;
    QMessageBox::warning(this, tr("MIDI communication error"), tr("No response from Magictomp. Check MIDI connection."), QMessageBox::Ok );
    if(isInTransmissionState)
        putGuiToTransmissionState(false, false);
    cancelOperation = false;
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
        if(isInTransmissionState)
            putGuiToTransmissionState(false, false);
        return;
    }
    MidiEvent *ev = midiOutQueue.dequeue();
    emit sendMidiEvent( ev);
    if(isInTransmissionState)
        progressWidget->setValue( 100 - (midiOutQueue.size() / 4));
}

void MainWindow::parameterChanged(int offset, int length)
{
    qDebug("parameterChanged(offset=%d,len=%d)", offset, length);

    if( offset == PatchName) // Name needs to be sent as single chars
    {
        length = 1;
        patchListModel->patchUpdated(currentPatchEdited);
    }

    if( offset == PatchType)
    {
        patchListModel->patchUpdated(currentPatchEdited);
    }

    MidiEvent *midiev = new MidiEvent(static_cast<QEvent::Type>(MidiEvent::SysEx));
    QByteArray *reqArr = midiev->sysExData();
    reqArr->append(QByteArray(reinterpret_cast<const char*>(&sysExParameterSendHeader[0]), parameterSendHeaderLength));
    reqArr->append(0x20);
    if(offset < PatchCommonLength)
    {
        reqArr->append(static_cast<char>(0x00));
        reqArr->append(offset);
    }
    else
    {
        reqArr->append(0x01);
        reqArr->append(offset - PatchCommonLength);
    }
    ArrayDataEditWidget *editWidget = static_cast<ArrayDataEditWidget *>(centralWidget());
    for(int i= 0; i< length; i++)
    {
        reqArr->append( *(editWidget->DataArray()->constData()+offset+i));
    }
    reqArr->append(0xF7);
    emit sendMidiEvent( midiev);

    qDebug() << reqArr->toHex(',');

    if( offset == PatchName) // Name needs to be sent as single chars
    {
        for(int i= PatchName + 1; i < PatchNameLast; i++)
        {
            parameterChanged( i, 1);
        }
    }
    if( ! dirtyPatchesIndexSet.contains(currentPatchEdited ))
    {
        dirtyPatchesIndexSet.insert(currentPatchEdited);
        patchListModel->patchUpdated(currentPatchEdited);
    }
}

void MainWindow::putGuiToTransmissionState(bool isTransmitting, bool sending)
{
    if( isTransmitting)
    {
        requestButton->setEnabled(false);
        sendButton->setEnabled(false);
        patchListView->setEnabled(false);
        centralWidget()->setEnabled( false);

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
        patchListView->setEnabled(true);
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
    if( patchDataList.at( idx.row()).isEmpty())
        return;

    sendPatch(idx.row());
    midiOutTimer->start();
    ArrayDataEditWidget *widget = static_cast<ArrayDataEditWidget *>(centralWidget());
    widget->setDataArray(& patchDataList[idx.row()]);
    currentPatchEdited = idx.row();
}

void MainWindow::portsInComboChanged(int rowIdx)
{
    // TODO:It should be possible to subcribe ( connect ) to multiple ports.

    emit readableMidiPortSelected(portsInCombo->currentData( MidiPortModel::ClientIdRole).toInt(),
                                  portsInCombo->currentData( MidiPortModel::PortIdRole).toInt());

    Q_UNUSED(rowIdx)

}
void MainWindow::portsOutComboChanged(int rowIdx)
{
    Q_UNUSED(rowIdx)

    emit writableMidiPortSelected(portsOutCombo->currentData( MidiPortModel::ClientIdRole).toInt(),
                                  portsOutCombo->currentData( MidiPortModel::PortIdRole).toInt());
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
