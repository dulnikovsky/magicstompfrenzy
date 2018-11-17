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
#include "bassfreqspinbox.h"

BassFreqSpinBox::BassFreqSpinBox(QWidget *parent )
    : FreqSpinBox( parent)
{

}

void BassFreqSpinBox::setRawValue(int val)
{
    setParametersForVal(val);
    FreqSpinBox::setRawValue(val);
}

void BassFreqSpinBox::stepBy(int val)
{
    setParametersForVal(RawValue()+val);
    FreqSpinBox::stepBy(val);
}

BassFreqSpinBox::StepEnabled BassFreqSpinBox::stepEnabled() const
{
    if( RawValue() == 0x4A || RawValue() == 0x49 )
    {
        StepEnabled enabled = QAbstractSpinBox::StepNone;
        enabled |= QAbstractSpinBox::StepUpEnabled;
        enabled |= QAbstractSpinBox::StepDownEnabled;
        return enabled;
    }
    else
        return FreqSpinBox::stepEnabled();
}

void BassFreqSpinBox::setParametersForVal(int val)
{
    if( val < 0x4A)
        setParameters( 20.0, 100.0, 0, 0x49);
    else
        setParameters( 100.0, 320.0, 0x4A, 0x7F);
}
