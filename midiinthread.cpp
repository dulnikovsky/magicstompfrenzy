#include "midiinthread.h"

#include "midievent.h"
#include <alsa/asoundlib.h>

#include <QApplication>
#include <QDebug>


MidiInThread::MidiInThread(snd_seq_t *handle, QObject *parent)
    :QThread(parent), handle(handle)
{

}

void MidiInThread::run()
{
    snd_seq_event_t *ev;
    MidiEvent *midisysexevent=nullptr;
    while (snd_seq_event_input(handle, &ev) >= 0)
    {
        if(ev->type==SND_SEQ_EVENT_SYSEX)
        {
            QByteArray arr((char *)ev->data.ext.ptr, ev->data.ext.len);
            if( midisysexevent != nullptr)
            {
                QByteArray *data = midisysexevent->sysExData();
                data->append(arr);
            }
            else
            {
                midisysexevent = new MidiEvent(static_cast<QEvent::Type>(MidiEvent::SysEx));
                quint32 port = ev->source.port;
                port |= static_cast<quint32>(ev->source.client) << 8;
                midisysexevent->setPort(port);
                QByteArray *data = midisysexevent->sysExData();
                *data=arr;
            }
            if(static_cast<unsigned char>(arr.at(arr.size()-1)) == 0xF7)
            {
                QApplication::postEvent(parent(), midisysexevent);
                midisysexevent=nullptr;
            }
        }
        else if(ev->type==SND_SEQ_EVENT_CLIENT_EXIT)
        {
            return;
        }
        else if(ev->type==SND_SEQ_EVENT_SENSING)
        {
            //qDebug("got sensing");
        }
        else
        {
            qDebug("MIDI Event %x, %x, %x",ev->data.raw32.d[0], ev->data.raw32.d[1], ev->data.raw32.d[2]);
        }

        snd_seq_free_event(ev);
    }
}
