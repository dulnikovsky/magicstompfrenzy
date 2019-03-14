/****************************************************************************
**
** Copyright (C) 2019 Robert Vetter.
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
#include "noisegatedecaycombobox.h"

NoiseGateDecayComboBox::NoiseGateDecayComboBox(QWidget *parent) :
    QComboBox(parent)
{
    addItems(valuesStringList);
}

const QStringList NoiseGateDecayComboBox::valuesStringList =
{
    QStringLiteral("6 ms"),
    QStringLiteral("17 ms"),
    QStringLiteral("29 ms"),
    QStringLiteral("41 ms"),
    QStringLiteral("52 ms"),
    QStringLiteral("64 ms"),
    QStringLiteral("75 ms"),
    QStringLiteral("87 ms"),
    QStringLiteral("99 ms"),
    QStringLiteral("110 ms"),
    QStringLiteral("122 ms"),
    QStringLiteral("133 ms"),
    QStringLiteral("145 ms"),
    QStringLiteral("157 ms"),
    QStringLiteral("168 ms"),
    QStringLiteral("180 ms"),
    QStringLiteral("192 ms"),
    QStringLiteral("215 ms"),
    QStringLiteral("238 ms"),
    QStringLiteral("261 ms"),
    QStringLiteral("284 ms"),
    QStringLiteral("308 ms"),
    QStringLiteral("331 ms"),
    QStringLiteral("354 ms"),
    QStringLiteral("377 ms"),
    QStringLiteral("424 ms"),
    QStringLiteral("470 ms"),
    QStringLiteral("517 ms"),
    QStringLiteral("563 ms"),
    QStringLiteral("609 ms"),
    QStringLiteral("656 ms"),
    QStringLiteral("702 ms"),
    QStringLiteral("749 ms"),
    QStringLiteral("842 ms"),
    QStringLiteral("934 ms"),
    QStringLiteral("1.02 s"),
    QStringLiteral("1.12 s"),
    QStringLiteral("1.21 s"),
    QStringLiteral("1.30 s"),
    QStringLiteral("1.39 s"),
    QStringLiteral("1.49 s"),
    QStringLiteral("1.67 s"),
    QStringLiteral("1.86 s"),
    QStringLiteral("2.04 s"),
    QStringLiteral("2.23 s"),
    QStringLiteral("2.42 s"),
    QStringLiteral("2.60 s"),
    QStringLiteral("2.79 s"),
    QStringLiteral("2.97 s"),
    QStringLiteral("3.34 s"),
    QStringLiteral("3.72 s"),
    QStringLiteral("4.09 s"),
    QStringLiteral("4.46 s"),
    QStringLiteral("4.83 s"),
    QStringLiteral("5.20 s"),
    QStringLiteral("5.57 s"),
    QStringLiteral("5.94 s"),
    QStringLiteral("6.69 s"),
    QStringLiteral("7.43 s"),
    QStringLiteral("8.17 s"),
    QStringLiteral("8.92 s"),
    QStringLiteral("9.66 s"),
    QStringLiteral("10.4 s"),
    QStringLiteral("11.1 s"),
    QStringLiteral("11.8 s"),
    QStringLiteral("13.3 s"),
    QStringLiteral("14.8 s"),
    QStringLiteral("16.3 s"),
    QStringLiteral("17.8 s"),
    QStringLiteral("19.3 s"),
    QStringLiteral("22.2 s"),
    QStringLiteral("23.7 s"),
    QStringLiteral("26.7 s"),
    QStringLiteral("29.7 s"),
    QStringLiteral("32.6 s"),
    QStringLiteral("35.6 s"),
    QStringLiteral("38.6 s"),
    QStringLiteral("41.6 s"),
    QStringLiteral("44.5 s")
};
