#include "midiportidalsa.h"

#include <QHashFunctions>
#include <tuple>

uint qHash(const MidiPortIdAlsa &id)
{
    qint64 int64 = id.portId();
    int64 &= ((qint64)id.portId() << 32);
    return qHash( int64);
}
bool operator ==(const MidiPortIdAlsa &a, const MidiPortIdAlsa &b)
{
    return std::tie(a.client, a.port) == std::tie(b.client, b.port);
}
