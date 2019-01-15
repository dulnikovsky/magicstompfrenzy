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
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QQueue>
#include <QSet>
#include <QMap>

class MidiPortModel;
class PatchListModel;
class QTableView;
class QPushButton;
class QVBoxLayout;
class ProgressWidget;
class QListView;

class MidiEvent;

class QItemSelection;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow( MidiPortModel *readableportsmodel, MidiPortModel *writableportsmodel, QWidget *parent = Q_NULLPTR);

public slots:
    void midiEvent(MidiEvent *event);

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    enum PatchListType { User, GuitarPreset, BassPreset, AcousticPreset};

private slots:
    void requestAll();
    void sendAll(bool startMidiOutTimer = true);
    void requestPatch(int patchIndex);
    void sendPatch(int patchIndex, bool sendToTmpArea = true, PatchListType type=User,  bool startMidiOutTimer = true);

    void parameterToBeChanged(int offset, int length);
    void parameterChanged(int offset, int length);

    void timeout();
    void midiOutTimeOut();
    void cancelTransmission();
    void patchListDoubleClicked(const QModelIndex& idx);
    void patchListSelectionChanged();
    void putGuiToTransmissionState( bool isTransmitting, bool sending);

    void swapButtonPressed();
    void copyButtonPressed();
    void undoRedoButtonPressed();

    void showPreferences();

    void saveSettings();
    void restoreSettings();

    void importSMF();
    void exportSMF();

private:
    void loadPresetPatches(int index, const QString &filename);
    PatchListType getCurrentPatchType() const;

    MidiPortModel *readablePortsModel;
    MidiPortModel *writablePortsModel;

    //PatchListModel *patchListModel;
    QList<PatchListModel *> patchListModelList;
    PatchListModel *tmpPatchListModel;

    QTimer *timeOutTimer;
    QTimer *midiOutTimer;
    QQueue< MidiEvent *> midiOutQueue;

    //QList<QByteArray> patchDataList;
    QList<QList<QByteArray>> newPatchDataList;
    QList<QByteArray> tmpPatchDataList;
    QList<QMap<int, QPair<QByteArray, bool>>> backupPatchesMapList;

    QTabWidget *patchTabWidget;

    QTableView *patchListView;
    QPushButton *requestButton;
    QPushButton *sendButton;
    ProgressWidget *progressWidget;

    QPushButton *swapButton;
    QPushButton *copyButton;
    QPushButton *undoRedoButton;

    QVBoxLayout *patchListLayout;

    QAction *showPreferencesAction;
    QAction *importSMFAction;
    QAction *exportSMFAction;

    int currentPatchTransmitted;
    QPair<PatchListType, int> currentPatchEdited;

    bool cancelOperation;
    bool isInTransmissionState;

    static char calcChecksum(const char *data, int dataLength);
};

#endif // MAINWINDOW_H
