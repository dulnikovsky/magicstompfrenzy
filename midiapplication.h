#ifndef MIDIAPPLICATION_H
#define MIDIAPPLICATION_H

#include <QApplication>

#ifdef Q_OS_LINUX
typedef struct _snd_seq snd_seq_t;
typedef snd_seq_t* MidiClientHandle;
#endif

#ifdef Q_OS_MACOS
typedef quint32 MidiClientHandle;
#endif


class MidiInThread;
class MidiSender;
class MidiPortModel;
class MidiEvent;

class MidiApplication : public QApplication
{
    Q_OBJECT
public:
    MidiApplication(int &argc, char **argv);

    MidiPortModel *ReadablePortsModel() { return readablePortsModel;}
    MidiPortModel *WritablePortsModel() { return writablePortsModel;}

    bool event(QEvent *) override;

signals:
    void midiEventReceived(MidiEvent *);

public slots:
    bool connectToReadablePort( int clientId, int portId);
    bool connectToWritablePort( int clientId, int portId);

    void sendMidiEvent(MidiEvent *ev);

private slots:
    void isQuitting();

private:
    MidiInThread *midiInThread;
    QThread *midiOutThread;
    MidiSender *midiSender;

    MidiPortModel *readablePortsModel;
    MidiPortModel *writablePortsModel;

    MidiClientHandle handle;

    void midiSystemInit();

    unsigned int inPort;
    unsigned int outPort;
    unsigned int outDest;
};

#endif // MIDIAPPLICATION_H
