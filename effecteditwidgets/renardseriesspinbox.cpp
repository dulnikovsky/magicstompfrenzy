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
#include "renardseriesspinbox.h"
#include <QtMath>
#include <QLineEdit>

RenardSeriesSpinBox::RenardSeriesSpinBox(QWidget *parent) :
    QAbstractSpinBox(parent), divideSteps(40), minRawVal(0), maxRawVal(0x7F), rawValue(minRawVal), rawOffset(0)
{
    setReadOnly(true); // TODO: Accept input from the QLineEdit of this spinbox
}

void RenardSeriesSpinBox::setParameters(int divSteps, int minR , int maxR)
{
    divideSteps = divSteps;
    minRawVal = minR;
    maxRawVal = maxR;
    update();
}

void RenardSeriesSpinBox::setRawValue( int val)
{
    rawValue = val;

    lineEdit()->setText(convertToString());
    emit rawValueChanged( rawValue);
}

QString RenardSeriesSpinBox::convertToString() const
{
    QString txt;
    txt = QString::number(qPow(qPow(10.0, 1.0/divideSteps), rawValue+rawOffset) , 'f', 2 );
    return txt + suffix;
}

void RenardSeriesSpinBox::stepBy(int steps)
{
    int newval = rawValue + steps;
    if( newval >= minRawVal && newval <= maxRawVal)
        setRawValue( newval);
}

QAbstractSpinBox::StepEnabled RenardSeriesSpinBox::stepEnabled() const
{
    StepEnabled enabled = QAbstractSpinBox::StepNone;

    if( rawValue >= minRawVal && rawValue < maxRawVal)
        enabled |= QAbstractSpinBox::StepUpEnabled;

    if( rawValue <= maxRawVal && rawValue > minRawVal)
        enabled |= QAbstractSpinBox::StepDownEnabled;

    return enabled;
}
