#ifndef USEREVENTS_H
#define USEREVENTS_H

#include <QEvent>

enum UserEventTypes {

    MidiCommon = QEvent::User,
    MidiSysEx,
    MidiHeaderUsedEvent
};

#endif // USEREVENTS_H
