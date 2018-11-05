#ifndef MIDIAPPLICATION_H
#define MIDIAPPLICATION_H

#include <QApplication>

#ifdef Q_OS_LINUX
typedef struct _snd_seq snd_seq_t;
typedef snd_seq_t* MidiClientHandle;

class MidiPortIdAlsa
{
public:
    MidiPortIdAlsa() {}
    MidiPortIdAlsa(const MidiPortIdAlsa &other)
    {
        client = other.client;
        port = other.port;
    }
    ~MidiPortIdAlsa() {}

    MidiPortIdAlsa(int clientId, int portId)
        : client(clientId), port(portId) {}

    int clientId() const  { return client; }
    int portId() const { return port; }

private:
    int client;
    int port;
    QString name;
};
Q_DECLARE_METATYPE(MidiPortIdAlsa)
typedef MidiPortIdAlsa MidiClientPortId;

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
    bool connectToReadablePort( MidiClientPortId mcpId );
    bool connectToWritablePort( MidiClientPortId mcpId);

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

    unsigned int thisInPort;
    unsigned int thisOutPort;
    unsigned int outDest;
};

#endif // MIDIAPPLICATION_H
