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
#ifndef DELAYEARLYREFWIDGET_H
#define DELAYEARLYREFWIDGET_H

#include "effecteditbasewidget.h"

class DelayEarlyRefWidget: public EffectEditBaseWidget
{
    Q_OBJECT
public:
    explicit DelayEarlyRefWidget(bool isParallel = true, QWidget *parent = nullptr);

    enum ParameterOffsets
    {
        InitDelay = 0x02, //2 Bytes

        Type = 0x17,

        Balance = 0x21,
        Mix = 0x28,
        RoomSize = 0x29,
        Liveness = 0x2A,
        Diffusion = 0x2B,
        Density = 0x2C,
        ERNumber = 0x2D
    };
};

#endif // DELAYEARLYREFWIDGET_H
