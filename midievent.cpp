#include "midievent.h"

MidiEvent::~MidiEvent()
{
    if( type() == (int)SysEx && dataUnion.dataArray!=nullptr)
        delete dataUnion.dataArray;
}
