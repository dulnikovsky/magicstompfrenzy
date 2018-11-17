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
#include "hpfspinbox.h"

HpfSpinBox::HpfSpinBox(QWidget *parent )
    : FreqSpinBox( parent)
{

}

void HpfSpinBox::setRawValue(int val)
{
    setParametersForVal(val);
    FreqSpinBox::setRawValue(val);
}

void HpfSpinBox::stepBy(int val)
{
    setParametersForVal(RawValue()+val);
    FreqSpinBox::stepBy(val);
}

HpfSpinBox::StepEnabled HpfSpinBox::stepEnabled() const
{
    if( RawValue() == 0x1C || RawValue() == 0x1D )
    {
        StepEnabled enabled = QAbstractSpinBox::StepNone;
        enabled |= QAbstractSpinBox::StepUpEnabled;
        enabled |= QAbstractSpinBox::StepDownEnabled;
        return enabled;
    }
    else
        return FreqSpinBox::stepEnabled();
}

QString HpfSpinBox::convertToString() const
{
    if(RawValue() == 0x00)
        return "Thru";
    return FreqSpinBox::convertToString();
}

void HpfSpinBox::setParametersForVal(int val)
{
    if( val < 0x1D)
        setParameters( 20.0, 100.0, 0, 0x1C);
    else
        setParameters( 106.0, 8000.0, 0x1D, 0x68);
}
