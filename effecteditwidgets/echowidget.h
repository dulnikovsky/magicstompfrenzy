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
#ifndef ECHOWIDGET_H
#define ECHOWIDGET_H

#include "effecteditbasewidget.h"

class EchoWidget: public EffectEditBaseWidget
{
    Q_OBJECT
public:
    explicit EchoWidget(QWidget *parent = nullptr);

    enum ParameterOffsets
    {
        FBDelayR = 0x00, // 2 bytes
        DelayTimeL = 0x10, // 2 bytes
        DelayTimeR = 0x12, // 2 bytes
        FBDelayL = 0x14, // 2 bytes

        FBGainL =0x1E,
        FBGainR = 0x1F,
        L_RFeedbackGain = 0x20,
        R_LFeedbackGain = 0x21,
        HighRatio = 0x22,
        HPF = 0x23,
        LPF = 0x24,
        Mix = 0x28
    };
};

#endif // ECHOWIDGET_H
