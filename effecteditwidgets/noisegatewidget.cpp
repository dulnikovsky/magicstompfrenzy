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
#include "noisegatewidget.h"
#include <QGridLayout>
#include <QDoubleSpinBox>
#include <QLabel>
#include <QSpinBox>
#include "expspinbox.h"
#include "noisegatedecaycombobox.h"

NoiseGateWidget::NoiseGateWidget(int thresholdOffset,
                                 int attackOffset,
                                 int holdOffset,
                                 int decayOffset,
                                 QWidget *parent)
    :    EffectEditBaseWidget(parent)
{
    setTitle(tr("Noise Gate"));

    QDoubleSpinBox *dspinBox;
    QGridLayout *mainlyt = new QGridLayout();

    mainlyt->addWidget(new QLabel(tr("Threshold")), 0, 0);
    dspinBox = createStandard10DblSpinBox( thresholdOffset);
    mainlyt->addWidget(dspinBox, 1, 0);

    mainlyt->addWidget(new QLabel(tr("Attack")), 2, 0);
    QSpinBox *attackspinBox = createStandardRawSpinBox(attackOffset, 0, 120);
    attackspinBox->setSuffix(" ms");
    mainlyt->addWidget(attackspinBox, 3, 0);

    mainlyt->addWidget(new QLabel(tr("Hold")), 0, 1);
    ExpSpinBox *holdspinBox = new ExpSpinBox();
    holdspinBox->setSuffix(QStringLiteral(" ms"));
    holdspinBox->setParameters(0.2, 2040, 0, 0x6B);
    holdspinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, holdOffset);
    holdspinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    mainlyt->addWidget(holdspinBox, 1, 1);

    mainlyt->addWidget(new QLabel(tr("Decay")), 2, 1);
    QComboBox *decayComboBox = new NoiseGateDecayComboBox();
    decayComboBox->setProperty( ArrayDataEditWidget::valuePropertyName, QStringLiteral("currentIndex"));
    decayComboBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, decayOffset);
    decayComboBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    mainlyt->addWidget(decayComboBox, 3, 1);

    mainlyt->setRowStretch(4, 16);

    setLayout(mainlyt);
}
