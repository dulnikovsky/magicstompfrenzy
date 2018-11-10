#include "midiapplication.h"

#ifdef Q_OS_LINUX
#include <alsa/asoundlib.h>
#endif
#ifdef Q_OS_MACOS
#include <AudioToolbox/AudioToolbox.h>
#endif

#include "midievent.h"
#ifdef Q_OS_LINUX
#include "midiinthread.h"
#include "midisender.h"
#endif
#include "midiportmodel.h"

#include <QtDebug>

#ifdef Q_OS_MAC
void MIDIEngineNotifyProc(const MIDINotification *message, void *refCon)
{
    MidiApplication *midiApp = static_cast< MidiApplication *>( refCon);
    if( message->messageID == kMIDIMsgObjectAdded || message->messageID == kMIDIMsgObjectRemoved)
    {
        const MIDIObjectAddRemoveNotification *addRemoveNotify = reinterpret_cast< const MIDIObjectAddRemoveNotification*>(message);
        if(addRemoveNotify->childType == kMIDIObjectType_Source)
        {
            midiApp->onPortClientPortStatusChanged( addRemoveNotify->child, message->messageID==kMIDIMsgObjectAdded?true:false);
        }
        else if(addRemoveNotify->childType == kMIDIObjectType_Destination)
        {
            midiApp->onPortClientPortStatusChanged( addRemoveNotify->child, message->messageID==kMIDIMsgObjectAdded?true:false);
        }
    }
    qDebug("MIDI Notify, messageId=%d,", message->messageID);
}

static MidiEvent *midievent = nullptr;
void MIDIEngineReadProc(const MIDIPacketList *pktlist, void *arg, void *connRefCon)
{
    Q_UNUSED(connRefCon)

    const MIDIPacket *packet = pktlist->packet;
    for (unsigned int i=0; i < pktlist->numPackets; i++)
    {
        //quint32 port = ev->source.port;
        //port |= static_cast<quint32>(ev->source.client) << 8;
       // midisysexevent->setPort(port);

        if( midievent != nullptr)
        {
            QByteArray *data = midievent->sysExData();
            data->append( reinterpret_cast< const char *>( & (packet->data[0])), static_cast<int>( packet->length) );
            if( static_cast< unsigned char>( packet->data[packet->length-1]) != 0xF7 )
            {
                continue;
            }
        }

        if( packet->data[0] == 0xFE)
            continue;


        if( packet->data[0] == 0xF0 )
        {
            Q_ASSERT( midievent == nullptr);
            midievent = new MidiEvent(static_cast<QEvent::Type>(MidiEvent::SysEx));
            QByteArray *data = midievent->sysExData();
            data->append( reinterpret_cast< const char *>( & (packet->data[0])), static_cast<int>( packet->length) );
            if( static_cast< unsigned char>( packet->data[packet->length-1]) != 0xF7 )
            {
                continue;
            }
        }
        else if(midievent == nullptr)
        {
            midievent = new MidiEvent(static_cast<QEvent::Type>(MidiEvent::Common));
        }
        else
        {
             Q_ASSERT( midievent != nullptr);
        }

        if( midievent->type() == static_cast<QEvent::Type>(MidiEvent::SysEx))
            qDebug() << midievent->sysExData()->toHex(',');
        QApplication::postEvent( static_cast< QObject *>(arg), midievent);
        midievent = nullptr;

        //fprintf(stderr,"MIDI Read, Channel=%d, Command=%X, data1=%d, data2=%d\n", (mevent.status & 0x0F) +1 , mevent.status >> 4, mevent.data1, mevent.data2);
    }
}

static MIDISysexSendRequest sysexReq;
void sysexCompletionProc(MIDISysexSendRequest *req)
{
    Q_UNUSED(req)
}

#endif

