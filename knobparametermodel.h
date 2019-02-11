/****************************************************************************
**
** Copyright (C) 2019 Robert Vetter.
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
#ifndef KNOBPARAMETERMODEL_H
#define KNOBPARAMETERMODEL_H

#include <QAbstractItemModel>

class KnobParameterModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit KnobParameterModel(const QMap<int, QString> &parameterMap, int numberOfRows, QObject *parent = 0);

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    int rowCount(const QModelIndex &) const override { return nRows; }
    int columnCount(const QModelIndex &) const override { return 1; }

    QModelIndex index(int row, int column, const QModelIndex & = QModelIndex()) const override { return createIndex(row, column); }
    QModelIndex parent(const QModelIndex &) const override { return QModelIndex(); }

private:
    const QMap<int, QString> &parameterMap;
    int nRows;
};

#endif // KNOBPARAMETERMODEL_H
