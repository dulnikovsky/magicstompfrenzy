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
#include "expspinbox.h"
#include <QtMath>
#include <QLineEdit>

ExpSpinBox::ExpSpinBox(QWidget *parent) :
    QAbstractSpinBox(parent), realValue(0.0), minRealVal(20.0), maxRealVal(20000.0), minRawVal(0), maxRawVal(0x7F), rawValue(minRawVal)
{
    setReadOnly(true); // TODO: Accept input from the QLineEdit of this spinbox
}

void ExpSpinBox::setParameters(double minRVal, double maxRVal, int minR , int maxR)
{
    minRealVal = minRVal;
    maxRealVal = maxRVal;
    minRawVal = minR;
    maxRawVal = maxR;
    update();
}

void ExpSpinBox::setRawValue( int val)
{
    double maxExponent = qLn(maxRealVal) / qLn(minRealVal);
    double exponentStep = ((maxExponent-1) / ( maxRawVal - minRawVal ));
    realValue = qPow(minRealVal, (1 + (exponentStep * (val - minRawVal))));

    rawValue = val;
    lineEdit()->setText(convertToString());
    emit rawValueChanged( rawValue);
}

QString ExpSpinBox::convertToString() const
{
    QString txt;
    double val = RealValue();
    if( val < 1.0)
        txt = QString::number( val, 'f', 3 );
    else if( val < 10.0)
        txt = QString::number( val, 'f', 2 );
    else
        txt = QString::number( val, 'f', 1 );
    return txt + suffix;
}

void ExpSpinBox::stepBy(int steps)
{
    int newval = rawValue + steps;
    if( newval >= minRawVal && newval <= maxRawVal)
        setRawValue( newval);
}

QAbstractSpinBox::StepEnabled ExpSpinBox::stepEnabled() const
{
    StepEnabled enabled = QAbstractSpinBox::StepNone;

    if( rawValue >= minRawVal && rawValue < maxRawVal)
        enabled |= QAbstractSpinBox::StepUpEnabled;

    if( rawValue <= maxRawVal && rawValue > minRawVal)
        enabled |= QAbstractSpinBox::StepDownEnabled;

    return enabled;
}
