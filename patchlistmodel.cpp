#include "patchlistmodel.h"
#include <QColor>

PatchListModel::PatchListModel( const QList<QByteArray> &patchDataList, QObject *parent)
    :QAbstractItemModel(parent), patchDataRef(patchDataList)
{

}

QVariant PatchListModel::data(const QModelIndex &index, int role) const
{
    if(role==Qt::DisplayRole)
    {
        QString number = QString::number(index.row()+1).rightJustified(2, '0');
        QString patchName;
        if( patchDataRef.at(index.row()).size()>= 32)
        {
            patchName = QString::fromLatin1( patchDataRef.at(index.row()).mid(16, 12));
        }
        return number + " " + patchName;
    }
//    else if(role==Qt::DecorationRole)
//    {
//        return QColor(Qt::yellow);
//    }
    return QVariant();
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
    emit dataChanged( createIndex(index, 0), createIndex(index, 0));
}
