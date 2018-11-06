#ifndef MIDIPORTIDALSA_H
#define MIDIPORTIDALSA_H

#include <QString>

class MidiPortIdAlsa
{
public:
    MidiPortIdAlsa() {}
    MidiPortIdAlsa(const MidiPortIdAlsa &other)
    {
        client = other.client;
        port = other.port;
    }
    ~MidiPortIdAlsa() {}

    MidiPortIdAlsa(int clientId, int portId)
        : client(clientId), port(portId) {}

    int clientId() const  { return client; }
    int portId() const { return port; }

    friend bool operator ==(const MidiPortIdAlsa &a, const MidiPortIdAlsa &b);

private:
    int client;
    int port;
    QString name;
};

uint qHash(const MidiPortIdAlsa &id);

bool operator ==(const MidiPortIdAlsa &a, const MidiPortIdAlsa &b);

#endif // MIDIPORTIDALSA_H
