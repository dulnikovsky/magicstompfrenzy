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
#include "tapeechowidget.h"
#include <QGridLayout>
#include <QDoubleSpinBox>
#include <QLabel>

TapeEchoWidget::TapeEchoWidget(QWidget *parent) :
    EffectEditBaseWidget(parent)
{
    QDoubleSpinBox *dspinBox;
    QGridLayout *mainlyt = new QGridLayout();

    mainlyt->addWidget(new QLabel(tr("Time")), 0, 0);
    dspinBox = createStandard10DblSpinBox(Time);
    dspinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 2);
    mainlyt->addWidget(dspinBox, 1, 0);

    mainlyt->addWidget(new QLabel(tr("Feedback")), 0, 1);
    dspinBox = createStandard10DblSpinBox(Feedback);
    mainlyt->addWidget(dspinBox, 1, 1);

    mainlyt->addWidget(new QLabel(tr("Level")), 0, 2);
    dspinBox = createStandard10DblSpinBox(Level);
    mainlyt->addWidget(dspinBox, 1, 2);

    mainlyt->setColumnStretch(3, 2);
    mainlyt->setRowStretch( 2,2);

    setLayout(mainlyt);
}
