#ifndef MIDISENDER_H
#define MIDISENDER_H

#include <QObject>

#ifdef Q_OS_LINUX
typedef struct _snd_seq snd_seq_t;
#include "midiportidalsa.h"
#endif

class MidiSender : public QObject
{
    Q_OBJECT
public:
#ifdef Q_OS_LINUX
    explicit MidiSender(snd_seq_t *handle, MidiClientPortId outport, QObject *parent = nullptr) : QObject(parent), handle(handle), outport(outport) {}
#endif
    explicit MidiSender( MidiClientPortId outport, QObject *parent = nullptr) :QObject(parent), outport(outport) {}
    bool event(QEvent *);

signals:

public slots:

private:
#ifdef Q_OS_LINUX
    snd_seq_t *handle;
#endif
    MidiClientPortId outport;

};

#endif // MIDISENDER_H
