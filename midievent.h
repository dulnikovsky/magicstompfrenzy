#ifndef MIDIEVENT_H
#define MIDIEVENT_H

#include <QEvent>

class MidiEvent : public QEvent
{
    Q_GADGET
public:

    enum MidiEventQtType { Common=QEvent::User, SysEx };

    enum MidiEventType { NoteOff=0x08, NoteOn, PolyphonicKeyPressure, ControlChange, ProgramChange, ChannelPressure, PitchBend, SystemCommon };

    explicit MidiEvent(Type type) : QEvent(type),dataUnion{nullptr}, port(0) {}

    ~MidiEvent()
    {
        if(type()==(int)SysEx && dataUnion.dataArray!=nullptr)
            delete dataUnion.dataArray;
    }

    bool isValid() const
    {
        if(type()==(int)Common)
            return ( !(dataUnion.status & 0x80));
        else
            return dataUnion.dataArray!=nullptr;
    }

    inline MidiEventType midiType() const { return static_cast<MidiEventType> (dataUnion.status>>4); }

    inline quint8 Status() const { return dataUnion.status & 0xF0; }
    inline quint8 Channel() const { return dataUnion.status & 0x0F; }

    inline quint32 Port() const { return port; }
    inline void setPort(quint32 val) { port=val; }

    QByteArray* sysExData()
    {
        Q_ASSERT(type()==(int)SysEx);

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
