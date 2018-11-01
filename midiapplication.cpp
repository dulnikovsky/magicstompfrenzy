#include "midiapplication.h"

#ifdef Q_OS_LINUX
#include <alsa/asoundlib.h>
#endif

#include "midievent.h"
#include "midiinthread.h"
#include "midisender.h"
#include "midiportmodel.h"

MidiApplication::MidiApplication(int &argc, char **argv)
    :QApplication( argc, argv)
{
    int  midiEventType;
    midiEventType = QEvent::registerEventType(MidiEvent::Common);
    Q_ASSERT(midiEventType==MidiEvent::Common);
    midiEventType = QEvent::registerEventType(MidiEvent::SysEx);
    Q_ASSERT(midiEventType==MidiEvent::SysEx);

    handle = midiSystemInit();

    midiInThread = new MidiInThread(handle, this);
    midiInThread->start();

    midiSender = new MidiSender(handle, outport);

    midiOutThread = new QThread(this);
    midiSender->moveToThread(midiOutThread);
    midiOutThread->start();

    readablePortsModel = new MidiPortModel(handle, MidiPortModel::ReadablePorts, this);
    readablePortsModel->scan();
    writablePortsModel = new MidiPortModel(handle, MidiPortModel::WritablePorts, this);
    writablePortsModel->scan();

    connect(this, SIGNAL(aboutToQuit()), this, SLOT(isQuitting()));

#ifdef QT_DEBUG
    if(argc > 2)
    {
        bool okclient, okport;
        int client = QString(argv[1]).toInt( &okclient);
        int port = QString(argv[2]).toInt( &okport);
        if( okclient && okport  )
            connectToReadablePort( client, port);
    }
    if(argc > 4)
    {
        bool okclient, okport;
        int client = QString(argv[3]).toInt( &okclient);
        int port = QString(argv[4]).toInt( &okport);
        if( okclient && okport  )
            connectToWritablePort(client, port);
    }
#endif
}

bool MidiApplication::event(QEvent *e)
{
    MidiEvent *me = dynamic_cast<MidiEvent *>(e);
    if(me)
    {
        emit midiEventReceived(me);
    }
    QApplication::event(e);
}

snd_seq_t * MidiApplication::midiSystemInit()
{
    snd_seq_t *handle;

    int err;
    err = snd_seq_open(&handle, "default", SND_SEQ_OPEN_DUPLEX, 0);

    snd_seq_set_client_name(handle, "MagicstompFrenzy");

    inport = snd_seq_create_simple_port(handle, "MagicstompFrenzy IN", SND_SEQ_PORT_CAP_WRITE|SND_SEQ_PORT_CAP_SUBS_WRITE, SND_SEQ_PORT_TYPE_MIDI_GENERIC | SND_SEQ_PORT_TYPE_APPLICATION);
    outport = snd_seq_create_simple_port(handle, "MagicstompFrenzy OUT", SND_SEQ_PORT_CAP_READ|SND_SEQ_PORT_CAP_SUBS_READ, SND_SEQ_PORT_TYPE_MIDI_GENERIC );

    // Subscribe to the announce port.
    snd_seq_port_subscribe_t* subs;
    snd_seq_port_subscribe_alloca(&subs);
    snd_seq_addr_t announce_sender;
    snd_seq_addr_t announce_dest;
    announce_sender.client = SND_SEQ_CLIENT_SYSTEM;
    announce_sender.port = SND_SEQ_PORT_SYSTEM_ANNOUNCE;
    announce_dest.client = snd_seq_client_id(handle);
    announce_dest.port = inport;
    snd_seq_port_subscribe_set_sender(subs, &announce_sender);
    snd_seq_port_subscribe_set_dest(subs, &announce_dest);
    err = snd_seq_subscribe_port(handle, subs);
    if (err != 0)
    {
        puts ("snd_seq_subscribe_port on the announce port fails: ");
    }
    return handle;
}

bool MidiApplication::connectToReadablePort( int clientId, int portId)
{
    snd_seq_addr_t sender, dest;
    snd_seq_port_subscribe_t* subs;
    snd_seq_port_subscribe_alloca(&subs);

    dest.client = snd_seq_client_id(handle);
    dest.port = inport;
    sender.client = clientId;
    sender.port = portId;

    snd_seq_port_subscribe_set_sender(subs, &sender);
    snd_seq_port_subscribe_set_dest(subs, &dest);
    return snd_seq_subscribe_port(handle, subs);
}

bool MidiApplication::connectToWritablePort( int clientId, int portId)
{
    snd_seq_addr_t sender, dest;
    snd_seq_port_subscribe_t* subs;
    snd_seq_port_subscribe_alloca(&subs);

    sender.client = snd_seq_client_id(handle);
    sender.port = outport;
    dest.client = clientId;
    dest.port = portId;

    snd_seq_port_subscribe_set_sender(subs, &sender);
    snd_seq_port_subscribe_set_dest(subs, &dest);
    return snd_seq_subscribe_port(handle, subs);
}
void MidiApplication::sendMidiEvent(MidiEvent *ev)
{
    postEvent( midiSender, ev);
}

void MidiApplication::isQuitting()
{
    midiInThread->terminate();
    midiInThread->wait();

    midiOutThread->quit();
    midiOutThread->wait();

    snd_seq_close(handle);
}
