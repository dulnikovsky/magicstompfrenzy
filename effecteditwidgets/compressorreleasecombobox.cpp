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
#include "compressorreleasecombobox.h"

CompressorReleaseComboBox::CompressorReleaseComboBox(QWidget *parent) :
    QComboBox(parent)
{
    addItems(valuesStringList);
}

const QStringList CompressorReleaseComboBox::valuesStringList =
{
    QStringLiteral("6 ms"),
    QStringLiteral("12 ms"),
    QStringLiteral("17 ms"),
    QStringLiteral("23 ms"),
    QStringLiteral("29 ms"),
    QStringLiteral("35 ms"),
    QStringLiteral("41 ms"),
    QStringLiteral("46 ms"),
    QStringLiteral("52 ms"),
    QStringLiteral("58 ms"),
    QStringLiteral("64 ms"),
    QStringLiteral("70 ms"),
    QStringLiteral("75 ms"),
    QStringLiteral("81 ms"),
    QStringLiteral("87 ms"),
    QStringLiteral("93 ms"),
    QStringLiteral("99 ms"),
    QStringLiteral("104 ms"),
    QStringLiteral("110 ms"),
    QStringLiteral("116 ms"),
    QStringLiteral("122 ms"),
    QStringLiteral("128 ms"),
    QStringLiteral("133 ms"),
    QStringLiteral("139 ms"),
    QStringLiteral("145 ms"),
    QStringLiteral("151 ms"),
    QStringLiteral("157 ms"),
    QStringLiteral("163 ms"),
    QStringLiteral("168 ms"),
    QStringLiteral("174 ms"),
    QStringLiteral("180 ms"),
    QStringLiteral("186 ms"),
    QStringLiteral("192 ms"),
    QStringLiteral("203 ms"),
    QStringLiteral("215 ms"),
    QStringLiteral("226 ms"),
    QStringLiteral("250 ms"),
    QStringLiteral("261 ms"),
    QStringLiteral("273 ms"),
    QStringLiteral("284 ms"),
    QStringLiteral("296 ms"),
    QStringLiteral("308 ms"),
    QStringLiteral("319 ms"),
    QStringLiteral("331 ms"),
    QStringLiteral("342 ms"),
    QStringLiteral("354 ms"),
    QStringLiteral("366 ms"),
    QStringLiteral("377 ms"),
    QStringLiteral("400 ms"),
    QStringLiteral("424 ms"),
    QStringLiteral("447 ms"),
    QStringLiteral("470 ms"),
    QStringLiteral("493 ms"),
    QStringLiteral("517 ms"),
    QStringLiteral("540 ms"),
    QStringLiteral("563 ms"),
    QStringLiteral("586 ms"),
    QStringLiteral("609 ms"),
    QStringLiteral("633 ms"),
    QStringLiteral("656 ms"),
    QStringLiteral("679 ms"),
    QStringLiteral("702 ms"),
    QStringLiteral("725 ms"),
    QStringLiteral("749 ms"),
    QStringLiteral("795 ms"),
    QStringLiteral("842 ms"),
    QStringLiteral("888 ms"),
    QStringLiteral("934 ms"),
    QStringLiteral("981 ms"),
    QStringLiteral("1.02 s"),
    QStringLiteral("1.07 s"),
    QStringLiteral("1.12 s"),
    QStringLiteral("1.16 s"),
    QStringLiteral("1.21 s"),
    QStringLiteral("1.25 s"),
    QStringLiteral("1.30 s"),
    QStringLiteral("1.35 s"),
    QStringLiteral("1.39 s"),
    QStringLiteral("1.44 s"),
    QStringLiteral("1.49 s"),
    QStringLiteral("1.58 s"),
    QStringLiteral("1.67 s"),
    QStringLiteral("1.77 s"),
    QStringLiteral("1.86 s"),
    QStringLiteral("1.95 s"),
    QStringLiteral("2.04 s"),
    QStringLiteral("2.14 s"),
    QStringLiteral("2.23 s"),
    QStringLiteral("2.32 s"),
    QStringLiteral("2.42 s"),
    QStringLiteral("2.51 s"),
    QStringLiteral("2.60 s"),
    QStringLiteral("2.69 s"),
    QStringLiteral("2.79 s"),
    QStringLiteral("2.88 s"),
    QStringLiteral("2.97 s"),
    QStringLiteral("3.16 s"),
    QStringLiteral("3.34 s"),
    QStringLiteral("3.53 s"),
    QStringLiteral("3.72 s"),
    QStringLiteral("3.90 s"),
    QStringLiteral("4.09 s"),
    QStringLiteral("4.27 s"),
    QStringLiteral("4.46 s"),
    QStringLiteral("4.64 s"),
    QStringLiteral("4.83 s"),
    QStringLiteral("5.02 s"),
    QStringLiteral("5.20 s"),
    QStringLiteral("5.39 s"),
    QStringLiteral("5.57 s"),
    QStringLiteral("5.76 s"),
    QStringLiteral("5.94 s"),
    QStringLiteral("6.32 s"),
    QStringLiteral("6.69 s"),
    QStringLiteral("7.06 s"),
    QStringLiteral("7.43 s"),
    QStringLiteral("7.80 s"),
    QStringLiteral("8.17 s"),
    QStringLiteral("8.54 s"),
    QStringLiteral("8.92 s"),
    QStringLiteral("9.29 s"),
    QStringLiteral("9.66 s"),
    QStringLiteral("10.0 s"),
    QStringLiteral("10.4 s"),
    QStringLiteral("10.7 s"),
    QStringLiteral("11.1 s"),
    QStringLiteral("11.5 s")
};
