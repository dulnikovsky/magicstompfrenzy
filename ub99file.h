#ifndef UB99FILE_H
#define UB99FILE_H

#include <QFile>

class UB99File : public QFile
{
    Q_OBJECT
public:
    UB99File() : QFile() {}
    UB99File(const QString &name) : QFile(name) {}
#ifndef QT_NO_QOBJECT
    explicit UB99File(QObject *parent) : QFile( parent) {}
    UB99File(const QString &name, QObject *parent) : QFile( name, parent) {}
#endif

    bool open(OpenMode mode) override;
    void close() override { return QFile::close(); }

    void writePatchData( const QList<QByteArray> &patchDataList);

    QList<QByteArray> patchData();

private:
    static const int IdentifierLenght{10};
    const char UB99Header[IdentifierLenght] = { 'U', 'B', '9', '9', ' ', 'V', '1', '.', '0', '0' };

    static const int HeaderLenght{0x40};
    static const int NamesBlockOffset = HeaderLenght*2;
    static const int NamesBlockLenght{0x600 - NamesBlockOffset};
    static const int PatchDataBlockOffset = NamesBlockOffset + NamesBlockLenght;
    static const int PatchDataBlockLenght{0x4400 - PatchDataBlockOffset};

};

#endif // UB99FILE_H
