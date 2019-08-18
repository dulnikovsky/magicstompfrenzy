#include "ub99file.h"

#include "magicstomp.h"

bool UB99File::open(OpenMode mode)
{
    bool ret = false;
    if((mode & QIODevice::ReadOnly) == QIODevice::ReadOnly)
    {
        ret = QFile::open(mode);
        if(ret == false)
            return ret;

        char buffer[10];
        qint64 len = readData(buffer, 10);
        if(len != 10 || strncmp( UB99Header, buffer, 10) != 0)
        {
            close();
            return false;
        }
    }
    return true;
}

QList<QByteArray> UB99File::patchData()
{
    QList<QByteArray> dataList;

    seek(0);
    if( seek(0x600) == false)
        return dataList;

    char *buffer = new char[MagistompPatchDesc::PatchTotalLength];
    qint64 len = readData(buffer, MagistompPatchDesc::PatchTotalLength);
    while( len == MagistompPatchDesc::PatchTotalLength)
    {
        dataList.append( QByteArray(buffer, MagistompPatchDesc::PatchTotalLength));
        len = readData(buffer, MagistompPatchDesc::PatchTotalLength);
    }

    delete[] buffer;
    return dataList;
}
