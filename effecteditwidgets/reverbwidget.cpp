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
#include "reverbwidget.h"
#include "magicstomptext.h"
#include "reverbtimespinbox.h"
#include "hpfspinbox.h"
#include "lpfspinbox.h"
#include <QGridLayout>
#include <QDoubleSpinBox>
#include <QLabel>
#include <QSpinBox>
#include <QComboBox>
#include <QGroupBox>

ReverbWidget::ReverbWidget(QWidget *parent) :
    EffectEditBaseWidget(parent)
{
    QSpinBox *spinBox;
    QDoubleSpinBox *dspinBox;
    QGridLayout *mainlyt = new QGridLayout();

    mainlyt->addWidget(new QLabel(tr("Type")), 0, 0);
    QComboBox *typeComboBox = new QComboBox();
    typeComboBox->addItems( ReverbTypeNameList);
    typeComboBox->setCurrentIndex(-1);
    typeComboBox->setProperty( ArrayDataEditWidget::valuePropertyName, QStringLiteral("currentIndex"));
    typeComboBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, Type);
    typeComboBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    mainlyt->addWidget( typeComboBox, 1, 0);

    mainlyt->addWidget(new QLabel(tr("Mix")), 0, 1);
    spinBox = new QSpinBox();
    spinBox->setMinimum(0);
    spinBox->setMaximum(100);
    spinBox->setSuffix(" %");
    spinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, Mix);
    spinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    mainlyt->addWidget(spinBox, 1, 1);

    mainlyt->addWidget(new QLabel(tr("Time")), 0, 2);
    ReverbTimeSpinBox *revTimeSpinBox = new ReverbTimeSpinBox();
    revTimeSpinBox->setParameters(0, 0x53);
    revTimeSpinBox->setSuffix(" s");
    revTimeSpinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, Time);
    revTimeSpinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 2);
    mainlyt->addWidget(revTimeSpinBox, 1, 2);

    mainlyt->addWidget(new QLabel(tr("Diffusion")), 0, 3);
    spinBox = new QSpinBox();
    spinBox->setMinimum(0);
    spinBox->setMaximum(10);
    spinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, Diffusion);
    spinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    mainlyt->addWidget(spinBox, 1, 3);

    mainlyt->addWidget(new QLabel(tr("Density")), 0, 4);
    spinBox = new QSpinBox();
    spinBox->setMinimum(0);
    spinBox->setMaximum(100);
    spinBox->setSuffix(" %");
    spinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, Density);
    spinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    mainlyt->addWidget(spinBox, 1, 4);

    mainlyt->addWidget(new QLabel(tr("Init Delay")), 0, 5);
    dspinBox = new QDoubleSpinBox();
    dspinBox->setMinimum(0.0);
    dspinBox->setMaximum(500.0);
    dspinBox->setSingleStep(0.1);
    dspinBox->setDecimals(1);
    dspinBox->setSuffix(" ms");
    dspinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, InitDelay);
    dspinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 2);
    dspinBox->setProperty( ArrayDataEditWidget::convertMethodProperty, QStringLiteral("scaleAndAdd(0.1, 0)"));
    mainlyt->addWidget(dspinBox, 1, 5);

    mainlyt->addWidget(new QLabel(tr("High Ratio")), 2, 0);
    dspinBox = new QDoubleSpinBox();
    dspinBox->setMinimum(0.1);
    dspinBox->setMaximum(1.0);
    dspinBox->setSingleStep(0.1);
    dspinBox->setDecimals(1);
    dspinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, HighRatio);
    dspinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 2);
    dspinBox->setProperty( ArrayDataEditWidget::convertMethodProperty, QStringLiteral("scaleAndAdd(0.1, 0.1)"));
    mainlyt->addWidget(dspinBox, 3, 0);

    mainlyt->addWidget(new QLabel(tr("Low Ratio")), 2, 1);
    dspinBox = new QDoubleSpinBox();
    dspinBox->setMinimum(0.1);
    dspinBox->setMaximum(2.4);
    dspinBox->setSingleStep(0.1);
    dspinBox->setDecimals(1);
    dspinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, LowRatio);
    dspinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    dspinBox->setProperty( ArrayDataEditWidget::convertMethodProperty, QStringLiteral("scaleAndAdd(0.1, 0.1)"));
    mainlyt->addWidget(dspinBox, 3, 1);

    mainlyt->addWidget(new QLabel(tr("ER/Rev. Delay")), 2, 2);
    dspinBox = new QDoubleSpinBox();
    dspinBox->setMinimum(0.0);
    dspinBox->setMaximum(100.0);
    dspinBox->setSingleStep(0.1);
    dspinBox->setDecimals(1);
    dspinBox->setSuffix(" ms");
    dspinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, ERRevDelay);
    dspinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 2);
    dspinBox->setProperty( ArrayDataEditWidget::convertMethodProperty, QStringLiteral("scaleAndAdd(0.1, 0)"));
    mainlyt->addWidget(dspinBox, 3, 2);

    mainlyt->addWidget(new QLabel(tr("ER/Rev. Balance")), 2, 3);
    spinBox = new QSpinBox();
    spinBox->setMinimum(0);
    spinBox->setMaximum(100);
    spinBox->setSuffix(" %");
    spinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, ERRevBalance);
    spinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    mainlyt->addWidget(spinBox, 3, 3);

    mainlyt->addWidget(new QLabel(tr("High Pass Filter")), 2, 4);
    HpfSpinBox *hpfSpinBox = new HpfSpinBox();
    hpfSpinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, HPF);
    hpfSpinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    mainlyt->addWidget(hpfSpinBox, 3, 4);

    mainlyt->addWidget(new QLabel(tr("Low Pass Filter")), 2, 5);
    LpfSpinBox *lpfSpinBox = new LpfSpinBox();
    lpfSpinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, LPF);
    lpfSpinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    mainlyt->addWidget(lpfSpinBox, 3, 5);

    QGroupBox *gateGroupBox = new QGroupBox("Gate");
    QGridLayout *gateLayout = new QGridLayout();

    gateLayout->addWidget(new QLabel(tr("Level")), 0, 0);
    spinBox = new QSpinBox();
    spinBox->setMinimum(-61);
    spinBox->setMaximum(0);
    spinBox->setSuffix(" dB");
    spinBox->setSpecialValueText(QStringLiteral("Off"));
    spinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, GateLevel);
    spinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    spinBox->setProperty( ArrayDataEditWidget::convertMethodProperty, QStringLiteral("scaleAndAdd(1, -61)"));
    gateLayout->addWidget(spinBox, 1, 0);

    gateLayout->addWidget(new QLabel(tr("Attack")), 0, 1);
    spinBox = new QSpinBox();
    spinBox->setMinimum(0);
    spinBox->setMaximum(120);
    spinBox->setSuffix(QStringLiteral(" ms"));
    spinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, GateAttack);
    spinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    gateLayout->addWidget(spinBox, 1, 1);

    gateLayout->addWidget(new QLabel(tr("Hold")), 0, 2);
    ExpSpinBox *holdSpinBox = new ExpSpinBox();
    holdSpinBox->setParameters(0.2, 2040.0, 0, 0x6B);
    holdSpinBox->setSuffix(QStringLiteral(" ms"));
    holdSpinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, GateHold);
    holdSpinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    gateLayout->addWidget(holdSpinBox, 1, 2);

    gateLayout->addWidget(new QLabel(tr("Decay(?)")), 0, 3);
    /*ExpSpinBox *decaySpinBox = new ExpSpinBox();
    decaySpinBox->setParameters(6.0, 44500.0, 0, 0x4F);
    decaySpinBox->setSuffix(QStringLiteral(" ms"));
    decaySpinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, GateDecay);
    decaySpinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    gateLayout->addWidget(decaySpinBox, 1, 3);*/

    spinBox = new QSpinBox();
    spinBox->setMinimum(0);
    spinBox->setMaximum(0x4F);
    spinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, GateDecay);
    spinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    gateLayout->addWidget(spinBox, 1, 3);


    gateGroupBox->setLayout(gateLayout);

    mainlyt->addWidget(gateGroupBox, 4, 0, 1, 6);

    setLayout(mainlyt);
}
