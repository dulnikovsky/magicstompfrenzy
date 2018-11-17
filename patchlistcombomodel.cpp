/****************************************************************************
**
** Copyright (C) 2018 Robert Vetter.
**
** This file is part of the MagicstompFrenzy - an editor for Yamaha Magicstomp
** effect processor
**
** THIS CODE IS PROVIDED *AS IS* WITHOUT WARRANTY OF
** ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING ANY
** IMPLIED WARRANTIES OF FITNESS FOR A PARTICULAR
** PURPOSE, MERCHANTABILITY, OR NON-INFRINGEMENT.
**
** GNU General Public License Usage
** This file may be used under the terms of the GNU
** General Public License version 2.0 or (at your option) the GNU General
** Public license version 3 or any later version . The licenses are
** as published by the Free Software Foundation and appearing in the file LICENSE
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-2.0.html and
** https://www.gnu.org/licenses/gpl-3.0.html.
**/
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
