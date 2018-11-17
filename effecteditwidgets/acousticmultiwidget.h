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
#ifndef ACOUSTICMULTIWIDGET_H
#define ACOUSTICMULTIWIDGET_H

#include "effecteditbasewidget.h"

class AcousticMultiWidget: public EffectEditBaseWidget
{
    Q_OBJECT
public:
    explicit AcousticMultiWidget(QWidget *parent = nullptr);

    enum ParameterOffsets
    {
        MicType = 0x16,

        Blend = 0x1E,
        Bass = 0x1F,
        Middle = 0x20,
        Treble = 0x21,
        Presence = 0x22,

        Volume = 0x23,
        Stereo = 0x24,
        BassFreq = 0x25,
        MiddleFreq = 0x26,
        TrebleFreq = 0x27,
        PresenceFreq = 0x28,
        Limiter = 0x29,
        ChorusDelayType = 0x2B,
        ReverbType = 0x2D,
        LimiterLevel = 0x2F,

        SpeedTime = 0x30,
        DepthFeedback = 0x31,
        EffectLevel = 0x32,
        ReverbLevel = 0x33

    };
private:

};

#endif // ACOUSTICMULTIWIDGET_H
