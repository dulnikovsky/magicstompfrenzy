/****************************************************************************
**
** Copyright (C) 2018 Robert Vetter.
**
** This file is part of the MagicstompFrenzy - an editor for Yamaha Magicstomp
** effect processor
**
** THIS CODE IS PROVIDED *AS IS* WITHOUT WARRANTY OF
** ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING ANY
** IMPLIED WARRANTIES OF FITNESS FOR A PARTICULAR
** PURPOSE, MERCHANTABILITY, OR NON-INFRINGEMENT.
**
** GNU General Public License Usage
** This file may be used under the terms of the GNU
** General Public License version 2.0 or (at your option) the GNU General
** Public license version 3 or any later version . The licenses are
** as published by the Free Software Foundation and appearing in the file LICENSE
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-2.0.html and
** https://www.gnu.org/licenses/gpl-3.0.html.
**/
#include "midiapplication.h"

#ifdef Q_OS_LINUX
#include <alsa/asoundlib.h>
#endif
#ifdef Q_OS_MACOS
#include <AudioToolbox/AudioToolbox.h>
#endif
#ifdef Q_OS_WIN
#include "inmidiheaderusedevent.h"
#include <windows.h>
#include <mmsystem.h>
#include <QThread>
#include <QMessageBox>
#endif


#include "midievent.h"
#ifdef Q_OS_LINUX
#include "midiinthread.h"
#include "midisender.h"
#endif
#include "midiportmodel.h"

#include <QtDebug>

#ifdef Q_OS_MAC
void MidiApplication::MIDIEngineNotifyProc(const MIDINotification *message, void *refCon)
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

void MidiApplication::MIDIEngineReadProc(const MIDIPacketList *pktlist, void *arg, void *connRefCon)
{
    Q_UNUSED(connRefCon)

    static MidiEvent *midiEvent;

    const MIDIPacket *packet = &pktlist->packet[0];
    for (unsigned int i=0; i < pktlist->numPackets; i++)
    {
        for(int j=0; j< static_cast<int>( packet->length); j++)
        {

            if( (packet->data[j] & 0xF8) == 0xF8 )
            { // Skip MIDI realtime messages
                continue;
            }

            if( midiEvent != nullptr)
            {
                QByteArray *data = midiEvent->sysExData();
                data->append( static_cast<char>( packet->data[j]));
                if( packet->data[j] == 0xF7 )
                {
                    QApplication::postEvent( static_cast< QObject *>(arg), midiEvent);
                    midiEvent = nullptr;
                    qDebug() << data->toHex(',');
                    continue;
                }
            }
            else if( packet->data[0] == 0xF0 )
            {
                Q_ASSERT( midiEvent == nullptr);
                midiEvent = new MidiEvent(static_cast<QEvent::Type>(UserEventTypes::MidiSysEx));
                QByteArray *data = midiEvent->sysExData();
                data->append( static_cast<char>( packet->data[j]));
            }
            else if(midiEvent == nullptr)
            {
                //handle other MIDI messages here
                if( (packet->data[0] & 0xC0) == 0xC0 )
                {
                    midiEvent = new MidiEvent(static_cast<QEvent::Type>(UserEventTypes::MidiCommon));
                    midiEvent->setStatusByte( (static_cast< unsigned char>(MidiEvent::MidiEventType::ProgramChange) << 4) | ( packet->data[0] & 0x0F ) );
                    midiEvent->setData1( packet->data[1]);
                    midiEvent->setData2(0);
                    QApplication::postEvent( static_cast< QObject *>(arg), midiEvent);
                }
                else if( (packet->data[0] & 0xB0) == 0xB0 )
                {
                    midiEvent = new MidiEvent(static_cast<QEvent::Type>(UserEventTypes::MidiCommon));
                    midiEvent->setStatusByte( (static_cast< unsigned char>(MidiEvent::MidiEventType::ControlChange) << 4) | ( packet->data[0] & 0x0F ) );
                    midiEvent->setData1( packet->data[1]);
                    midiEvent->setData2( packet->data[2]);
                    QApplication::postEvent( static_cast< QObject *>(arg), midiEvent);
                }
                midiEvent = nullptr;
                break;
            }
            else
            {
                 Q_ASSERT( midiEvent != nullptr);
            }
        }
        packet = MIDIPacketNext(packet);
        //fprintf(stderr,"MIDI Read, Channel=%d, Command=%X, data1=%d, data2=%d\n", (mevent.status & 0x0F) +1 , mevent.status >> 4, mevent.data1, mevent.data2);
    }
}

