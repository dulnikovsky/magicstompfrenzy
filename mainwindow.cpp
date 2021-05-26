/****************************************************************************
**
** Copyright (C) 2018 Robert Vetter.
**
** This file is part of the MagicstompFrenzy - an editor for Yamaha Magicstomp
** effect processor
**
** THIS CODE IS PROVIDED *AS IS* WITHOUT WARRANTY OF
** ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING ANY
** IMPLIED WARRANTIES OF FITNESS FOR A PARTICULAR
** PURPOSE, MERCHANTABILITY, OR NON-INFRINGEMENT.
**
** GNU General Public License Usage
** This file may be used under the terms of the GNU
** General Public License version 2.0 or (at your option) the GNU General
** Public license version 3 or any later version . The licenses are
** as published by the Free Software Foundation and appearing in the file LICENSE
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-2.0.html and
** https://www.gnu.org/licenses/gpl-3.0.html.
**/

#include "mainwindow.h"
#include "midiportmodel.h"
#include "patchlistmodel.h"
#include "midievent.h"
#include "patcheditorwidget.h"
#include "progresswidget.h"
#include "patchcopydialog.h"
#include "preferencesdialog.h"
#include "aboutdialog.h"
#include "magicstomp.h"
#include "importbankselectiondialog.h"

#include "midiapplication.h"

#include "standardmidifile.h"
#include "ub99file.h"

#include <QGroupBox>
#include <QListView>
#include <QTableView>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QLabel>
#include <QSpinBox>
#include <QPushButton>
#include <QSpinBox>
#include <QSplitter>
#include <QTimer>
#include <QMessageBox>
#include <QProgressDialog>
#include <QSettings>
#include <QDir>
#include <QStandardPaths>
#include <QItemSelectionModel>
#include <QTabWidget>
#include <QAction>
#include <QCloseEvent>
#include <QMenuBar>
#include <QFileDialog>
#include <QDebug>

static const int sysExBulkHeaderLength = 8;
static const unsigned char sysExBulkHeader[sysExBulkHeaderLength] = { 0xF0, 0x43, 0x7D, 0x30, 0x55, 0x42, 0x39, 0x39 };
static const unsigned char dumpRequestHeader[] = { 0xF0, 0x43, 0x7D, 0x50, 0x55, 0x42, 0x30, 0x01 };

static const int parameterSendHeaderLength = 6;
static const unsigned char sysExParameterSendHeader[parameterSendHeaderLength] = { 0xF0, 0x43, 0x7D, 0x40, 0x55, 0x42 };

