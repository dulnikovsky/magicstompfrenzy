#ifndef MIDIINTHREAD_H
#define MIDIINTHREAD_H

#include <QThread>

typedef struct _snd_seq snd_seq_t;

class MidiInThread : public QThread
{
    Q_OBJECT
public:
    MidiInThread(snd_seq_t *handle, QObject *parent=0);
protected:
    void run();
private:
    snd_seq_t *handle;
};

#endif // MIDIINTHREAD_H
