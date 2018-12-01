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
#ifndef MODFILTERWIDGET_H
#define MODFILTERWIDGET_H

#include "effecteditbasewidget.h"

class ModFilterWidget: public EffectEditBaseWidget
{
    Q_OBJECT
public:
    explicit ModFilterWidget( QWidget *parent = nullptr);

    enum ParameterOffsets
    {
        Freq = 0x00, // 2 Bytes

        Type = 0x16,

        Depth = 0x1E,
        Phase = 0x1F,
        Offset = 0x20,
        Resonance = 0x21,
        Level = 0x22,

        Mix = 0x28
    };
};

#endif // MODFILTERWIDGET_H
