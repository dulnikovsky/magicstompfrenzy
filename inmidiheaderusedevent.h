#ifndef INMIDIHEADERUSEDEVENT_H
#define INMIDIHEADERUSEDEVENT_H

#include <QEvent>

typedef struct midihdr_tag *LPMIDIHDR;

class InMidiHeaderUsedEvent : public QEvent
{
    Q_GADGET
public:
    explicit InMidiHeaderUsedEvent(Type type, void *handle, LPMIDIHDR header) : QEvent(type), midiHandle(handle), midiHdr(header) {}

    void *Handle() const { return midiHandle; }
    LPMIDIHDR midiHeader() const { return midiHdr; }

private:
    void *midiHandle;
    LPMIDIHDR midiHdr;
};

#endif // INMIDIHEADERUSEDEVENT_H
