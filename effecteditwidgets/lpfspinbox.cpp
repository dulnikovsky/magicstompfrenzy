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
#include "lpfspinbox.h"

LpfSpinBox::LpfSpinBox(QWidget *parent )
    : FreqSpinBox( parent)
{

}

void LpfSpinBox::setRawValue(int val)
{
    setParametersForVal(val);
    FreqSpinBox::setRawValue(val);
}

void LpfSpinBox::stepBy(int steps)
{
    int newval = RawValue() + steps;
    setRawValue( newval);
}

LpfSpinBox::StepEnabled LpfSpinBox::stepEnabled() const
{
    StepEnabled enabled = QAbstractSpinBox::StepNone;
    if( RawValue() == 0x0C || RawValue() == 0x0D || RawValue() == 0x64)
    {
        enabled |= QAbstractSpinBox::StepUpEnabled;
        enabled |= QAbstractSpinBox::StepDownEnabled;
        return enabled;
    }
    else if(RawValue() == 0x65)
    {
        enabled |= QAbstractSpinBox::StepDownEnabled;
        return enabled;
    }
    else
        return FreqSpinBox::stepEnabled();
}

QString LpfSpinBox::convertToString() const
{
    if(RawValue() == 0x65)
        return "Thru";
    return FreqSpinBox::convertToString();
}

void LpfSpinBox::setParametersForVal(int val)
{
    if( val < 0x0D)
        setParameters( 50.0, 100.0, 0, 0x0C);
    else
        setParameters( 106.0, 16000.0, 0x0D, 0x64);
}