static MIDISysexSendRequest sysexReq;
void MidiApplication::sysexCompletionProc(MIDISysexSendRequest *req)
{
    Q_UNUSED(req)
}
#endif
#ifdef Q_OS_WIN
void CALLBACK MidiInProc(HMIDIIN hMidiIn, UINT wMsg, DWORD dwInstance, DWORD dwParam1, DWORD dwParam2)
{
    switch(wMsg) {
    case MIM_OPEN:
        qDebug("wMsg=MIM_OPEN");
        break;
    case MIM_CLOSE:
        qDebug("wMsg=MIM_CLOSE");
        break;
    case MIM_DATA:
        if( (dwParam1 & 0xF8) == 0xF8 )
        { // Skip MIDI realtime messages
            return;
        }
        {
            MidiEvent *midiEvent = new MidiEvent(static_cast<QEvent::Type>(UserEventTypes::MidiCommon));
            midiEvent->setStatusByte( dwParam1 & 0xFF);
            midiEvent->setData1( (dwParam1 & 0x7F00) >>8);
            midiEvent->setData2( (dwParam1 & 0x7F0000) >>16);
            QApplication::postEvent( qApp, midiEvent);
        }
        qDebug("wMsg=MIM_DATA, dwInstance=%08lx, dwParam1=%08lx, dwParam2=%08lx", dwInstance, dwParam1, dwParam2);
        break;
    case MIM_LONGDATA:
        qDebug("wMsg=MIM_LONGDATA");
        {
            LPMIDIHDR midihdr = reinterpret_cast<LPMIDIHDR>(dwParam1);
            QByteArray dataArr = QByteArray::fromRawData((char *)(midihdr->lpData), midihdr->dwBytesRecorded);
            if(midihdr->dwBytesRecorded > 2 && dataArr.at(0) == static_cast<char>(0xF0) && dataArr.at(midihdr->dwBytesRecorded - 1) == static_cast<char>(0xF7))
            {
                qDebug("Sysex. Len=%d", midihdr->dwBytesRecorded);

                MidiEvent *midiEvent = new MidiEvent(static_cast<QEvent::Type>(UserEventTypes::MidiSysEx));
                QByteArray *data = midiEvent->sysExData();
                data->append( dataArr);
                QApplication::postEvent( qApp, midiEvent);
                InMidiHeaderUsedEvent *midiheaderev = new InMidiHeaderUsedEvent(static_cast<QEvent::Type>(UserEventTypes::MidiHeaderUsedEvent), hMidiIn, midihdr);
                MidiPortModel *portmodel = reinterpret_cast<MidiPortModel *>(dwInstance);
                QApplication::postEvent( portmodel, midiheaderev);
            }
        }
        break;
    case MIM_ERROR:
        qDebug("wMsg=MIM_ERROR");
        break;
    case MIM_LONGERROR:
        qDebug("wMsg=MIM_LONGERROR");
        break;
    case MIM_MOREDATA:
        qDebug("wMsg=MIM_MOREDATA");
        break;
    default:
        qDebug("wMsg = unknown");
        break;
    }
    return;
}
#endif