MainWindow::MainWindow(MidiPortModel *readPortsMod, MidiPortModel *writePortsMod, QWidget *parent)
    : QMainWindow(parent), readablePortsModel(readPortsMod), writablePortsModel(writePortsMod),
      currentPatchTransmitted(-1), currentPatchEdited(QPair<PatchListType,int>(User,-1)),
      cancelOperation(false), isInTransmissionState(false), isInImportState(false)
{
    newPatchDataList.append(QList<QByteArray>());
    for(int i=0; i<numOfPatches; i++)
    {
        newPatchDataList[0].append( QByteArray());
        tmpPatchDataList.append( QByteArray());
    }

    for(int i=0; i<NumPatchListTypes; i++)
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

    newPatchDataList.append(QList<QByteArray>()); // init SMF Import
    for(int i=0; i<numOfPatches; i++)
    {
        newPatchDataList[SMFImport].append( QByteArray());
    }

    patchListModelList.append(new PatchListModel( newPatchDataList.at(User), backupPatchesMapList.at(User), this));
    patchListModelList.append(new PatchListModel( newPatchDataList.at(GuitarPreset), backupPatchesMapList.at(GuitarPreset), this));
    patchListModelList.append(new PatchListModel( newPatchDataList.at(BassPreset), backupPatchesMapList.at(BassPreset), this));
    patchListModelList.append(new PatchListModel( newPatchDataList.at(AcousticPreset), backupPatchesMapList.at(AcousticPreset), this));
    patchListModelList.append(new PatchListModel( newPatchDataList.at(SMFImport), backupPatchesMapList.at(SMFImport), this));

    timeOutTimer = new QTimer(this);
    timeOutTimer->setInterval(1000);
    timeOutTimer->setSingleShot(true);
    connect(timeOutTimer, SIGNAL(timeout()), this, SLOT(timeout()));

    midiOutTimer = new QTimer(this);
    connect(midiOutTimer, SIGNAL(timeout()), this, SLOT(midiOutTimeOut()));

    showPreferencesAction = new QAction(tr("&Preferences"), this);
    connect(showPreferencesAction, &QAction::triggered, this, &MainWindow::showPreferences);

    importAction = new QAction(tr("&Import"), this);
    connect(importAction, &QAction::triggered, this, &MainWindow::onImport);

    exportAction = new QAction(tr("&Export"), this);
    connect(exportAction, &QAction::triggered, this, &MainWindow::onExport);

    QAction *quitAction = new QAction(tr("&Quit"), this);
    connect(quitAction, &QAction::triggered, this, &MainWindow::close);

    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(importAction);
    fileMenu->addAction(exportAction);
    fileMenu->addSeparator();
    fileMenu->addAction(showPreferencesAction);
    fileMenu->addSeparator();
    fileMenu->addAction(quitAction);

    QMenu *helpMenu = menuBar()->addMenu(tr("&Help"));
    QAction *aboutAct = new QAction(tr("&About"), this);
    connect(aboutAct, &QAction::triggered, [this]() {
           AboutDialog abdialog(this);
           abdialog.exec();
       });

    helpMenu->addAction(aboutAct);
    QAction *aboutQtAct = new QAction(tr("About &Qt"), this);
    connect(aboutQtAct, &QAction::triggered, [this]() {
           QMessageBox::aboutQt(this);
       });
    helpMenu->addAction(aboutQtAct);

    patchNameLabel = new QLabel();
    patchNameLabel->setStyleSheet("font: 40pt;");

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


    QTableView *smfImportPatchListView = new QTableView();
    smfImportPatchListView->setSelectionBehavior(QAbstractItemView::SelectRows);
    smfImportPatchListView->setModel(patchListModelList.at(SMFImport));
    connect(smfImportPatchListView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(patchListDoubleClicked(QModelIndex)));
    connect(smfImportPatchListView->selectionModel(), SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
            this, SLOT(patchListSelectionChanged()));
    patchTabWidget->addTab( smfImportPatchListView, tr("Imported Patches"));

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
    mainLeftlayout->addWidget( patchNameLabel);
    mainLeftlayout->addWidget( patchListGroupbox);

    QWidget *dockWidgetDummy = new QWidget();
    dockWidgetDummy->setMinimumSize(440, 196);
    dockWidgetDummy->setLayout(mainLeftlayout);

    QSplitter *splitter = new QSplitter( Qt::Horizontal);
    splitter->addWidget( dockWidgetDummy);

    /*QDockWidget *dockWidget = new QDockWidget();
    dockWidget->setFeatures( QDockWidget::DockWidgetMovable  | QDockWidget::DockWidgetFloatable);
    dockWidget->setObjectName( QStringLiteral("dockWidget"));
    dockWidget->setWidget(dockWidgetDummy);
    addDockWidget(Qt::LeftDockWidgetArea, dockWidget);*/
    //resizeDocks({dockWidget}, {600}, Qt::Horizontal); // workaroud for dock widget resize bug

    PatchEditorWidget *editor = new PatchEditorWidget();
    connect(editor, SIGNAL(parameterAboutToBeChanged(int,int,QWidget *)), this, SLOT(parameterToBeChanged(int,int,QWidget *)));
    connect(editor, SIGNAL(parameterChanged(int,int,QWidget *)), this, SLOT(parameterChanged(int,int,QWidget *)));
    connect(editor, SIGNAL(patchTypeEditorChanged(int)), this, SLOT(onPatchTypeEditorChanged(int)));

    splitter->addWidget( editor);

    setCentralWidget(splitter);

#if defined(QT_DEBUG) && defined(Q_OS_LINUX)
    QSettings cacheSettings(QStandardPaths::writableLocation(QStandardPaths::CacheLocation)+QStringLiteral("/patchcache.ini"), QSettings::IniFormat);
    for(int i=0; i<numOfPatches;i++)
    {
        QByteArray arr;
        arr = cacheSettings.value("Patchdata"+QString::number(i+1).rightJustified(2, '0')).toByteArray();
        if(arr.size() == PatchTotalLength && arr.at(PatchType+1)<EffectTypeNUMBER)
            newPatchDataList[User][i] = arr;
    }
#endif
    //patchListView->resizeColumnsToContents();
    guitarPatchListView->resizeColumnsToContents();
    bassPatchListView->resizeColumnsToContents();
    acousticPatchListView->resizeColumnsToContents();
    setMinimumHeight(256);

    nameToCCMap.insert("Master", 7 | (1 << 12));
    nameToCCMap.insert("Gain", 16 | (1 << 12));
    nameToCCMap.insert("EffectLevel", 80 | (1 << 8) | (1 << 12));
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    for(int i=0; i <= AcousticPreset; i++)
    {
        if(! backupPatchesMapList.at(i).isEmpty() )
        {
            QMessageBox msgBox;
            msgBox.setText(tr("Application contains unsaved/untranferred data."));
            msgBox.setInformativeText(tr("Do you really want to exit?"));
            msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
            msgBox.setDefaultButton(QMessageBox::No);
            int ret = msgBox.exec();
            if(ret == QMessageBox::No)
            {
                event->ignore();
                return;
            }
            else
            {
                break;
            }
        }
    }
#if defined(QT_DEBUG) && defined(Q_OS_LINUX)
    QSettings cacheSettings(QStandardPaths::writableLocation(QStandardPaths::CacheLocation)+QStringLiteral("/patchcache.ini"), QSettings::IniFormat);
    for(int i=0; i<numOfPatches;i++)
    {
        if(newPatchDataList.at(User).at(i).size() == PatchTotalLength)
            cacheSettings.setValue("Patchdata"+QString::number(i+1).rightJustified(2, '0'), newPatchDataList.at(User).at(i));
    }
#endif
    saveSettings();
    QMainWindow::closeEvent(event);
}

