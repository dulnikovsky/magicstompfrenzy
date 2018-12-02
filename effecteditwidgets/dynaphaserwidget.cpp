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
#include "dynaphaserwidget.h"

#include <QGridLayout>
#include <QLabel>
#include <QSpinBox>
#include <QComboBox>
#include "freqspinbox.h"

DynaPhaserWidget::DynaPhaserWidget( QWidget *parent) :
    EffectEditBaseWidget(parent)
{
    QSpinBox *spinBox;
    QDoubleSpinBox *dspinBox;

    QGridLayout *mainlyt = new QGridLayout();

    mainlyt->addWidget(new QLabel(tr("Mix")), 0, 0);
    spinBox = new QSpinBox();
    spinBox->setMinimum(0);
    spinBox->setMaximum(100);
    spinBox->setSuffix(" %");
    spinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, Mix);
    spinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    mainlyt->addWidget(spinBox, 1, 0);

    mainlyt->addWidget(new QLabel(tr("Decay(?)")), 0, 1);
    spinBox = createStandardRawSpinBox( Decay, 0, 0xFF);
    spinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 2);
    mainlyt->addWidget( spinBox, 1, 1);

    mainlyt->addWidget(new QLabel(tr("Feedback Gain")), 0, 2);
    spinBox = createStandardRawSpinBox( FeedbackGain, -99, 99, 2);
    spinBox->setProperty( ArrayDataEditWidget::convertMethodProperty, QStringLiteral("scaleAndAdd(1, -99)"));
    mainlyt->addWidget(spinBox, 1, 2);

    mainlyt->addWidget(new QLabel(tr("Direction")), 0, 3);
    QComboBox *dirComboBox = new QComboBox();
    dirComboBox->addItem(QStringLiteral("Up"));
    dirComboBox->addItem(QStringLiteral("Down"));
    dirComboBox->setCurrentIndex(-1);
    dirComboBox->setProperty( ArrayDataEditWidget::valuePropertyName, QStringLiteral("currentIndex"));
    dirComboBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, Direction);
    dirComboBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    mainlyt->addWidget( dirComboBox, 1, 3);

    mainlyt->addWidget(new QLabel(tr("Sense")), 2, 0);
    spinBox = createStandardRawSpinBox( Sense, 0, 100);
    mainlyt->addWidget(spinBox, 3, 0);

    mainlyt->addWidget(new QLabel(tr("Offset")), 2, 1);
    spinBox = createStandardRawSpinBox( Offset, 0, 100);
    mainlyt->addWidget( spinBox, 3, 1);

    mainlyt->addWidget(new QLabel(tr("LSH Freq")), 2, 2);
    FreqSpinBox *lshspinBox = new FreqSpinBox();
    lshspinBox->setParameters( 21.2, 8000.0, 0, 0x67);
    lshspinBox->setSuffix(QStringLiteral(" Hz"));
    lshspinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, LSHFreq);
    lshspinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    mainlyt->addWidget(lshspinBox, 3, 2);

    mainlyt->addWidget(new QLabel(tr("LSH Gain")), 2, 3);
    dspinBox = new QDoubleSpinBox();
    dspinBox->setMinimum(-12.0);
    dspinBox->setMaximum(12.0);
    dspinBox->setSingleStep(0.5);
    dspinBox->setDecimals(1);
    dspinBox->setSuffix(QStringLiteral(" dB"));
    dspinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, LSHGain);
    dspinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    dspinBox->setProperty( ArrayDataEditWidget::convertMethodProperty, QStringLiteral("scaleAndAdd(0.5, -12.0)"));
    mainlyt->addWidget(dspinBox, 3, 3);

    mainlyt->addWidget(new QLabel(tr("HSH Freq")), 4, 2);
    FreqSpinBox *hshspinBox = new FreqSpinBox();
    hshspinBox->setParameters( 50.0, 16000.0, 0, 0x64);
    hshspinBox->setSuffix(QStringLiteral(" Hz"));
    hshspinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, HSHFreq);
    hshspinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    mainlyt->addWidget(hshspinBox, 5, 2);

    mainlyt->addWidget(new QLabel(tr("HSH Gain")), 4, 3);
    dspinBox = new QDoubleSpinBox();
    dspinBox->setMinimum(-12.0);
    dspinBox->setMaximum(12.0);
    dspinBox->setSingleStep(0.5);
    dspinBox->setDecimals(1);
    dspinBox->setSuffix(QStringLiteral(" dB"));
    dspinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, HSHGain);
    dspinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    dspinBox->setProperty( ArrayDataEditWidget::convertMethodProperty, QStringLiteral("scaleAndAdd(0.5, -12.0)"));
    mainlyt->addWidget(dspinBox, 5, 3);

    mainlyt->addWidget(new QLabel(tr("Stage")), 4, 0);
    spinBox = new QSpinBox();
    spinBox->setMinimum(2);
    spinBox->setMaximum(16);
    spinBox->setSingleStep(2);
    spinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, Stage);
    spinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    spinBox->setProperty( ArrayDataEditWidget::convertMethodProperty, QStringLiteral("scaleAndAdd(2, 2)"));
    mainlyt->addWidget(spinBox, 5, 0);

    setLayout(mainlyt);
}
