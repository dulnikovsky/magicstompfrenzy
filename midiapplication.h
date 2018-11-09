#ifndef MIDIAPPLICATION_H
#define MIDIAPPLICATION_H

#include <QApplication>
#include <QSet>

#ifdef Q_OS_LINUX
typedef struct _snd_seq snd_seq_t;
typedef snd_seq_t* MidiClientHandle;

#include "midiportidalsa.h"
Q_DECLARE_METATYPE(MidiPortIdAlsa)

#endif

#ifdef Q_OS_MACOS
typedef quint32 MidiClientHandle;
typedef quint32 MidiClientPortId;
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
    bool changeReadableMidiPortStatus( MidiClientPortId mcpId, bool connect );
    bool changeWritebleeMidiPortStatus( MidiClientPortId mcpId, bool connect );

    void sendMidiEvent(MidiEvent *ev);

private slots:
    void onPortConnectionStatusChanged(MidiClientPortId srcId, MidiClientPortId destId, bool isConnected);
    void onPortClientPortStatusChanged(MidiClientPortId mpId, bool isExisting);

    void isQuitting();

private:
    MidiInThread *midiInThread;
    QThread *midiOutThread;
    MidiSender *midiSender;

    MidiPortModel *readablePortsModel;
    MidiPortModel *writablePortsModel;

    MidiClientHandle handle;

    void midiSystemInit();

    MidiClientPortId thisInPort;
    MidiClientPortId thisOutPort;
};

#endif // MIDIAPPLICATION_H
