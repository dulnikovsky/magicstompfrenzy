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
#ifndef DUALPITCHWIDGET_H
#define DUALPITCHWIDGET_H

#include "effecteditbasewidget.h"

class DualPitchWidget: public EffectEditBaseWidget
{
    Q_OBJECT
public:
    explicit DualPitchWidget(QWidget *parent = nullptr);

    enum ParameterOffsets
    {
        FBGain2 = 0x00, // 2Bytes
        Delay1 = 0x10, // 2Bytes
        FBGain1 = 0x12, // 2Bytes
        Delay2 = 0x14, // 2Bytes
        Mode = 0x16,
        Pitch1 = 0x1E,
        Fine1 = 0x1F,
        Level1 = 0x20,
        Pan1 = 0x21,

        Pitch2 = 0x22,
        Fine2 = 0x23,
        Level2 = 0x24,
        Pan2 = 0x25,

        Mix = 0x28
    };
};

#endif // DUALPITCHWIDGET_H
