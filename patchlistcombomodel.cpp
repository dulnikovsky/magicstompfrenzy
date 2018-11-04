#include "patchlistcombomodel.h"

QVariant PatchListComboModel::data(const QModelIndex &index, int role) const
{
    if(sourcemodel == nullptr)
        return QVariant();

    if(role == Qt::DisplayRole && index.column()==0)
    {
        int row = index.row();
        return QString::number(row+1).rightJustified(2, '0') + " " +
                sourcemodel->data( sourcemodel->index(row, 0), role).toString() + " [" +
                sourcemodel->data( sourcemodel->index(row, 1), role).toString() + " ]";

    }
    return QVariant();
}

Qt::ItemFlags PatchListComboModel::flags(const QModelIndex &idx) const
{
    if(idx.row() == disabledRow)
        return Qt::NoItemFlags;
    else if( sourcemodel != nullptr)
        return sourcemodel->flags( sourcemodel->index(idx.row(), idx.column()));
    else
        return QAbstractItemModel::flags(idx);
}