MidiApplication::MidiApplication(int &argc, char **argv)
    :QApplication( argc, argv)
{
    int  midiEventType;
    midiEventType = QEvent::registerEventType(MidiEvent::Common);
    Q_ASSERT(midiEventType==MidiEvent::Common);
    midiEventType = QEvent::registerEventType(MidiEvent::SysEx);
    Q_ASSERT(midiEventType==MidiEvent::SysEx);

    qRegisterMetaType<MidiClientPortId>("MidiClientPortId");

    midiSystemInit();

#ifdef Q_OS_LINUX
    midiInThread = new MidiInThread(handle, this);
    connect(midiInThread, SIGNAL(portClientPortStatusChanged(MidiClientPortId,bool)), this, SLOT(onPortClientPortStatusChanged(MidiClientPortId,bool)));
    connect(midiInThread, SIGNAL(portConnectionStatusChanged(MidiClientPortId,MidiClientPortId,bool)),
            this, SLOT(onPortConnectionStatusChanged(MidiClientPortId,MidiClientPortId,bool)));
    midiInThread->start();

    midiSender = new MidiSender(handle, thisOutPort);

    midiOutThread = new QThread(this);
    midiSender->moveToThread(midiOutThread);
    midiOutThread->start();
#endif
#ifdef Q_OS_MACOS
    MIDIInputPortCreate(handle, CFSTR("In Port"), MIDIEngineReadProc, this, &thisInPort);
    MIDIOutputPortCreate(handle, CFSTR("Out Port"),  &thisOutPort);
#endif

    readablePortsModel = new MidiPortModel(handle, MidiPortModel::ReadablePorts, this);
    readablePortsModel->scan();
    writablePortsModel = new MidiPortModel(handle, MidiPortModel::WritablePorts, this);
    writablePortsModel->scan();

    connect(this, SIGNAL(aboutToQuit()), this, SLOT(isQuitting()));

#if defined(QT_DEBUG) && defined(Q_OS_LINUX)
    if(argc > 2)
    {
        bool okclient, okport;
        int client = QString(argv[1]).toInt( &okclient);
        int port = QString(argv[2]).toInt( &okport);
        if( okclient && okport  )
            changeReadableMidiPortStatus( MidiClientPortId (client, port), true);
    }
    if(argc > 4)
    {
        bool okclient, okport;
        int client = QString(argv[3]).toInt( &okclient);
        int port = QString(argv[4]).toInt( &okport);
        if( okclient && okport  )
            changeWritebleeMidiPortStatus(MidiClientPortId (client, port), true);
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
    return QApplication::event(e);
}


void  MidiApplication::midiSystemInit()
{
#ifdef Q_OS_LINUX

    int err;
    err = snd_seq_open(&handle, "default", SND_SEQ_OPEN_DUPLEX, 0);

    snd_seq_set_client_name(handle, "MagicstompFrenzy");

    int inPort = snd_seq_create_simple_port(handle, "MagicstompFrenzy IN",
                                            SND_SEQ_PORT_CAP_WRITE|SND_SEQ_PORT_CAP_SUBS_WRITE, SND_SEQ_PORT_TYPE_MIDI_GENERIC | SND_SEQ_PORT_TYPE_APPLICATION);
    int outPort = snd_seq_create_simple_port(handle, "MagicstompFrenzy OUT",
                                             SND_SEQ_PORT_CAP_READ|SND_SEQ_PORT_CAP_SUBS_READ, SND_SEQ_PORT_TYPE_MIDI_GENERIC );

    thisInPort = MidiClientPortId( snd_seq_client_id(handle), inPort);
    thisOutPort = MidiClientPortId( snd_seq_client_id(handle), outPort);

    // Subscribe to the announce port.
    snd_seq_port_subscribe_t* subs;
    snd_seq_port_subscribe_alloca(&subs);
    snd_seq_addr_t announce_sender;
    snd_seq_addr_t announce_dest;
    announce_sender.client = SND_SEQ_CLIENT_SYSTEM;
    announce_sender.port = SND_SEQ_PORT_SYSTEM_ANNOUNCE;
    announce_dest.client = snd_seq_client_id(handle);
    announce_dest.port = thisInPort.portId();
    snd_seq_port_subscribe_set_sender(subs, &announce_sender);
    snd_seq_port_subscribe_set_dest(subs, &announce_dest);
    err = snd_seq_subscribe_port(handle, subs);
    if (err != 0)
    {
        puts ("snd_seq_subscribe_port on the announce port fails: ");
    }
#endif
#ifdef Q_OS_MACOS
    MIDIClientCreate(CFSTR("MagicstompFrenzy"), MIDIEngineNotifyProc, this, &handle);
#endif
}

bool MidiApplication::changeReadableMidiPortStatus( MidiClientPortId mcpId, bool connect)
{
    return readablePortsModel->connectPorts(mcpId, thisInPort, connect);
}

bool MidiApplication::changeWritebleeMidiPortStatus( MidiClientPortId mcpId, bool connect)
{
    return writablePortsModel->connectPorts(thisOutPort, mcpId, connect);
}
void MidiApplication::sendMidiEvent(MidiEvent *ev)
{
#ifdef Q_OS_LINUX
    postEvent( midiSender, ev);
#endif
#ifdef Q_OS_MACOS
    if( ev->type() == static_cast< QEvent::Type>( MidiEvent::SysEx))
    {
        QSet<MidiClientPortId>::const_iterator iter = writablePortsModel->ConnectionsSet().constBegin();
        while (iter != writablePortsModel->ConnectionsSet().constEnd())
        {
            sysexReq.bytesToSend = static_cast< unsigned int>(ev->sysExData()->size());
            sysexReq.complete = false;
            sysexReq.completionProc = sysexCompletionProc;
            sysexReq.completionRefCon = nullptr;
            sysexReq.data = reinterpret_cast<const Byte *>(ev->sysExData()->constData());
            sysexReq.destination = *iter;
            MIDISendSysex( & sysexReq);
            MIDIFlushOutput( *iter);
            ++iter;
        }
    }
#endif
}

void MidiApplication::onPortConnectionStatusChanged(MidiClientPortId srcId, MidiClientPortId destId, bool isConnected)
{
    if(destId == thisInPort)
        readablePortsModel->connectPorts(srcId, destId, isConnected);
    else if(srcId == thisOutPort)
        writablePortsModel->connectPorts( srcId, destId, isConnected);
}
void MidiApplication::onPortClientPortStatusChanged(MidiClientPortId mpId, bool isExisting)
{
#ifdef Q_OS_MACOS
    // In MacOS there is not notification on disconecting before removeing a connected midi client
    if( !isExisting)
    {
        if(readablePortsModel->ConnectionsSet().contains(mpId))
            onPortConnectionStatusChanged( mpId, thisInPort, false);
        else if(writablePortsModel->ConnectionsSet().contains(mpId))
            onPortConnectionStatusChanged( thisOutPort, mpId, false);
    }
#endif
    readablePortsModel->scan();
    writablePortsModel->scan();
}

void MidiApplication::isQuitting()
{
#ifdef Q_OS_LINUX
    midiInThread->terminate();
    midiInThread->wait();

    midiOutThread->quit();
    midiOutThread->wait();

    snd_seq_close(handle);
#endif
#ifdef Q_OS_MACOS
    MIDIPortDispose(thisInPort);
    MIDIPortDispose(thisOutPort);
#endif
}
