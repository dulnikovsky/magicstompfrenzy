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
#include "reverbtimespinbox.h"
#include <QtMath>
#include <QLineEdit>

ReverbTimeSpinBox::ReverbTimeSpinBox(QWidget *parent) :
    QAbstractSpinBox(parent), minRawVal(0), maxRawVal(0x7F), rawValue(minRawVal)
{
    setReadOnly(true); // TODO: Accept input from the QLineEdit of this spinbox
}

void ReverbTimeSpinBox::setParameters( int minR , int maxR)
{
    minRawVal = minR;
    maxRawVal = maxR;
    update();
}

void ReverbTimeSpinBox::setRawValue( int val)
{
    QString txt;

    if(val < 0x2F)
        txt = QString::number( static_cast<double>(val)/10.0+0.3);
    else if( val < 0x39 )
        txt = QString::number( static_cast<double>(val-0x2F)/2.0 +5);
    else if( val < 0x43 )
        txt = QString::number( static_cast<double>((val-0x39)+10));
    else
        txt = QString::number( static_cast<double>(val-0x43)*5 +20);
    lineEdit()->setText(txt + suffix);
    update();
    rawValue = val;
    emit rawValueChanged( rawValue);
}

void ReverbTimeSpinBox::stepBy(int steps)
{
    int newval = rawValue + steps;
    if( newval >= minRawVal && newval <= maxRawVal)
        setRawValue( newval);
}

QAbstractSpinBox::StepEnabled ReverbTimeSpinBox::stepEnabled() const
{
    StepEnabled enabled = QAbstractSpinBox::StepNone;

    if( rawValue >= minRawVal && rawValue < maxRawVal)
        enabled |= QAbstractSpinBox::StepUpEnabled;

    if( rawValue <= maxRawVal && rawValue > minRawVal)
        enabled |= QAbstractSpinBox::StepDownEnabled;

    return enabled;
}
