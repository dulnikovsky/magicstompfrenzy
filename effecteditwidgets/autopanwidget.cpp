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
#include "autopanwidget.h"
#include "freqspinbox.h"
#include <QGridLayout>
#include <QDoubleSpinBox>
#include <QLabel>
#include <QSpinBox>
#include <QComboBox>
#include <QGroupBox>

AutoPanWidget::AutoPanWidget(QWidget *parent) :
    EffectEditBaseWidget(parent)
{
    QSpinBox *spinBox;
    QDoubleSpinBox *dspinBox;
    QGridLayout *mainlyt = new QGridLayout();

    mainlyt->addWidget(new QLabel(tr("Wave")), 0, 0);
    QComboBox *waveComboBox = new QComboBox();
    waveComboBox->addItem(QStringLiteral("Sine"));
    waveComboBox->addItem(QStringLiteral("Triangle"));
    waveComboBox->addItem(QStringLiteral("Square"));
    waveComboBox->setCurrentIndex(-1);
    waveComboBox->setProperty( ArrayDataEditWidget::valuePropertyName, QStringLiteral("currentIndex"));
    waveComboBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, Wave);
    waveComboBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    mainlyt->addWidget( waveComboBox, 1, 0);

    mainlyt->addWidget(new QLabel(tr("Freq")), 0, 1);
    dspinBox = new QDoubleSpinBox();
    dspinBox->setMinimum(0.05);
    dspinBox->setMaximum(40.0);
    dspinBox->setSingleStep(0.05);
    dspinBox->setDecimals(2);
    dspinBox->setSuffix(" Hz");
    dspinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, Freq);
    dspinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 2);
    dspinBox->setProperty( ArrayDataEditWidget::convertMethodProperty, QStringLiteral("scaleAndAdd(0.05, 0.05)"));
    mainlyt->addWidget(dspinBox, 1, 1);

    mainlyt->addWidget(new QLabel(tr("Depth")), 0, 2);
    spinBox = new QSpinBox();
    spinBox->setMinimum(0);
    spinBox->setMaximum(100);
    spinBox->setSuffix(" %");
    spinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, Depth);
    spinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    mainlyt->addWidget(spinBox, 1, 2);

    mainlyt->addWidget(new QLabel(tr("Direction")), 0, 3);
    QComboBox *directionComboBox = new QComboBox();
    directionComboBox->addItem(QStringLiteral("L<--->R"));
    directionComboBox->addItem(QStringLiteral("L--->R"));
    directionComboBox->addItem(QStringLiteral("L<---R"));
    directionComboBox->addItem(QStringLiteral("Turn L"));
    directionComboBox->addItem(QStringLiteral("Turn R"));
    directionComboBox->setCurrentIndex(-1);
    directionComboBox->setProperty( ArrayDataEditWidget::valuePropertyName, QStringLiteral("currentIndex"));
    directionComboBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, Direction);
    directionComboBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    mainlyt->addWidget( directionComboBox, 1, 3);

    mainlyt->addWidget(new QLabel(tr("LSH Freq")), 0, 4);
    FreqSpinBox *lshspinBox = new FreqSpinBox();
    lshspinBox->setParameters( 21.2, 8000.0, 0, 0x67);
    lshspinBox->setSuffix(QStringLiteral(" Hz"));
    lshspinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, LSHFreq);
    lshspinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    mainlyt->addWidget(lshspinBox, 1, 4);

    mainlyt->addWidget(new QLabel(tr("LSH Gain")), 0, 5);
    dspinBox = new QDoubleSpinBox();
    dspinBox->setMinimum(-12.0);
    dspinBox->setMaximum(12.0);
    dspinBox->setSingleStep(0.5);
    dspinBox->setDecimals(1);
    dspinBox->setSuffix(QStringLiteral(" dB"));
    dspinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, LSHGain);
    dspinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    dspinBox->setProperty( ArrayDataEditWidget::convertMethodProperty, QStringLiteral("scaleAndAdd(0.5, -12.0)"));
    mainlyt->addWidget(dspinBox, 1, 5);

    mainlyt->addWidget(new QLabel(tr("HSH Freq")), 2, 4);
    FreqSpinBox *hshspinBox = new FreqSpinBox();
    hshspinBox->setParameters( 50.0, 16000.0, 0, 0x64);
    hshspinBox->setSuffix(QStringLiteral(" Hz"));
    hshspinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, HSHFreq);
    hshspinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    mainlyt->addWidget(hshspinBox, 3, 4);

    mainlyt->addWidget(new QLabel(tr("HSH Gain")), 2, 5);
    dspinBox = new QDoubleSpinBox();
    dspinBox->setMinimum(-12.0);
    dspinBox->setMaximum(12.0);
    dspinBox->setSingleStep(0.5);
    dspinBox->setDecimals(1);
    dspinBox->setSuffix(QStringLiteral(" dB"));
    dspinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, HSHGain);
    dspinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    dspinBox->setProperty( ArrayDataEditWidget::convertMethodProperty, QStringLiteral("scaleAndAdd(0.5, -12.0)"));
    mainlyt->addWidget(dspinBox, 3, 5);

    mainlyt->addWidget(new QLabel(tr("EQ Freq")), 2, 0);
    FreqSpinBox *eqFreqSpinBox = new FreqSpinBox();
    eqFreqSpinBox->setParameters( 100.0, 8000.0, 0, 0x4C);
    eqFreqSpinBox->setSuffix(QStringLiteral(" Hz"));
    eqFreqSpinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, EQFreq);
    eqFreqSpinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    mainlyt->addWidget(eqFreqSpinBox, 3, 0);

    mainlyt->addWidget(new QLabel(tr("EQ Gain")), 2, 1);
    dspinBox = new QDoubleSpinBox();
    dspinBox->setMinimum(-12.0);
    dspinBox->setMaximum(12.0);
    dspinBox->setSingleStep(0.5);
    dspinBox->setDecimals(1);
    dspinBox->setSuffix(QStringLiteral(" dB"));
    dspinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, EQGain);
    dspinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    dspinBox->setProperty( ArrayDataEditWidget::convertMethodProperty, QStringLiteral("scaleAndAdd(0.5, -12.0)"));
    mainlyt->addWidget(dspinBox, 3, 1);

    mainlyt->addWidget(new QLabel(tr("EQ Q(?)")), 2, 2);
    spinBox = new QSpinBox();
    spinBox->setMinimum(0);
    spinBox->setMaximum(0x28);
    spinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, EQQ);
    spinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    mainlyt->addWidget(spinBox, 3, 2);

    setLayout(mainlyt);
}
