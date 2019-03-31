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
#ifndef MIDIEVENT_H
#define MIDIEVENT_H

#include <QEvent>
#include "userevents.h"

class MidiEvent : public QEvent
{
    Q_GADGET
public:

    enum MidiEventType { NoteOff=0x08, NoteOn, PolyphonicKeyPressure, ControlChange, ProgramChange, ChannelPressure, PitchBend, SystemCommon };

    explicit MidiEvent(Type type) : QEvent(type), dataUnion{nullptr}, port(0) {}

    ~MidiEvent();

    bool isValid() const
    {
        if(type()==(int)UserEventTypes::MidiCommon)
            return ( !(dataUnion.status & 0x80));
        else
            return dataUnion.dataArray!=nullptr;
    }

    inline MidiEventType midiType() const { return static_cast<MidiEventType> (dataUnion.status>>4); }

    inline quint8 Status() const { return dataUnion.status >> 4; }
    inline quint8 Channel() const { return dataUnion.status & 0x0F; }

    inline quint8 Data1() const { return dataUnion.data1; }
    inline quint8 Data2() const { return dataUnion.data2; }

    inline void setStatusByte( quint8 status) { dataUnion.status = status; }
    inline void setData1( quint8 data) { dataUnion.data1 = data; }
    inline void setData2( quint8 data) { dataUnion.data2 = data; }

    inline quint32 Port() const { return port; }
    inline void setPort(quint32 val) { port=val; }

    QByteArray* sysExData()
    {
        Q_ASSERT(type()==(int)UserEventTypes::MidiSysEx);

        if(dataUnion.dataArray == nullptr)
            dataUnion.dataArray = new QByteArray();
        return dataUnion.dataArray;
    }

private:
    union DataUnion
    {
        QByteArray *dataArray;
        struct
        {
            quint8 status;
            quint8 data1;
            quint8 data2;
        };
    };
    DataUnion dataUnion;
    quint32 port;
};

#endif // MIDIEVENT_H
