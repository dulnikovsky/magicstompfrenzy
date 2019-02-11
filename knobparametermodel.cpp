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
#include "knobparametermodel.h"

KnobParameterModel::KnobParameterModel(const QMap<int, QString> &parameterMap, int numberOfRows, QObject *parent)
    : parameterMap(parameterMap), nRows(numberOfRows), QAbstractItemModel(parent)
{

}

QVariant KnobParameterModel::data(const QModelIndex &index, int role) const
{
    if(role == Qt::DisplayRole && index.column() == 0)
    {
        int row = index.row();
        if( parameterMap.contains( row))
            return parameterMap.value( row);

    }
    return QVariant();
}
