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
#include "echowidget.h"
#include "hpfspinbox.h"
#include "lpfspinbox.h"
#include <QGridLayout>
#include <QDoubleSpinBox>
#include <QLabel>
#include <QSpinBox>
#include <QGroupBox>

EchoWidget::EchoWidget(QWidget *parent) :
    EffectEditBaseWidget(parent)
{
    QSpinBox *spinBox;
    QDoubleSpinBox *dspinBox;
    QGridLayout *mainlyt = new QGridLayout();

    mainlyt->addWidget(new QLabel(tr("Delay Left")), 0, 0);
    dspinBox = new QDoubleSpinBox();
    dspinBox->setMinimum(0.0);
    dspinBox->setMaximum(1350.0);
    dspinBox->setSingleStep(0.1);
    dspinBox->setDecimals(1);
    dspinBox->setSuffix(" ms");
    dspinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, DelayTimeL);
    dspinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 2);
    dspinBox->setProperty( ArrayDataEditWidget::convertMethodProperty, QStringLiteral("scaleAndAdd(0.1, 0)"));
    mainlyt->addWidget(dspinBox, 1, 0);

    mainlyt->addWidget(new QLabel(tr("FB Delay Left")), 0, 1);
    dspinBox = new QDoubleSpinBox();
    dspinBox->setMinimum(0.0);
    dspinBox->setMaximum(1350.0);
    dspinBox->setSingleStep(0.1);
    dspinBox->setDecimals(1);
    dspinBox->setSuffix(" ms");
    dspinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, FBDelayL);
    dspinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 2);
    dspinBox->setProperty( ArrayDataEditWidget::convertMethodProperty, QStringLiteral("scaleAndAdd(0.1, 0)"));
    mainlyt->addWidget(dspinBox, 1, 1);

    mainlyt->addWidget(new QLabel(tr("FB Gain Left")), 0, 2);
    spinBox = new QSpinBox();
    spinBox->setMinimum(-100);
    spinBox->setMaximum(100);
    spinBox->setSingleStep(2);
    spinBox->setSuffix(QStringLiteral(" %"));
    spinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, FBGainL);
    spinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    spinBox->setProperty( ArrayDataEditWidget::convertMethodProperty, QStringLiteral("scaleAndAdd(2, -100)"));
    mainlyt->addWidget(spinBox, 1, 2);

    mainlyt->addWidget(new QLabel(tr("Delay Right")), 0, 3);
    dspinBox = new QDoubleSpinBox();
    dspinBox->setMinimum(0.0);
    dspinBox->setMaximum(1350.0);
    dspinBox->setSingleStep(0.1);
    dspinBox->setDecimals(1);
    dspinBox->setSuffix(" ms");
    dspinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, DelayTimeR);
    dspinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 2);
    dspinBox->setProperty( ArrayDataEditWidget::convertMethodProperty, QStringLiteral("scaleAndAdd(0.1, 0)"));
    mainlyt->addWidget(dspinBox, 1, 3);

    mainlyt->addWidget(new QLabel(tr("FB Delay Right")), 0, 4);
    dspinBox = new QDoubleSpinBox();
    dspinBox->setMinimum(0.0);
    dspinBox->setMaximum(1350.0);
    dspinBox->setSingleStep(0.1);
    dspinBox->setDecimals(1);
    dspinBox->setSuffix(" ms");
    dspinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, FBDelayR);
    dspinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 2);
    dspinBox->setProperty( ArrayDataEditWidget::convertMethodProperty, QStringLiteral("scaleAndAdd(0.1, 0)"));
    mainlyt->addWidget(dspinBox, 1, 4);

    mainlyt->addWidget(new QLabel(tr("FB Gain Right")), 0, 5);
    spinBox = new QSpinBox();
    spinBox->setMinimum(-100);
    spinBox->setMaximum(100);
    spinBox->setSingleStep(2);
    spinBox->setSuffix(QStringLiteral(" %"));
    spinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, FBGainR);
    spinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    spinBox->setProperty( ArrayDataEditWidget::convertMethodProperty, QStringLiteral("scaleAndAdd(2, -100)"));
    mainlyt->addWidget(spinBox, 1, 5);

    mainlyt->addWidget(new QLabel(tr("L->R Feedback Gain")), 2, 0);
    spinBox = new QSpinBox();
    spinBox->setMinimum(-100);
    spinBox->setMaximum(100);
    spinBox->setSingleStep(2);
    spinBox->setSuffix(QStringLiteral(" %"));
    spinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, L_RFeedbackGain);
    spinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    spinBox->setProperty( ArrayDataEditWidget::convertMethodProperty, QStringLiteral("scaleAndAdd(2, -100)"));
    mainlyt->addWidget(spinBox, 3, 0);

    mainlyt->addWidget(new QLabel(tr("R->L Feedback Gain")), 2, 1);
    spinBox = new QSpinBox();
    spinBox->setMinimum(-100);
    spinBox->setMaximum(100);
    spinBox->setSingleStep(2);
    spinBox->setSuffix(QStringLiteral(" %"));
    spinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, R_LFeedbackGain);
    spinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    spinBox->setProperty( ArrayDataEditWidget::convertMethodProperty, QStringLiteral("scaleAndAdd(2, -100)"));
    mainlyt->addWidget(spinBox, 3, 1);

    mainlyt->addWidget(new QLabel(tr("High Ratio")), 2, 2);
    dspinBox = new QDoubleSpinBox();
    dspinBox->setMinimum(0.1);
    dspinBox->setMaximum(1.0);
    dspinBox->setSingleStep(0.1);
    dspinBox->setDecimals(1);
    dspinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, HighRatio);
    dspinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    dspinBox->setProperty( ArrayDataEditWidget::convertMethodProperty, QStringLiteral("scaleAndAdd(0.1, 0.1)"));
    mainlyt->addWidget(dspinBox, 3, 2);

    mainlyt->addWidget(new QLabel(tr("High Pass Filter")), 2, 3);
    HpfSpinBox *hpfSpinBox = new HpfSpinBox();
    hpfSpinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, HPF);
    hpfSpinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    mainlyt->addWidget(hpfSpinBox, 3, 3);

    mainlyt->addWidget(new QLabel(tr("Low Pass Filter")), 2, 4);
    LpfSpinBox *lpfSpinBox = new LpfSpinBox();
    lpfSpinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, LPF);
    lpfSpinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    mainlyt->addWidget(lpfSpinBox, 3, 4);

    mainlyt->addWidget(new QLabel(tr("Mix")), 2, 5);
    spinBox = new QSpinBox();
    spinBox->setMinimum(0);
    spinBox->setMaximum(100);
    spinBox->setSuffix(" %");
    spinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, Mix);
    spinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    mainlyt->addWidget(spinBox, 3, 5);

    mainlyt->setRowStretch( 4,2);

    setLayout(mainlyt);
}
