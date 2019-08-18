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

    QList<QByteArray> patchData();

private:
    const char UB99Header[10] = { 'U', 'B', '9', '9', ' ', 'V', '1', '.', '0', '0' };

};

#endif // UB99FILE_H
