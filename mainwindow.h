#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QQueue>
#include <QSet>
#include "midiapplication.h"

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

signals:
    void readableMidiPortSelected( MidiClientPortId id);
    void writableMidiPortSelected( MidiClientPortId id);
    void sendMidiEvent(MidiEvent *);

private:
    enum PatchListType { User, GuitarPreset, BassPreset, AcousticPreset};

private slots:
    void requestAll();
    void sendAll();
    void requestPatch(int patchIndex);
    void sendPatch(int patchIndex, bool sendToTmpArea = true, PatchListType type =User);

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

private:
    void loadPresetPatches(int index, const QString &filename);

    int currentPatchTransmitted;
    QPair<PatchListType, int> currentPatchEdited;
    int patchToCopy;

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

    bool cancelOperation;
    bool isInTransmissionState;

    static char calcChecksum(const char *data, int dataLength);
};

#endif // MAINWINDOW_H
