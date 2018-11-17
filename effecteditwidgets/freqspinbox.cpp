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
#include "freqspinbox.h"
#include <QtMath>
#include <QLineEdit>

FreqSpinBox::FreqSpinBox(QWidget *parent) :
    ExpSpinBox(parent)
{

}

QString FreqSpinBox::convertToString() const
{
    QString txt;
    double val = RealValue();
    if( val < 100.0)
        txt = QString::number( val, 'f', 1 ) + QStringLiteral(" Hz");
    else if( val < 1000.0)
        txt = QString::number( val, 'f', 0 ) + QStringLiteral(" Hz");
    else
        txt = QString::number( val/1000, 'f', 2 ) + QStringLiteral(" kHz");
    return txt;
}
