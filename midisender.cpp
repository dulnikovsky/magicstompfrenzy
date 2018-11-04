#include "midisender.h"

#include "midievent.h"

#ifdef Q_OS_LINUX
#include <alsa/asoundlib.h>
#endif

#include <QApplication>
#include <QThread>
#include <QDebug>

#include <QCoreApplication>

bool MidiSender::event(QEvent *e)
{
#ifdef Q_OS_LINUX
    MidiEvent *me = dynamic_cast<MidiEvent *>(e);
    if(me && me->type()==static_cast<QEvent::Type>(MidiEvent::SysEx))
    {
        snd_seq_event_t ev;
        snd_seq_ev_clear(&ev);
        snd_seq_ev_set_source(&ev, outport);
        snd_seq_ev_set_subs(&ev);
        snd_seq_ev_set_direct(&ev);

        snd_seq_ev_set_variable(&ev, me->sysExData()->size(), (void * )me->sysExData()->constData() );
        ev.type=SND_SEQ_EVENT_SYSEX;

        //qDebug() << me->sysExData()->toHex(',') << "\n";

        int ret;

        ret = snd_seq_event_output(handle, &ev);
        if(ret < 0)
        {
            qDebug() << "Error at snd_seq_event_output";
        }
        ret = snd_seq_drain_output(handle);
        if(ret < 0)
        {
            qDebug() << "Error at snd_seq_drain_output";
        }
        me->accept();
    }
#endif
    return QObject::event(e);
}
