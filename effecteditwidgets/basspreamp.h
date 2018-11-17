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
#ifndef BASSPREAMPWIDGET_H
#define BASSPREAMPWIDGET_H

#include "effecteditbasewidget.h"

class BassPreampWidget : public EffectEditBaseWidget
{
    Q_OBJECT
public:
    enum EffectParameterOffsets
    {
        ParametricEQFreq = 0x02, // 2 bytes

        Gain = 0x10, // 2 bytes
        Master = 0x12, // 2 bytes
        Type = 0x16,
        Bass = 0x1E,
        LowMiddle = 0x1F,
        Middle = 0x20,
        HighMiddle = 0x21,
        Treble = 0x22,

        BassFreq = 0x24,
        LowMidFreq = 0x25,
        MiddleFreq = 0x26,
        HighMidFreq = 0x27,
        TrebleFreq = 0x28,

        ParametricEQQ = 0x29,
        ParametricEQGain = 0x2A,

        Gate = 0x2B,
        SpeakerSimulatorSwitch = 0x2C,
        Limiter = 0x2D,
        Ratio = 0x2E,
        Threshold = 0x2F,
        Attack = 0x30,
        Release = 0x31,
        CompressorGain = 0x32,
        Knee = 0x33
    };
    explicit BassPreampWidget( QWidget *parent = nullptr);
private:

    static QDoubleSpinBox * createStdGainSpinBox(int offset);
};

#endif // BASSPREAMPWIDGET_H
