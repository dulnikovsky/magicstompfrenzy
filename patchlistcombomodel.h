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
#ifndef PATCHLISTCOMBOMODEL_H
#define PATCHLISTCOMBOMODEL_H

#include <QAbstractItemModel>

class PatchListComboModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    PatchListComboModel( QObject *parent = nullptr) : QAbstractItemModel(parent), sourcemodel(nullptr), disabledRow(-1) { }

    void setSourceModel(QAbstractItemModel *model) { beginResetModel(); sourcemodel = model; endResetModel(); }
    void setDisabledRow(int row) { disabledRow = row; }

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    int rowCount(const QModelIndex &parent) const override { return sourcemodel!=nullptr?sourcemodel->rowCount(parent):0; }
    int columnCount(const QModelIndex &) const override { return 1; }

    QModelIndex index(int row, int column, const QModelIndex & = QModelIndex()) const override { return createIndex(row, column); }
    QModelIndex parent(const QModelIndex &) const override { return QModelIndex(); }

    Qt::ItemFlags flags(const QModelIndex &index) const override;
private:
    QAbstractItemModel *sourcemodel;
    int disabledRow;
};

#endif // PATCHLISTCOMBOMODEL_H
