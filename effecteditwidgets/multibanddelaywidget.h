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
#ifndef MULTIBANDDELAYWIDGET_H
#define MULTIBANDDELAYWIDGET_H

#include "effecteditbasewidget.h"

class MultibandDelayWidget : public EffectEditBaseWidget
{
    Q_OBJECT
public:

    enum parameterOffsets
    {
        DelayTime1 = 0x00,
        DelayTime2 = 0x02,
        DelayTime3 = 0x04,
        DelayTime4 = 0x06,
        DelayTime5 = 0x08,
        DelayTime6 = 0x0A,
        DelayTime7 = 0x0C,
        DelayTime8 = 0x0E,

        EffectLevel = 0x10, //Two bytes
        DirectLevel = 0x12, //Two bytes
        DirectPan = 0x14, //Two bytes
        WaveForm = 0x16,
        LowCutFilter1 = 0x1E
    };
    static const int BandLenght = 11;

    explicit MultibandDelayWidget( EffectTypeId id, QWidget *parent = nullptr);
};

#endif // NOISEGATEWIDGET_H
