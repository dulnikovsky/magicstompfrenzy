/****************************************************************************
**
** Copyright (C) 2018 Robert Vetter.
**
** This file is part of the MagicstompFrenzy - an editor for Yamaha Magicstomp
** effect processor
**
** THIS CODE IS PROVIDED *AS IS* WITHOUT WARRANTY OF
** ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING ANY
** IMPLIED WARRANTIES OF FITNESS FOR A PARTICULAR
** PURPOSE, MERCHANTABILITY, OR NON-INFRINGEMENT.
**
** GNU General Public License Usage
** This file may be used under the terms of the GNU
** General Public License version 2.0 or (at your option) the GNU General
** Public license version 3 or any later version . The licenses are
** as published by the Free Software Foundation and appearing in the file LICENSE
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-2.0.html and
** https://www.gnu.org/licenses/gpl-3.0.html.
**/
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

typedef MidiPortIdAlsa MidiClientPortId;

uint qHash(const MidiPortIdAlsa &id);

bool operator ==(const MidiPortIdAlsa &a, const MidiPortIdAlsa &b);

#endif // MIDIPORTIDALSA_H
