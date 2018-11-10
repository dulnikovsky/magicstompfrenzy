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

private slots:
    void requestAll();
    void sendAll();
    void requestPatch(int patchIndex);
    void sendPatch(int patchIndex, bool sendToTmpArea = true);

    void parameterChanged(int offset, int length);

    void timeout();
    void midiOutTimeOut();
    void cancelTransmission();
    void patchListDoubleClicked(const QModelIndex& idx);
    void patchListSelectionChanged();
    void putGuiToTransmissionState( bool isTransmitting, bool sending);

    void swapButtonPressed();
    void copyButtonPressed();

    void showPreferences();

private:
    int currentPatchTransmitted;
    int currentPatchEdited;
    int patchToCopy;
    bool cancelOperation;
    bool isInTransmissionState;

    MidiPortModel *readablePortsModel;
    MidiPortModel *writablePortsModel;

    PatchListModel *patchListModel;

    QTimer *timeOutTimer;
    QTimer *midiOutTimer;
    QQueue< MidiEvent *> midiOutQueue;

    QList<QByteArray> patchDataList;
    //QMap<int, QByteArray> backupPatchesMap;
    QSet<int> dirtyPatches;

    QTableView *patchListView;
    QPushButton *requestButton;
    QPushButton *sendButton;
    ProgressWidget *progressWidget;

    QPushButton *swapButton;
    QPushButton *copyButton;

    QVBoxLayout *patchListLayout;

    QAction *showPreferencesAction;

    static char calcChecksum(const char *data, int dataLength);
};

#endif // MAINWINDOW_H
