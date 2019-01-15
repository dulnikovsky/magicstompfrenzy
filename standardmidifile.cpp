#include "standardmidifile.h"
#include "midievent.h"
#include <QtEndian>
#include <QQueue>

bool StandardMidiFile::open(OpenMode mode)
{
    bool ret = false;
    if((mode & QIODevice::ReadOnly) == QIODevice::ReadOnly)
    {
        ret = QFile::open(mode);
        if(ret == false)
            return ret;

        char buffer[4];
        qint64 len = readData(buffer, 4);
        if(len != 4 || strncmp( SMFHeader, buffer, 4) != 0)
        {
            close();
            return false;
        }
        len = readData(buffer, 4);
        if(len != 4 || qFromBigEndian(*(reinterpret_cast<quint32 *>(buffer))) != 6)
        {
            close();
            return false;
        }
        len = readData(buffer, 2);
        if(len != 2 )
        {
            close();
            return false;
        }
        quint16 formatInt = qFromBigEndian(*(reinterpret_cast<quint16 *>(buffer)));
        if(formatInt > 2 )
            return false;
        format = static_cast<SMFFormat>(formatInt);
        len = readData(buffer, 2);
        if(len != 2 )
        {
            close();
            return false;
        }
        ntracks = qFromBigEndian(*(reinterpret_cast<quint16 *>(buffer)));
        len = readData(buffer, 2);
        if(len != 2 )
        {
            close();
            return false;
        }
        division = qFromBigEndian(*(reinterpret_cast<quint16 *>(buffer)));
    }
    else if((mode & QIODevice::WriteOnly) == QIODevice::WriteOnly)
    {
        ret = QFile::open(mode);
        if(ret == false)
            return ret;

        write(SMFHeader, 4);
        char buffer[4];
        qToBigEndian(static_cast<qint32>(6), buffer);
        write(buffer, 4);
        qToBigEndian(static_cast<qint16>(format), buffer);
        write(buffer, 2);
        qToBigEndian(static_cast<qint16>(ntracks), buffer);
        write(buffer, 2);
        qToBigEndian(static_cast<qint16>(division), buffer);
        write(buffer, 2);
    }
    return ret;
}

bool StandardMidiFile::readNextTrack( MidiEventList &midieventlist)
{
    if(! isOpen())
        return false;

    char buffer[4];
    qint64 len = readData(buffer, 4);
    if(len != 4 || strncmp( SMFTrackHeader, buffer, 4) != 0)
    {
        return false;
    }
    len = readData(buffer, 4);
    if(len != 4)
    {
        return false;
    }
    quint32 trackLenght = qFromBigEndian(*(reinterpret_cast<quint32 *>(buffer)));
    quint32 bytesReadTotal = 0;
    char lastStatus;
    while(bytesReadTotal < trackLenght)
    {
        unsigned int bytesRead;

        quint32 deltaTime = readVariableLengthQuantity( &bytesRead);
        if(bytesRead == 0)
            break;

        bytesReadTotal += bytesRead;

        char statusByte;
        len = readData( &statusByte, 1);
        if(len == 0)
            break;

        bytesReadTotal++;

        if(statusByte == static_cast< char>(0xFF))
        {
            QByteArray arr;
            readMetaData( &bytesRead, arr);
            if(bytesRead == 0)
                break;
            //midieventlist.append(MidiEvent(deltaTime, statusByte, arr));
            bytesReadTotal += bytesRead;
        }
        else if(statusByte == static_cast< char>(0xF0))
        {
            QByteArray arr;
            readSysExData( &bytesRead, arr);
            if(bytesRead == 0)
                break;
            MidiEvent *midiev = new MidiEvent(static_cast<QEvent::Type>(UserEventTypes::MidiSysEx));
            QByteArray *reqArr = midiev->sysExData();
            reqArr->append(statusByte);
            reqArr->append(arr);

            midieventlist.append( midiev);
            bytesReadTotal += bytesRead;
        }
        else
        {
            char data1;
            char data2;
            bool lastStatusUsed;
            if((statusByte & 0x80) != 0x80)
            {
                data1 = statusByte;
                statusByte = lastStatus;
                lastStatusUsed = true;
            }
            else
            {
                lastStatus = statusByte;
                lastStatusUsed = false;
            }

            len = 0;

            if(((statusByte & 0xF0) == 0xC0) || ((statusByte & 0xF0) == 0xD0))
            {
                if(! lastStatusUsed )
                {
                    len = readData(buffer, 1);
                    if(len == 0)
                        break;
                    data1 = buffer[0];
                }
            }
            else
            {
                if(! lastStatusUsed )
                {
                    len = readData(buffer, 2);
                    if(len != 2)
                        break;
                    data1 = buffer[0];
                    data2 = buffer[1];
                }
                else
                {
                    len = readData(buffer, 1);
                    if(len == 0)
                        break;
                    data2 = buffer[0];
                }
            }
            //midieventlist.append(MidiEvent(deltaTime, statusByte, data1, data2));
            bytesReadTotal += len;
        }
    }
    if( ! midieventlist.isEmpty())
    {
        if(1/*midieventlist.last().Status() == MidiEvent::System &&
                midieventlist.last().SystemStatus() == 0x0F &&
                midieventlist.last().VariableDataArray()->at(0) == 0x2F*/)
        {
            midieventlist.takeLast();
        }
        return true;
    }
    else
        return false;

    // We don't check de length as many SMF have wrong data lenght
    //return(trackLenght == bytesReadTotal);
}

