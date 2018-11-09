#ifndef MIDIINTHREAD_H
#define MIDIINTHREAD_H

#include <QThread>

#include "midiportidalsa.h"

typedef struct _snd_seq snd_seq_t;

class MidiInThread : public QThread
{
    Q_OBJECT
public:
    MidiInThread(snd_seq_t *handle, QObject *parent=0);

signals:
    void portConnectionStatusChanged(MidiClientPortId src, MidiClientPortId dest, bool isConnected);
    void portClientPortStatusChanged(MidiClientPortId mpId, bool isExisting);
protected:
    void run();
private:
    snd_seq_t *handle;
};

#endif // MIDIINTHREAD_H
