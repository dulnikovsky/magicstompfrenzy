#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QQueue>

typedef struct _snd_seq snd_seq_t;

class MidiPortModel;
class QComboBox;

class MidiInThread;
class MidiSender;
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
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    bool event(QEvent *event) override;
protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    void portsInComboChanged(int index);
    void portsOutComboChanged(int index);
    void requestAll();
    void sendAll();
    void requestPatch(int patchIndex);
    void sendPatch(int patchIndex, bool sendToTmpArea = true);

    void timeout();
    void midiOutTimeOut();
    void cancelTransmission();
    void patchListDoubleClicked(const QModelIndex& idx);
    void putGuiToTransmissionState( bool isTransmitting, bool sending);
private:
    int currentPatchTransmitted;
    bool cancelOperation;
    bool isInTransmissionState;
    MidiInThread *midiInThread;
    QThread *midiOutThread;
    MidiSender *midiSender;

    PatchListModel *patchListModel;

    MidiPortModel *portinmodel;
    MidiPortModel *portoutmodel;

    QTimer *timeOutTimer;
    QTimer *midiOutTimer;
    QQueue< MidiEvent *> midiOutQueue;

    QList<QByteArray> patchDataList;
    const int numOfPatches = 99;
    const int PatchCommonLength = 0x20;
    const int PatchEffectLength = 0x7F;
    const int PatchLength = PatchCommonLength+PatchEffectLength;

    QComboBox *portsInCombo;
    QComboBox *portsOutCombo;
    QListView *patchListView;
    QPushButton *requestButton;
    QPushButton *sendButton;
    ProgressWidget *progressWidget;

    QVBoxLayout *patchListLayout;

    snd_seq_t *handle;
    snd_seq_t * midiSystemInit();
    int inport;
    int outport;

    static char calcChecksum(const char *data, int dataLength);
};

#endif // MAINWINDOW_H
