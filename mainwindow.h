#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QQueue>
#include <QSet>

class MidiPortModel;
class QComboBox;

class PatchListModel;
class QListView;
class QPushButton;
class QVBoxLayout;
class ProgressWidget;

class MidiEvent;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(MidiPortModel *readableportsmodel, MidiPortModel *writableportsmodel, QWidget *parent = 0);
    ~MainWindow();

public slots:
    void midiEvent(MidiEvent *event);

signals:
    void readableMidiPortSelected( int clientId, int portId);
    void writableMidiPortSelected( int clientId, int portId);
    void sendMidiEvent(MidiEvent *);

private slots:
    void portsInComboChanged(int index);
    void portsOutComboChanged(int index);
    void requestAll();
    void sendAll();
    void requestPatch(int patchIndex);
    void sendPatch(int patchIndex, bool sendToTmpArea = true);

    void parameterChanged(int offset, int length);

    void timeout();
    void midiOutTimeOut();
    void cancelTransmission();
    void patchListDoubleClicked(const QModelIndex& idx);
    void putGuiToTransmissionState( bool isTransmitting, bool sending);
private:
    int currentPatchTransmitted;
    int currentPatchEdited;
    bool cancelOperation;
    bool isInTransmissionState;

    PatchListModel *patchListModel;

    QTimer *timeOutTimer;
    QTimer *midiOutTimer;
    QQueue< MidiEvent *> midiOutQueue;

    QList<QByteArray> patchDataList;
    QSet<int> dirtyPatchesIndexSet;

    QComboBox *portsInCombo;
    QComboBox *portsOutCombo;
    QListView *patchListView;
    QPushButton *requestButton;
    QPushButton *sendButton;
    ProgressWidget *progressWidget;

    QVBoxLayout *patchListLayout;

    static char calcChecksum(const char *data, int dataLength);
};

#endif // MAINWINDOW_H
