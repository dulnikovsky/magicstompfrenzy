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
#ifndef PHASERWIDGET_H
#define PHASERWIDGET_H

#include "effecteditbasewidget.h"

class PhaserWidget: public EffectEditBaseWidget
{
    Q_OBJECT
public:
    explicit PhaserWidget(QWidget *parent = nullptr);

    enum ParameterOffsets
    {
        Offset= 0x00, // 2 Bytes
        Freq = 0x10, //2 bytes
        Depth = 0x12, //2 bytes
        FBGain = 0x14, //2 bytes
        Stage =0x16,

        Phase = 0x1E,
        LSHFreq = 0x1F,
        LSHGain = 0x20,
        HSHFreq = 0x21,
        HSHGain = 0x22,

        Mix = 0x28
    };
};

#endif // PHASERWIDGET_H
