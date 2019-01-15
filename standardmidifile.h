#ifndef STANDARDMIDIFILE_H
#define STANDARDMIDIFILE_H

#include <QFile>
#include "midievent.h"

typedef QList< MidiEvent *> MidiEventList;

class StandardMidiFile : protected QFile
{
    Q_OBJECT
public:
    StandardMidiFile() : QFile() {}
    StandardMidiFile(const QString &name) : QFile(name) {}
#ifndef QT_NO_QOBJECT
    explicit StandardMidiFile(QObject *parent) : QFile( parent) {}
    StandardMidiFile(const QString &name, QObject *parent) : QFile( name, parent) {}
#endif

    bool open(OpenMode mode) override;
    void close() override { return QFile::close(); }

    quint32 TrackNum() const { return ntracks; }
    void setTrackNum(quint32 val) { ntracks=val; }
    bool readNextTrack(MidiEventList &midieventlist);

    void writeTrack(QQueue< MidiEvent *> &eventQueue);

    bool isSMTPEFrameDivision() const { return division & 0x8000; }
    quint16 ticksPerQuarterNote() const { return division; }
    void setTicksPerQuarterNote(quint16 val) { division=val; }
    unsigned char ticksPerSMTPEUnits() const { return division & 0x000F; }
    unsigned char SMTPEFramesPerSecond() const { return (division & 0x7F00) >> 8; }

    enum SMFFormat
    {
        Format0,
        Format1,
        Format2
    };

    SMFFormat Format() const { return format; }

private:
    const char SMFHeader[4] = { 'M', 'T', 'h', 'd' };
    const char SMFTrackHeader[4] = { 'M', 'T', 'r', 'k' };

    SMFFormat format{Format0};
    quint32 ntracks{0};
    quint16 division{0};

    quint32 readVariableLengthQuantity( unsigned int *bytesRead);
    QByteArray getVariableLengthQuantity(quint32 val);
    bool readMetaData(unsigned int *bytesRead, QByteArray &arr);
    bool readSysExData(unsigned int *bytesRead, QByteArray &arr);

};

#endif // STANDARDMIDIFILE_H
