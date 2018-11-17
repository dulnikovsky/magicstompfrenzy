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
#ifndef SYMPHONICWIDGET_H
#define SYMPHONICWIDGET_H

#include "effecteditbasewidget.h"

class SymphonicWidget: public EffectEditBaseWidget
{
    Q_OBJECT
public:
    explicit SymphonicWidget(QWidget *parent = nullptr);

    enum ParameterOffsets
    {
        Freq = 0x10, //2 bytes
        Depth = 0x12, //2 bytes
        ModDelay = 0x14, //2 bytes
        Wave =0x16,

        LSHFreq = 0x1E,
        LSHGain = 0x1F,

        EQFreq = 0x20,
        EQGain = 0x21,
        EQQ = 0x22,

        HSHFreq = 0x24,
        HSHGain = 0x25,

        Mix = 0x28
    };
};

#endif // FLANGEWIDGET_H
