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
#ifndef REVERBWIDGET_H
#define REVERBWIDGET_H

#include "effecteditbasewidget.h"

class ReverbWidget: public EffectEditBaseWidget
{
    Q_OBJECT
public:
    explicit ReverbWidget(QWidget *parent = nullptr);

    enum ParameterOffsets
    {
        HighRatio = 0x00, // 2 Bytes
        InitDelay = 0x10, // 2 Bytes
        ERRevDelay = 0x12, // 2 Bytes
        Time = 0x14, // 2 Bytes
        Type = 0x16,

        LowRatio = 0x1E,
        Diffusion = 0x1F,
        Density = 0x20,
        ERRevBalance = 0x21,
        HPF = 0x22,
        LPF = 0x23,
        GateLevel = 0x24,
        GateAttack = 0x25,
        GateHold = 0x26,
        GateDecay = 0x27,
        Mix = 0x28
    };
};

#endif // REVERBWIDGET_H
