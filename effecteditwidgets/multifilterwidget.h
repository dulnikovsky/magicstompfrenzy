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
#ifndef MULTIFILTERWIDGET_H
#define MULTIFILTERWIDGET_H

#include "effecteditbasewidget.h"

class MultiFilterWidget: public EffectEditBaseWidget
{
    Q_OBJECT
public:
    explicit MultiFilterWidget( QWidget *parent = nullptr);

    enum ParameterOffsets
    {
        Type1 = 0x16,
        Type2 = 0x17,
        Type3 = 0x18,

        Level1 = 0x1F,
        Level2 = 0x2A,
        Level3 = 0x35,

        Freq1 = 0x1E,
        Freq2 = 0x29,
        Freq3 = 0x35,

        Resonance1 = 0x20,
        Resonance2 = 0x2B,
        Resonance3 = 0x36,

        Mix = 0x28
    };
};

#endif // MULTIFILTERWIDGET_H
