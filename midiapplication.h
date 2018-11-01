#ifndef MIDIAPPLICATION_H
#define MIDIAPPLICATION_H

#include <QApplication>

#ifdef Q_OS_LINUX
typedef struct _snd_seq snd_seq_t;
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

#ifdef Q_OS_LINUX
    snd_seq_t *handle;
    snd_seq_t * midiSystemInit();
#endif
    int inport;
    int outport;
};

#endif // MIDIAPPLICATION_H