MidiApplication::MidiApplication(int &argc, char **argv)
    :QApplication( argc, argv)
{
    int  midiEventType;
    midiEventType = QEvent::registerEventType(UserEventTypes::MidiCommon);
    Q_ASSERT(midiEventType==UserEventTypes::MidiCommon);
    midiEventType = QEvent::registerEventType(UserEventTypes::MidiSysEx);
    Q_ASSERT(midiEventType==UserEventTypes::MidiSysEx);
    midiEventType = QEvent::registerEventType(UserEventTypes::MidiHeaderUsedEvent);
    Q_ASSERT(midiEventType==UserEventTypes::MidiHeaderUsedEvent);

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

#if 0
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
            changeWritebleMidiPortStatus(MidiClientPortId (client, port), true);
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

    snd_seq_set_client_name(handle, applicationName().toLocal8Bit().constData());

    int inPort = snd_seq_create_simple_port(handle, applicationName().toLocal8Bit().constData(),
                                            SND_SEQ_PORT_CAP_WRITE|SND_SEQ_PORT_CAP_SUBS_WRITE, SND_SEQ_PORT_TYPE_MIDI_GENERIC | SND_SEQ_PORT_TYPE_APPLICATION);
    int outPort = snd_seq_create_simple_port(handle, applicationName().toLocal8Bit().constData(),
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
    MIDIClientCreate( CFStringCreateWithCString( kCFAllocatorDefault, applicationName().toLocal8Bit().constData(), kCFStringEncodingASCII), MIDIEngineNotifyProc, this, &handle);
#endif
}

bool MidiApplication::changeReadableMidiPortStatus( MidiClientPortId mcpId, bool connect)
{
    return readablePortsModel->connectPorts(mcpId, thisInPort, connect);
}

bool MidiApplication::changeWritebleMidiPortStatus( MidiClientPortId mcpId, bool connect)
{
    return writablePortsModel->connectPorts(thisOutPort, mcpId, connect);
}
bool MidiApplication::changeReadableMidiPortStatus( const QString &portName, bool connect )
{
    return readablePortsModel->connectPortsByName(portName, thisInPort, connect);
}

bool MidiApplication::changeWritebleMidiPortStatus( const QString &portName, bool connect )
{
    return writablePortsModel->connectPortsByName(thisOutPort, portName, connect);
}

bool MidiApplication::sendMidiEvent(MidiEvent *ev)
{
#ifdef Q_OS_LINUX
    postEvent( midiSender, ev);
#endif
#ifdef Q_OS_MACOS
    if( ev->type() == static_cast< QEvent::Type>( UserEventTypes::MidiSysEx))
    {
        ConnectionsContainer::const_iterator iter = writablePortsModel->currentConnections().constBegin();
        while (iter != writablePortsModel->currentConnections().constEnd())
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
        delete ev;
    }
#endif
#ifdef Q_OS_WIN
    if( ev->type() == static_cast< QEvent::Type>( UserEventTypes::MidiSysEx))
    {
        ConnectionsContainer::const_iterator iter = writablePortsModel->currentConnections().constBegin();
        while (iter != writablePortsModel->currentConnections().constEnd())
        {
            MIDIHDR midihdr;
            midihdr.lpData = ev->sysExData()->data();
            midihdr.dwBufferLength = ev->sysExData()->size();
            midihdr.dwFlags = 0;
            MMRESULT res = midiOutPrepareHeader((HMIDIOUT)iter.value(), &midihdr, sizeof(MIDIHDR));
            res = midiOutLongMsg( (HMIDIOUT)iter.value(), &midihdr, sizeof(MIDIHDR));
            if (res != MMSYSERR_NOERROR)
            {
                QMessageBox::critical(nullptr, tr("MIDI Error"), tr("Error sending MIDI data. Check your MIDI setup and restart the application"));
                return false;
            }
            while (MIDIERR_STILLPLAYING == midiOutUnprepareHeader((HMIDIOUT)iter.value(), &midihdr, sizeof(MIDIHDR)))
            {
                QThread::msleep(5);
            }
            ++iter;
        }
        delete ev;
    }
#endif
    return true;
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
#ifdef Q_OS_LINUX
   Q_UNUSED(mpId)
   Q_UNUSED(isExisting)
#endif
#ifdef Q_OS_MACOS
    // In MacOS there is no notification on disconecting before removing a connected midi client
    if( !isExisting)
    {
        if(readablePortsModel->currentConnections().contains(mpId))
            onPortConnectionStatusChanged( mpId, thisInPort, false);
        else if(writablePortsModel->currentConnections().contains(mpId))
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
