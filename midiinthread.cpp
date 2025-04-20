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
#include "midiinthread.h"

#include "midievent.h"

#include <QApplication>
#include <QDebug>


MidiInThread::MidiInThread(snd_seq_t *handle, QObject *parent)
    :QThread(parent), handle(handle)
{
    int count = snd_seq_poll_descriptors_count(handle, POLLIN);
    if(count != 1) {
        qWarning("Poll descriptor count higher than 1????");
    }
    snd_seq_poll_descriptors(handle, &seqPollFd, 1, POLLIN);
    seqPollFd.events = POLLIN;
    seqPollFd.revents = 0;
}

void MidiInThread::run()
{
#ifdef Q_OS_LINUX
    snd_seq_event_t *ev;
    MidiEvent *midievent = nullptr;
    int pollret;

    while( doRun) {
        pollret = poll(&seqPollFd, 1, 100); /* use a 100 milliseconds timeout */
        if (pollret < 0) {
            qWarning("Poll error. Exiting thread");
            break;
        }
        if(pollret == 0) { //timeout
            continue;
        }
        while (snd_seq_event_input(handle, &ev) >= 0)
        {
            if(ev->type==SND_SEQ_EVENT_SYSEX)
            {
                QByteArray arr(static_cast<char *>(ev->data.ext.ptr), static_cast<int>(ev->data.ext.len));
                if( midievent != nullptr)
                {
                    QByteArray *data = midievent->sysExData();
                    data->append(arr);
                }
                else
                {
                    midievent = new MidiEvent(static_cast<QEvent::Type>(UserEventTypes::MidiSysEx));
                    quint32 port = ev->source.port;
                    port |= static_cast<quint32>(ev->source.client) << 8;
                    midievent->setPort(port);
                    QByteArray *data = midievent->sysExData();
                    *data=arr;
                }
                if(static_cast<unsigned char>(arr.at(arr.size()-1)) == 0xF7)
                {
                    QApplication::postEvent(parent(), midievent);
                    midievent=nullptr;
                }
            }
            else if(ev->type==SND_SEQ_EVENT_PGMCHANGE)
            {
                midievent = new MidiEvent(static_cast<QEvent::Type>(UserEventTypes::MidiCommon));
                midievent->setStatusByte( (static_cast< unsigned char>(MidiEvent::MidiEventType::ProgramChange) << 4) | ( ev->data.raw8.d[0] & 0x0F ) );
                midievent->setData1( ev->data.raw8.d[8] );
                midievent->setData2(0);
                QApplication::postEvent(parent(), midievent);
            }
            else if(ev->type==SND_SEQ_EVENT_CONTROLLER)
            {
                midievent = new MidiEvent(static_cast<QEvent::Type>(UserEventTypes::MidiCommon));
                midievent->setStatusByte( (static_cast< unsigned char>(MidiEvent::MidiEventType::ControlChange) << 4) | ( ev->data.raw8.d[0] & 0x0F ) );
                midievent->setData1( ev->data.raw8.d[4]);
                midievent->setData2( ev->data.raw8.d[8]);
                QApplication::postEvent(parent(), midievent);
            }
            else if(ev->type==SND_SEQ_EVENT_PORT_SUBSCRIBED)
            {
                snd_seq_connect conn = ev->data.connect;
                emit portConnectionStatusChanged( MidiClientPortId(conn.sender.client, conn.sender.port),
                                                  MidiClientPortId(conn.dest.client, conn.dest.port),
                                                  true);

            }
            else if(ev->type==SND_SEQ_EVENT_PORT_UNSUBSCRIBED)
            {
                snd_seq_connect conn = ev->data.connect;
                emit portConnectionStatusChanged( MidiClientPortId(conn.sender.client, conn.sender.port),
                                                  MidiClientPortId(conn.dest.client, conn.dest.port),
                                                  false);

            }
            else if(ev->type==SND_SEQ_EVENT_CLIENT_START)
            {
                snd_seq_addr_t addr = ev->data.addr;
                emit portClientPortStatusChanged(MidiClientPortId(addr.client, addr.port), true);
            }
            else if(ev->type==SND_SEQ_EVENT_CLIENT_EXIT)
            {
                snd_seq_addr_t addr = ev->data.addr;
                emit portClientPortStatusChanged(MidiClientPortId(addr.client, addr.port), false);
            }
            else if(ev->type==SND_SEQ_EVENT_SENSING)
            {
                //qDebug("got SND_SEQ_EVENT_SENSING");
            }

            //qDebug("MIDI Event. Type = %d",ev->type);
            snd_seq_free_event(ev);
        }
    }
#endif
}
