#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QQueue>
#include <QSet>
//#include <QMap>

class MidiPortModel;
class QComboBox;

class PatchListModel;
class QTableView;
class QPushButton;
class QVBoxLayout;
class ProgressWidget;

class MidiEvent;

class QItemSelection;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(MidiPortModel *readableportsmodel, MidiPortModel *writableportsmodel, QWidget *parent = 0);

public slots:
    void midiEvent(MidiEvent *event);

protected:
    void closeEvent(QCloseEvent *event) override;

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
    void patchListSelectionChanged(const QItemSelection &, const QItemSelection &);
    void putGuiToTransmissionState( bool isTransmitting, bool sending);

    void swapButtonPressed();
private:
    int currentPatchTransmitted;
    int currentPatchEdited;
    int patchToCopy;
    bool cancelOperation;
    bool isInTransmissionState;

    PatchListModel *patchListModel;

    QTimer *timeOutTimer;
    QTimer *midiOutTimer;
    QQueue< MidiEvent *> midiOutQueue;

    QList<QByteArray> patchDataList;
    //QMap<int, QByteArray> backupPatchesMap;
    QSet<int> dirtyPatches;

    QComboBox *portsInCombo;
    QComboBox *portsOutCombo;
    QTableView *patchListView;
    QPushButton *requestButton;
    QPushButton *sendButton;
    ProgressWidget *progressWidget;

    QPushButton *swapButton;
    QPushButton *copyButton;
    QPushButton *pasteButton;
    QPushButton *resetButton;

    QVBoxLayout *patchListLayout;

    static char calcChecksum(const char *data, int dataLength);
};

#endif // MAINWINDOW_H
