#ifndef MIDISENDER_H
#define MIDISENDER_H

#include <QObject>

typedef struct _snd_seq snd_seq_t;
#include "midiportidalsa.h"

class MidiSender : public QObject
{
    Q_OBJECT
public:
    explicit MidiSender(snd_seq_t *handle, MidiClientPortId outport, QObject *parent = nullptr) : QObject(parent), handle(handle), outport(outport) {}

    bool event(QEvent *) override;

signals:

public slots:

private:
    snd_seq_t *handle;
    MidiClientPortId outport;
};

#endif // MIDISENDER_H
