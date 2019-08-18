#include "ub99file.h"

#include "magicstomp.h"

bool UB99File::open(OpenMode mode)
{
    bool ret = false;
    ret = QFile::open(mode);
    if(ret == false)
        return ret;

    if((mode & QIODevice::ReadOnly) == QIODevice::ReadOnly)
    {
        char buffer[IdentifierLenght];
        qint64 len = readData(buffer, IdentifierLenght);
        if(len != IdentifierLenght || strncmp( UB99Header, buffer, IdentifierLenght) != 0)
        {
            close();
            return false;
        }
        if( seek( HeaderLenght) == false)
        {
            close();
            return false;
        }
        len = readData(buffer, IdentifierLenght);
        if(len != IdentifierLenght || strncmp( UB99Header, buffer, IdentifierLenght) != 0)
        {
            close();
            return false;
        }
    }
    else if((mode & QIODevice::WriteOnly) == QIODevice::WriteOnly)
    {
        for(int i=0; i<2; i++)
        {
            if( write(UB99Header, IdentifierLenght) != IdentifierLenght)
            {
                return false;
            }
            for(int j = 0; j<HeaderLenght-IdentifierLenght; j++)
            {
                const char c = 0;
                if( write(&c, 1) != 1)
                {
                    return false;
                }
            }
        }
    }
    return true;
}

QList<QByteArray> UB99File::patchData()
{
    QList<QByteArray> dataList;

    seek(0);
    if( seek( PatchDataBlockOffset) == false)
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

void UB99File::writePatchData( const QList<QByteArray> &patchDataList)
{
    qint64 totalWritten = 0;
    for(int i=0; i<patchDataList.size(); i++)
    {
        if( patchDataList.at(i).length() != PatchTotalLength )
            continue;
        qint64 len = write( patchDataList.at(i).data()+PatchName, PatchNameLength);
        totalWritten += len;
    }
    for(int i = 0; i<NamesBlockLenght-totalWritten; i++)
    {
        const char c = 0;
        write(&c, 1);
    }
    totalWritten = 0;
    for(int i=0; i<patchDataList.size(); i++)
    {
        if( patchDataList.at(i).length() != PatchTotalLength )
            continue;
        qint64 len = write( patchDataList.at(i).data(), PatchTotalLength);
        totalWritten += len;
    }
    for(int i = 0; i<PatchDataBlockLenght-totalWritten; i++)
    {
        const char c = 0;
        write(&c, 1);
    }
}
