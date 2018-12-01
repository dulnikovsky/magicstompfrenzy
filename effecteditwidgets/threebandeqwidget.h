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
#ifndef THREEBANDEQWIDGET_H
#define THREEBANDEQWIDGET_H

#include "effecteditbasewidget.h"

class ThreeBandEqWidget: public EffectEditBaseWidget
{
    Q_OBJECT
public:
    explicit ThreeBandEqWidget( QWidget *parent = nullptr);

    enum ParameterOffsets
    {
        Level = 0x00, // 2 Bytes

        EQ1Freq = 0x10, // 2 Bytes
        EQ2Freq = 0x12, // 2 Bytes
        EQ3Freq = 0x14, // 2 Bytes

        EQ1Gain = 0x20,
        EQ2Gain = 0x21,
        EQ3Gain = 0x22,

        EQ1Q = 0x26,
        EQ2Q = 0x27,
        EQ3Q = 0x28
    };
};

#endif // THREEBANDEQWIDGET_H
