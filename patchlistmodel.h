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
#ifndef PATCHLISTMODEL_H
#define PATCHLISTMODEL_H

#include <QAbstractItemModel>

class PatchListModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    PatchListModel( const QList<QByteArray> &patchDataList, const QMap<int, QPair<QByteArray, bool>> &backupPatchDataMapRef, QObject *parent = Q_NULLPTR);

    QVariant data(const QModelIndex &index, int role) const override;

    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &) const override { return 2; }

    QModelIndex index(int row, int column, const QModelIndex &parent) const override;
    QModelIndex parent(const QModelIndex &child) const override;

    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

    void patchUpdated( int index);

private:
    const QList<QByteArray> &patchDataRef;
    const QMap<int, QPair<QByteArray, bool>> &backupPatchDataMapRef;
};

#endif // MIDIPORTMODEL_H
