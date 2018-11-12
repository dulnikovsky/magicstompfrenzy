#include "patchlistmodel.h"
#include <QColor>

#include "magicstomp.h"
#include "magicstomptext.h"

PatchListModel::PatchListModel( const QList<QByteArray> &patchDataList, const QMap<int, QPair<QByteArray, bool>> &backupPatchData, QObject *parent)
    :QAbstractItemModel(parent), patchDataRef(patchDataList), backupPatchDataMapRef(backupPatchData)
{

}

QVariant PatchListModel::data(const QModelIndex &index, int role) const
{
    if(index.column() == 0)
    {
        if(role==Qt::DisplayRole)
        {
            QString patchName;
            if( patchDataRef.at(index.row()).size() == PatchTotalLength)
            {
                patchName = QString::fromLatin1( patchDataRef.at(index.row()).mid(PatchName, PatchNameLength));
            }
            return patchName;
        }
        else if(role==Qt::DecorationRole)
        {
            int row = index.row();
            if(backupPatchDataMapRef.contains(row) && backupPatchDataMapRef.value(row).second == true)
                return QColor(Qt::yellow);
        }
    }
    if(index.column() == 1)
    {
        if(role==Qt::DisplayRole)
        {
            QString effectTypeName;
            if( patchDataRef.at(index.row()).size() == PatchTotalLength)
            {
                int patchId = patchDataRef.at(index.row()).at(PatchType+1); // Only last byte us used
                if( patchId>=0 && patchId<EffectTypeNUMBER)
                    effectTypeName = EffectTypeNameList.at(patchId);
            }
            return effectTypeName;
        }
    }
    return QVariant();
}

QVariant PatchListModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role==Qt::DisplayRole)
    {
        if( orientation==Qt::Horizontal)
        {
            if(section==0)
                return tr("Name");
            else if(section==1)
                return tr("Type");
        }
        else
        {
            return QString::number(section+1).rightJustified(2, '0');
        }
    }
    return QAbstractItemModel::headerData(section, orientation, role);
}

int PatchListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return patchDataRef.size();
}

QModelIndex PatchListModel::index(int row, int column, const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return createIndex( row, column);
}

QModelIndex PatchListModel::parent(const QModelIndex &child) const
{
    Q_UNUSED(child)
    return QModelIndex();
}

void PatchListModel::patchUpdated( int index)
{
    emit dataChanged( createIndex(index, 0), createIndex(index, 1));
}