void StandardMidiFile::writeTrack(QQueue< MidiEvent *> &eventQueue)
{
    write(SMFTrackHeader, 4);
    qint32 trackLen = 0;
    for (int i = 0; i < eventQueue.size(); ++i)
    {
        trackLen += 1; // delta time
        trackLen += eventQueue.at(i)->sysExData()->length();
        QByteArray varLenArr = getVariableLengthQuantity(static_cast<quint32>(eventQueue.at(i)->sysExData()->length()-1));
        trackLen += varLenArr.size();
    }

    trackLen += 4; // add end of track size

    char buffer[4];
    qToBigEndian(static_cast<qint32>(trackLen), buffer);
    write(buffer, 4);

    while (! eventQueue.isEmpty())
    {
        qToBigEndian(static_cast<qint32>(48), buffer);
        write(buffer+3, 1);

        MidiEvent *ev = eventQueue.dequeue();
        write((*ev).sysExData()->constData(), 1);
        QByteArray varLenArr = getVariableLengthQuantity(static_cast<quint32>((*ev).sysExData()->length()-1));
        write(varLenArr);
        write((*ev).sysExData()->constData()+1, (*ev).sysExData()->length()-1);
        delete ev;
    }

    // write end of track
    buffer[0] = 0;
    buffer[1] = static_cast<char>(0xFF);
    buffer[2] = 0x2F;
    buffer[3] = 0;
    write(buffer, 4);
}

quint32 StandardMidiFile::readVariableLengthQuantity(unsigned int *bytesRead)
{
    const int maxLenght = 4;
    quint32 val = 0;
    *bytesRead = 0;
    char c;
    do
    {
        qint64 len = readData(&c, 1);
        if(len == 0)
            return false;

        (*bytesRead)++;

        int bitshift = *bytesRead == 1?0:7;
        val = (val << bitshift) | (static_cast<quint32>(c & 0x7F));
    }
    while( (c & 0x80) == 0x80 && *bytesRead < maxLenght);

    return val;
}

QByteArray StandardMidiFile::getVariableLengthQuantity(quint32 val)
{
    QByteArray arr;

    const int maxLenght = 4;
    char destArray[4];
    for(int i=0, s=maxLenght-1; i<maxLenght; i++, s--)
    {
        destArray[i] = (val >> (s*8-s)) &0x7F;
    }

    int startIndex;
    for(startIndex=0; startIndex<maxLenght; startIndex++)
    {
        if(destArray[startIndex] != 0 )
            break;
    }
    if(startIndex>=maxLenght)
        startIndex=3;

    for(int i=startIndex; i<maxLenght-1; i++)
    {
        destArray[i] = destArray[i] | 0x80;
        arr.append(&destArray[i], 1);
    }
    arr.append(&destArray[3], 1);

    return arr;
}

bool StandardMidiFile::readMetaData(unsigned int *bytesRead, QByteArray &arr)
{
    char type;
    qint64 len = readData(&type, 1);
    *bytesRead = static_cast< unsigned int>(len);
    if(len != 1)
        return false;

    arr.clear();
    arr.append( type);

    unsigned int vlenRead;
    quint32 lenToRead = readVariableLengthQuantity(&vlenRead);
    if(vlenRead == 0)
        return false;

    *bytesRead = *bytesRead + vlenRead;

    arr.resize(static_cast<int>(lenToRead+1));
    len = readData(arr.data()+1, lenToRead);
    *bytesRead = *bytesRead + static_cast< unsigned int>(len);

    return true;
}

bool StandardMidiFile::readSysExData(unsigned int *bytesRead, QByteArray &array)
{
    unsigned int vlenRead;
    quint32 lenToRead = readVariableLengthQuantity(&vlenRead);
    if(vlenRead == 0)
        return false;

    *bytesRead = *bytesRead + vlenRead;

    array.resize(static_cast<int>(lenToRead));
    qint64 len = readData(array.data(), lenToRead);
    *bytesRead = *bytesRead + static_cast< unsigned int>(len);

    return true;
}