void MainWindow::midiEvent(MidiEvent *ev)
{
    if( ev->type() == static_cast<QEvent::Type>(UserEventTypes::MidiSysEx))
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

        if(! isInTransmissionState && !isInImportState) // incoming unexpected data
        {
            qDebug("Incoming unexpected data!");
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
                if(! isInImportState)
                    patchListView->scrollTo(patchListView->model()->index(currentPatchTransmitted, 0));
                currentPatchTransmitted = -1;
                if(! isInImportState)
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
    else if( ev->type() == static_cast<QEvent::Type>(UserEventTypes::MidiCommon) && !isInTransmissionState && !isInImportState)
    {
        if(ev->Status() == MidiEvent::MidiEventType::ProgramChange)
        {
            if(midiChannel == 0 || (midiChannel == ev->Channel()+1) )
            {
                if(ev->Data1() < 100)
                {
                    QModelIndex index = patchListModelList.at(0)->index( ev->Data1(), 0, QModelIndex());
                    patchListDoubleClicked( index );
                    patchTabWidget->setCurrentIndex( 0);
                    patchListView->selectRow(ev->Data1());
                }
            }
        }
        else if(ev->Status() == MidiEvent::MidiEventType::ControlChange)
        {
            if(midiChannel == 0 || (midiChannel == ev->Channel()+1) )
            {
                qDebug("CC %d %d", ev->Data1(), ev->Data2());
                QMap<int, widgetWithVal>::const_iterator iter = ccToWidgetMap.find(ev->Data1());
                if( iter != ccToWidgetMap.constEnd())
                {
                    if(iter.value().ccMode == SwitchLatch)
                    {
                        if(ev->Data2() != 0)
                        {
                            if( qFuzzyCompare(iter.value().dspinBox->minimum(), iter.value().dspinBox->value()) )
                                iter.value().dspinBox->setValue( iter.value().storedValue);
                            else
                                iter.value().dspinBox->setValue( iter.value().dspinBox->minimum());
                        }
                    }
                    else
                    {
                        iter.value().dspinBox->setValue( (static_cast<double>(ev->Data2())/127) * iter.value().storedValue);
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
            backupPatchesMapList[User].clear();
            QMessageBox::information(this, tr("MagicstimpFrenzy"), tr("Data requested successfully"));
        }
        else
        {
            QMessageBox::information(this, tr("MagicstimpFrenzy"), tr("Oparation was cancelled. Press a button on your Magicstomp."));
        }
        patchListView->setModel( patchListModelList.at(User));
        connect(patchListView->selectionModel(), SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
                this, SLOT(patchListSelectionChanged()));
        patchListView->resizeColumnsToContents();
        cancelOperation = false;
        return;
    }
    progressWidget->setValue(patchIndex+1);

    MidiEvent *midiev = new MidiEvent(static_cast<QEvent::Type>(UserEventTypes::MidiSysEx));
    QByteArray *reqArr = midiev->sysExData();

    reqArr->append(QByteArray(reinterpret_cast<const char*>(&dumpRequestHeader[0]),std::extent<decltype(dumpRequestHeader)>::value));
    reqArr->append(char(patchIndex));
    reqArr->append(static_cast<char>(0xF7));
    static_cast<MidiApplication *>(qApp)->sendMidiEvent(midiev);
    timeOutTimer->start();
}

void MainWindow::sendAll(bool startMidiOutTimer)
{
    if( ! hasValidUserPatches())
    {
        QMessageBox::warning(this, QStringLiteral("MagicstompFrenzy"), tr("Sending data to Magicstomp if User patch list is not complete is not possible."));
            return;
    }

    putGuiToTransmissionState(true, true);

    MidiEvent *midiev = new MidiEvent(static_cast<QEvent::Type>(UserEventTypes::MidiSysEx));
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
        sendPatch(i, false, User, false);

    //Bulk out all end
    midiev = new MidiEvent(static_cast<QEvent::Type>(UserEventTypes::MidiSysEx));
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
    if(startMidiOutTimer)
    {
        midiOutTimer->setInterval(70);
        midiOutTimer->start();
    }
}

void MainWindow::sendPatch( int patchIdx, bool sendToTmpArea, PatchListType type, bool startMidiOutTimer )
{
    MidiEvent *midiev = new MidiEvent(static_cast<QEvent::Type>(UserEventTypes::MidiSysEx));
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

    midiev = new MidiEvent(static_cast<QEvent::Type>(UserEventTypes::MidiSysEx));
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
#if QT_VERSION >= 0x050900
    qDebug() << "send Patch Common :" << reqArr->toHex(',');
#endif
    midiev = new MidiEvent(static_cast<QEvent::Type>(UserEventTypes::MidiSysEx));
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
#if QT_VERSION >= 0x050900
    qDebug() << "send Patch Effect :" << reqArr->toHex(',');
#endif
    midiev = new MidiEvent(static_cast<QEvent::Type>(UserEventTypes::MidiSysEx));
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
    if(startMidiOutTimer)
    {
        midiOutTimer->setInterval(70);
        midiOutTimer->start();
    }
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
    static_cast<MidiApplication *>(qApp)->sendMidiEvent(ev);
    if(isInTransmissionState)
        progressWidget->setValue( 100 - (midiOutQueue.size() / 4));
}

void MainWindow::parameterToBeChanged(int offset, int length, QWidget *editWidget)
{
    tmpArray.clear();
    if( ! editWidget->hasFocus() && dynamic_cast< QSpinBox *>(editWidget) != nullptr)
        tmpArray = newPatchDataList[currentPatchEdited.first][currentPatchEdited.second].mid( offset, length);

    if(! backupPatchesMapList.at(currentPatchEdited.first).contains(currentPatchEdited.second))
    {
        backupPatchesMapList[currentPatchEdited.first].insert(currentPatchEdited.second,
                  QPair<QByteArray, bool>(newPatchDataList[currentPatchEdited.first][currentPatchEdited.second], true));
    }
    else if ( backupPatchesMapList.at(currentPatchEdited.first).value(currentPatchEdited.second).second == false)
    { //If backup map contains the edited patch ( and not the original patch). This happens after the "undo" operation
        backupPatchesMapList[currentPatchEdited.first].insert(currentPatchEdited.second,
                  QPair<QByteArray, bool>(newPatchDataList[currentPatchEdited.first][currentPatchEdited.second], true));
    }
    patchListSelectionChanged();
}

void MainWindow::parameterChanged(int offset, int length, QWidget *paramEditWidget)
{
    qDebug("parameterChanged(offset=%d,len=%d)", offset, length);

    ArrayDataEditWidget *editWidget = static_cast<ArrayDataEditWidget *>( static_cast<QSplitter *>(centralWidget())->widget(1));
    if(editWidget == nullptr)
        return;

    if( offset == PatchName) // Name needs to be sent as single chars
    {
        length = 1;
        patchListModelList[currentPatchEdited.first]->patchUpdated(currentPatchEdited.second);
        QByteArray &dataArrRef = newPatchDataList[currentPatchEdited.first][currentPatchEdited.second];
        patchNameLabel->setText( QString::number( currentPatchEdited.second +1).rightJustified(2, '0') + " " + dataArrRef.mid(PatchName, PatchNameLength));
    }

    MidiEvent *midiev = new MidiEvent(static_cast<QEvent::Type>(UserEventTypes::MidiSysEx));
    QByteArray *reqArr = midiev->sysExData();
    reqArr->append(QByteArray::fromRawData(reinterpret_cast<const char*>(&sysExParameterSendHeader[0]), parameterSendHeaderLength));
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

    //Check for multiple events for same parameter in the midi out queue.
    //This can happen during fast changing a parameter by Control Change messages
    QQueue<MidiEvent *>::iterator it = midiOutQueue.begin();
    while (it != midiOutQueue.end())
    {
        QByteArray *sysexData = (*it)->sysExData();
        if( sysexData->startsWith(reqArr->left(parameterSendHeaderLength +3)))
        {
            MidiEvent *eventToRemove = *it;
            it = midiOutQueue.erase( it);
            delete eventToRemove;
            qDebug ("Removed item");
        }
        else
        {
            it++;
        }
    }
#if QT_VERSION >= 0x050900
    qDebug() << reqArr->toHex(',');
#endif
    midiOutQueue.enqueue( midiev);
    if(! midiOutTimer->isActive())
    {
        midiOutTimer->setInterval(10);
        midiOutTimer->start();
    }

    if( offset == PatchName) // Name needs to be sent as single chars
    {
        for(int i= PatchName + 1; i < PatchNameLast; i++)
        {
            parameterChanged( i, 1, paramEditWidget);
        }
    }

    if( (! paramEditWidget->hasFocus()) && (! tmpArray.isEmpty()))
    {
        newPatchDataList[currentPatchEdited.first][currentPatchEdited.second].replace(offset, length, tmpArray);
        tmpArray.clear();
    }

    QMap<int, widgetWithVal>::const_iterator iter = ccToWidgetMap.constBegin();
    while (iter != ccToWidgetMap.constEnd())
    {
        if( paramEditWidget->hasFocus() && iter.value().dspinBox == paramEditWidget)
        {
            buildCCToWidgetMap();
            break;
        }
        iter++;
    }

    if( offset == PatchType)
    {
        QSettings effectiniSettings(QApplication::applicationDirPath()+"/effects.ini", QSettings::IniFormat);
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
    ArrayDataEditWidget *editWidget = static_cast<ArrayDataEditWidget *>( static_cast<QSplitter *>(centralWidget())->widget(1));

    if( isTransmitting)
    {
        requestButton->setEnabled(false);
        sendButton->setEnabled(false);
        patchTabWidget->setEnabled(false);
        editWidget->setEnabled( false);
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
        menuBar()->setEnabled(false);
    }
    else
    {
        if( editWidget->DataArray() != nullptr )
            editWidget->setEnabled( true);
        requestButton->setEnabled(true);
        sendButton->setEnabled(true);
        patchTabWidget->setEnabled(true);

        menuBar()->setEnabled(true);

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

    patchNameLabel->clear();

    if(i >= patchListModelList.size())
        return;

    PatchListType type = static_cast<PatchListType>(i);

    if( newPatchDataList.at(type).at( idx.row()).isEmpty())
        return;

    sendPatch(idx.row(), true, type);
    //midiOutTimer->start();
    ArrayDataEditWidget *widget = static_cast<ArrayDataEditWidget *>( static_cast<QSplitter *>(centralWidget())->widget(1));
    currentPatchEdited = QPair<PatchListType, int>(type, idx.row());
    widget->setDataArray(& newPatchDataList[type][idx.row()]);

    patchNameLabel->setText( QString::number( currentPatchEdited.second +1).rightJustified(2, '0') + " " + newPatchDataList[type][idx.row()].mid(PatchName, PatchNameLength));
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
        ArrayDataEditWidget *editWidget = static_cast<ArrayDataEditWidget *>( static_cast<QSplitter *>(centralWidget())->widget(1));
        editWidget->setDataArray(& newPatchDataList[User][rowB]);
    }
    else if(QPair<PatchListType, int>( User, rowB)  == currentPatchEdited)
    {
        currentPatchEdited =  QPair<PatchListType, int>( User, rowA);
        ArrayDataEditWidget *editWidget = static_cast<ArrayDataEditWidget *>( static_cast<QSplitter *>(centralWidget())->widget(1));
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
            ArrayDataEditWidget *editWidget = static_cast<ArrayDataEditWidget *>( static_cast<QSplitter *>(centralWidget())->widget(1));
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

    ArrayDataEditWidget *editWidget = static_cast<ArrayDataEditWidget *>( static_cast<QSplitter *>(centralWidget())->widget(1));
    editWidget->setDataArray(& (newPatchDataList[type][row]));
    sendPatch(row, true, type);

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

    PreferencesDialog prefDialog(readablePortsModel, writablePortsModel, nameToCCMap, this);
    connect( &prefDialog, SIGNAL(midiInPortStatusChanged( MidiClientPortId, bool)), thisMidiApp, SLOT(changeReadableMidiPortStatus(MidiClientPortId,bool)) );
    connect( &prefDialog, SIGNAL(midiOutPortStatusChanged( MidiClientPortId, bool)), thisMidiApp, SLOT(changeWritebleMidiPortStatus(MidiClientPortId,bool)) );
    connect( &prefDialog, SIGNAL(midiChannelChanged(int)), this, SLOT(setMIDIChannel(int)));
    connect( &prefDialog, SIGNAL(paramToCCChanged(QString, int,int)), this, SLOT(onParamToCCChaged(QString, int,int)));
    prefDialog.exec();

    prefDialog.disconnect(thisMidiApp);
}
void MainWindow::onParamToCCChaged( const QString &name, int newVal, int oldVal)
{
    Q_UNUSED(name)

    QMap<int, widgetWithVal>::iterator iter = ccToWidgetMap.find( oldVal & 0x7F);
    if(iter == ccToWidgetMap.end())
        return;

    ccToWidgetMap.insert( newVal & 0x7F, iter.value());
    ccToWidgetMap.erase(iter);
}

void MainWindow::saveSettings()
{
    QSettings settings;
    settings.setValue("MainWindowGeometry", saveGeometry());
    settings.setValue("MainWindowState", saveState());

    settings.beginGroup("MidiConnections");
    settings.setValue(QStringLiteral("IncomingConnections"), readablePortsModel->currentConnectionsNameList());
    settings.setValue(QStringLiteral("OutgoingConnections"), writablePortsModel->currentConnectionsNameList());
    settings.endGroup();

    settings.beginGroup(QStringLiteral("MidiControls"));
    QMap<QString, int>::const_iterator iter = nameToCCMap.constBegin();
    while (iter != nameToCCMap.constEnd())
    {
        QStringList valList;
        valList.append( QString::number(iter.value() & 0x7F));
        valList.append( QString::number((iter.value() & 0x0F00) >>8));
        valList.append( QString::number((iter.value() & 0xF000) >>12));
        settings.setValue(iter.key(), valList);
        iter++;
    }
    settings.endGroup();
}

void MainWindow::restoreSettings()
{
    QSettings settings;

    restoreGeometry(settings.value("MainWindowGeometry").toByteArray());
    restoreState(settings.value("MainWindowState").toByteArray());

    /*QPalette palette = this->palette();
    palette.setColor(QPalette::Window, Qt::gray);
    palette.setColor(QPalette::Base, Qt::lightGray);
    setPalette(palette);*/

    settings.beginGroup(QStringLiteral("MidiControls"));
    QStringList keyList = settings.childKeys();
    for(int i=0; i<keyList.size(); i++)
    {
        if(keyList.at(i) == QStringLiteral("MIDIChannel"))
        {
            setMIDIChannel(settings.value(keyList.at(i), 0).toInt());
        }
        else
        {
            QStringList valList = settings.value(keyList.at(i), 0).toStringList();
            if(valList.size() < 3)
                continue;
            int ccNumber = valList.at(0).toInt();
            int ccMode = valList.at(1).toInt();
            int ccInitMode = valList.at(2).toInt();

            int val = (ccNumber & 0x7F) | ((ccMode & 0x0F) << 8) | ((ccInitMode & 0x0F) << 12);
            nameToCCMap.insert(keyList.at(i), val);
        }
    }
    settings.endGroup();

    if(!settings.contains(QStringLiteral("RestoreMidiConnectionsAtStartUp")))
    {
        settings.setValue(QStringLiteral("RestoreMidiConnectionsAtStartUp"), true);
        QMetaObject::invokeMethod(this, "showPreferences", Qt::QueuedConnection);
    }
    else if(settings.value(QStringLiteral("RestoreMidiConnectionsAtStartUp"), true).toBool() == true)
    {
        settings.beginGroup("MidiConnections");
        QStringList connectionsList;
        QSet<QString> failedPorts;
        bool ret;
        connectionsList = settings.value(QStringLiteral("IncomingConnections")).toStringList();
        for(int i=0; i< connectionsList.size(); i++)
        {
            ret = static_cast<MidiApplication *>(qApp)->changeReadableMidiPortStatus(connectionsList.at(i), true);
            if(! ret)
                failedPorts.insert(connectionsList.at(i));
        }

        connectionsList = settings.value(QStringLiteral("OutgoingConnections")).toStringList();
        for(int i=0; i< connectionsList.size(); i++)
        {
            ret = static_cast<MidiApplication *>(qApp)->changeWritebleMidiPortStatus(connectionsList.at(i), true);
            if(! ret)
                failedPorts.insert(connectionsList.at(i));
        }
        settings.endGroup();

        if( !failedPorts.isEmpty())
        {
            QMessageBox::warning(this, qApp->applicationName(), tr("Could not open MIDI ports used last time:\n %1").arg( QStringList(failedPorts.toList()).join('\n')));
        }
    }
}

void MainWindow::onImport()
{
    ImportBankSelectionDialog dial(this);
    if( dial.exec() == QDialog::Rejected )
        return;

    PatchListType type = dial.SelectedTab()==ImportBankSelectionDialog::ImportTab?SMFImport:User;

    bool ret = false;
    QFileInfo fileInfo(dial.fileName());
    if(fileInfo.suffix() == "mid")
    {
        ret = importSMF( dial.fileName(), type);
    }
    else
    {
        ret = importUB99(dial.fileName(), type);
    }
    if( ! ret)
    {
        QMessageBox::warning(this, qApp->applicationName(), tr("Error. Could not open or read file %1.").arg( dial.fileName() ));
        return;
    }
    patchTabWidget->setCurrentIndex( type);
}

bool MainWindow::importSMF(const QString &fileName, PatchListType type)
{
    StandardMidiFile smf(fileName);

    if( ! smf.open(QIODevice::ReadOnly))
        return false;

    MidiEventList midieventlist;
    smf.readNextTrack(midieventlist);

    isInImportState = true;
    for(int i=0; i< numOfPatches; i++)
        tmpPatchDataList[i].clear();

    for(int i=0; i<midieventlist.size(); i++)
    {
        MidiEvent *ev = midieventlist[i];
        midiEvent( ev);
        delete ev;
    }
    isInImportState = false;

    bool importComplete = true;
    for(int i=0; i<tmpPatchDataList.size(); i++)
    {
        if(tmpPatchDataList.at(i).size() != PatchTotalLength)
        {
            importComplete = false;
            break;
        }
    }

    if( ! importComplete)
    {
        return false;
    }
    newPatchDataList[type] = tmpPatchDataList;
    backupPatchesMapList[type].clear();

    return true;
}

bool MainWindow::importUB99(const QString &fileName, PatchListType type)
{
    UB99File ub99file(fileName);
    if( ! ub99file.open(QIODevice::ReadOnly))
        return false;

    QList<QByteArray> ub99DataList;
    ub99DataList = ub99file.patchData();

    newPatchDataList[type] = ub99DataList;
    backupPatchesMapList[type].clear();

    return true;
}

void MainWindow::onExport()
{
    if( ! hasValidUserPatches())
    {
        QMessageBox::warning(this, QStringLiteral("MagicstompFrenzy"), tr("Exporting if User patch list is not complete is not possible."));
            return;
    }
    QString fileName = QFileDialog::getSaveFileName(this, tr("Export User Patches to Standard MID File"),
                               QStandardPaths::writableLocation(QStandardPaths::HomeLocation),
                               tr("UB99 files (*.ub9);;Standard MIDI Files (*.mid)"));

    if(fileName.isEmpty())
        return;

    QFileInfo fileInfo(fileName);
    if( fileInfo.suffix() == "mid")
    {
        StandardMidiFile smf(fileName);
        smf.setTrackNum(1);
        smf.setTicksPerQuarterNote(96);
        if( smf.open(QIODevice::WriteOnly) == false )
        {
            QMessageBox::warning(this, qApp->applicationName(), tr("Could not open file %1 for writing.").arg( fileName ));
            return;
        }
        sendAll( false); // enque all midi events without sending them;
        if( midiOutQueue.isEmpty())
        {
            smf.close();
            return;
        }
        smf.writeTrack(midiOutQueue);
        midiOutQueue.clear();
        smf.close();
        putGuiToTransmissionState(false, false);
    }
    else
    {
        UB99File ub99file(fileName);
        if( ub99file.open(QIODevice::WriteOnly) == false )
        {
            QMessageBox::warning(this, qApp->applicationName(), tr("Could not open file %1 for writing.").arg( fileName ));
            return;
        }
        ub99file.writePatchData(newPatchDataList.at(User));
        ub99file.close();
    }
}

void MainWindow::onPatchTypeEditorChanged( int typeId)
{
    Q_UNUSED(typeId)
    buildCCToWidgetMap();
}

void MainWindow::buildCCToWidgetMap()
{
    ArrayDataEditWidget *editWidget = static_cast<ArrayDataEditWidget *>( static_cast<QSplitter *>(centralWidget())->widget(1));
    if(editWidget == nullptr)
        return;

    ccToWidgetMap.clear();

    QMap<QString, int>::const_iterator iter = nameToCCMap.constBegin();
    while (iter != nameToCCMap.constEnd())
    {
        QDoubleSpinBox *spinBox;
        spinBox = editWidget->findChild< QDoubleSpinBox *>( iter.key() );
        if( spinBox != nullptr)
        {
            widgetWithVal wwv;
            wwv.dspinBox = spinBox;
            wwv.ccMode = static_cast<CCMode>((iter.value() & 0x0F00) >> 8);
            wwv.ccInitMode = static_cast<CCInitMode>((iter.value() & 0xF000) >> 12);
            if(wwv.ccInitMode == CCInitMode::Miniumum)
                spinBox->setValue( spinBox->minimum());
            else
                wwv.storedValue = spinBox->value();
            ccToWidgetMap.insert( iter.value() & 0x7F, wwv );
        }
        ++iter;
    }
}

bool MainWindow::hasValidUserPatches() const
{
    const QList<QByteArray> &userList = newPatchDataList.at(User);
    for(int i=0; i<userList.size(); i++)
    {
        if(userList.at(i).size() != PatchTotalLength)
        {
            return false;
        }
    }
    return true;
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

void MainWindow::hideEditor()
{
    centralWidget()->hide();
}
