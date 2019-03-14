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
#include "ampmultidelaywidget.h"
#include "ampmultiwidget.h"
#include <QGridLayout>
#include <QDoubleSpinBox>
#include <QLabel>
#include <QSpinBox>
#include "hpfspinbox.h"
#include "lpfspinbox.h"

AmpMultiDelayWidget::AmpMultiDelayWidget(QWidget *parent) :
    EffectEditBaseWidget(parent)
{
    setTitle(tr("Delay"));

    QDoubleSpinBox *dspinBox;
    QSpinBox *spinBox;
    QGridLayout *mainlyt = new QGridLayout();

    mainlyt->addWidget(new QLabel(tr("Level")), 0, 0);
    dspinBox = createStandard10DblSpinBox( AmpMultiWidget::DelayLevel);
    mainlyt->addWidget(dspinBox, 1, 0);

    mainlyt->addWidget(new QLabel(tr("Feedback")), 2, 0);
    dspinBox = new QDoubleSpinBox();
    dspinBox->setSuffix(QStringLiteral(" ms"));
    dspinBox->setMinimum(0.0);
    dspinBox->setMaximum(1000.0);
    dspinBox->setSingleStep(0.1);
    dspinBox->setDecimals(1);
    dspinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, AmpMultiWidget::DelayFeedback);
    dspinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 2);
    dspinBox->setProperty( ArrayDataEditWidget::convertMethodProperty, QStringLiteral("scaleAndAdd(0.1, 0)"));
    mainlyt->addWidget(dspinBox, 3, 0);

    mainlyt->addWidget(new QLabel(tr("Tap L")), 0, 1);
    spinBox = createStandardRawSpinBox(AmpMultiWidget::DelayTapL, 0, 100);
    mainlyt->addWidget(spinBox, 1, 1);

    mainlyt->addWidget(new QLabel(tr("Tap R")), 0, 2);
    spinBox = createStandardRawSpinBox( AmpMultiWidget::DelayTapR, 0, 100);
    mainlyt->addWidget(spinBox, 1, 2);

    mainlyt->addWidget(new QLabel(tr("Feedback Gain")), 2, 1);
    spinBox = new QSpinBox();
    spinBox->setMinimum(-99);
    spinBox->setMaximum(99);
    spinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, AmpMultiWidget::DelayFeedbackGain);
    spinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    spinBox->setProperty( ArrayDataEditWidget::convertMethodProperty, QStringLiteral("scaleAndAdd(2, -99)")); //TODO check rounding
    mainlyt->addWidget(spinBox, 3, 1);

    mainlyt->addWidget(new QLabel(tr("High")), 2, 2);
    dspinBox = new QDoubleSpinBox();
    dspinBox->setMinimum(0.0);
    dspinBox->setMaximum(1.0);
    dspinBox->setSingleStep(0.1);
    dspinBox->setDecimals(1);
    dspinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, AmpMultiWidget::DelayHeigh);
    dspinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    dspinBox->setProperty( ArrayDataEditWidget::convertMethodProperty, QStringLiteral("scaleAndAdd(0.1, 0)"));
    mainlyt->addWidget(dspinBox, 3, 2);

    mainlyt->addWidget(new QLabel(tr("HPF")), 0, 4);
    HpfSpinBox *hpfSpinBox = new HpfSpinBox();
    hpfSpinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, AmpMultiWidget::DelayHPF);
    hpfSpinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    mainlyt->addWidget(hpfSpinBox, 1, 4);

    mainlyt->addWidget(new QLabel(tr("LPF")), 2, 4);
    LpfSpinBox *lpfSpinBox = new LpfSpinBox();
    lpfSpinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, AmpMultiWidget::DelayLPF);
    lpfSpinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    mainlyt->addWidget(lpfSpinBox, 3, 4);

    setLayout(mainlyt);
}
