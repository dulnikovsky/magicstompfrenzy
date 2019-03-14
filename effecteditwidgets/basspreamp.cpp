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
#include "basspreamp.h"
#include "magicstomptext.h"
#include "bassfreqspinbox.h"
#include <QLabel>
#include <QGridLayout>
#include <QDoubleSpinBox>
#include <QSpinBox>
#include "compressorreleasecombobox.h"

BassPreampWidget::BassPreampWidget( QWidget *parent) :
    EffectEditBaseWidget(parent)
{
    QDoubleSpinBox *dspinBox;
    FreqSpinBox *freqSpinBox;
    QSpinBox *spinBox;
    QGridLayout *mainlyt = new QGridLayout();

    mainlyt->addWidget(new QLabel(tr("Preamp Type")), 0, 0, 1, 2);
    QComboBox *speakerComboBox = new QComboBox();
    speakerComboBox->addItems( BassPreampTypeNameList);
    speakerComboBox->setCurrentIndex(-1);
    speakerComboBox->setProperty( ArrayDataEditWidget::valuePropertyName, QStringLiteral("currentIndex"));
    speakerComboBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, Type);
    speakerComboBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    mainlyt->addWidget( speakerComboBox, 1, 0);

    mainlyt->addWidget(new QLabel(tr("Gain")), 2, 0);
    dspinBox = new QDoubleSpinBox();
    dspinBox->setMinimum(0.0);
    dspinBox->setMaximum(10.0);
    dspinBox->setSingleStep(0.1);
    dspinBox->setDecimals(1);
    dspinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, Gain);
    dspinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 2);
    dspinBox->setProperty( ArrayDataEditWidget::convertMethodProperty, QStringLiteral("scaleAndAdd(0.1, 0)"));
    mainlyt->addWidget(dspinBox, 3, 0);

    mainlyt->addWidget(new QLabel(tr("Master")), 4, 0);
    dspinBox = new QDoubleSpinBox();
    dspinBox->setMinimum(0.0);
    dspinBox->setMaximum(10.0);
    dspinBox->setSingleStep(0.1);
    dspinBox->setDecimals(1);
    dspinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, Master);
    dspinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 2);
    dspinBox->setProperty( ArrayDataEditWidget::convertMethodProperty, QStringLiteral("scaleAndAdd(0.1, 0)"));
    mainlyt->addWidget(dspinBox, 5, 0);

    mainlyt->addWidget(new QLabel(tr("Bass")), 2, 1);
    dspinBox = createStdGainSpinBox(Bass);
    mainlyt->addWidget(dspinBox, 3, 1);

    mainlyt->addWidget(new QLabel(tr("Low Middle")), 2, 2);
    dspinBox = createStdGainSpinBox(LowMiddle);
    mainlyt->addWidget(dspinBox, 3, 2);

    mainlyt->addWidget(new QLabel(tr("Middle")), 2, 3);
    dspinBox = createStdGainSpinBox(Middle);
    mainlyt->addWidget(dspinBox, 3, 3);

    mainlyt->addWidget(new QLabel(tr("High Middle")), 2, 4);
    dspinBox = createStdGainSpinBox(HighMiddle);
    mainlyt->addWidget(dspinBox, 3, 4);

    mainlyt->addWidget(new QLabel(tr("Treble")), 2, 5);
    dspinBox = createStdGainSpinBox(Treble);
    mainlyt->addWidget(dspinBox, 3, 5);

    mainlyt->addWidget(new QLabel(tr("Bass Freq")), 4, 1);
    BassFreqSpinBox *bfreqSpinBox = new BassFreqSpinBox();
    bfreqSpinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, BassFreq);
    bfreqSpinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    mainlyt->addWidget(bfreqSpinBox, 5, 1);

    mainlyt->addWidget(new QLabel(tr("Low Mid Freq")), 4, 2);
    freqSpinBox = new FreqSpinBox();
    freqSpinBox->setParameters(80.0, 1280.0);
    freqSpinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, LowMidFreq);
    freqSpinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    mainlyt->addWidget(freqSpinBox, 5, 2);

    mainlyt->addWidget(new QLabel(tr("Middle Freq")), 4, 3);
    freqSpinBox = new FreqSpinBox();
    freqSpinBox->setParameters(250.0, 4000.0);
    freqSpinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, MiddleFreq);
    freqSpinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    mainlyt->addWidget(freqSpinBox, 5, 3);

    mainlyt->addWidget(new QLabel(tr("High Mid Freq")), 4, 4);
    freqSpinBox = new FreqSpinBox();
    freqSpinBox->setParameters(500.0, 8000.0);
    freqSpinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, HighMidFreq);
    freqSpinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    mainlyt->addWidget(freqSpinBox, 5, 4);

    mainlyt->addWidget(new QLabel(tr("Treble Freq")), 4, 5);
    freqSpinBox = new FreqSpinBox();
    freqSpinBox->setParameters(1250.0, 20000.0);
    freqSpinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, TrebleFreq);
    freqSpinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    mainlyt->addWidget(freqSpinBox, 5, 5);

    mainlyt->addWidget(new QLabel(tr("Parametric EQ Freq")), 6, 0);
    freqSpinBox = new FreqSpinBox();
    freqSpinBox->setParameters(20.0, 20000.0, 0, 0xFF);
    freqSpinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, ParametricEQFreq);
    freqSpinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 2);
    mainlyt->addWidget(freqSpinBox, 7, 0);

    mainlyt->addWidget(new QLabel(tr("Parametric EQ Q")), 6, 1);
    ExpSpinBox *extSpinBox = new ExpSpinBox();
    extSpinBox->setParameters(0.1, 20.0);
    extSpinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, ParametricEQQ);
    extSpinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    mainlyt->addWidget(extSpinBox, 7, 1);

    mainlyt->addWidget(new QLabel(tr("Parametric EQ Gain")), 6, 2);
    dspinBox = createStdGainSpinBox(ParametricEQGain);
    mainlyt->addWidget(dspinBox, 7, 2);

    mainlyt->addWidget(new QLabel(tr("Gate")), 6, 3);
    spinBox = new QSpinBox();
    spinBox->setMinimum(-54);
    spinBox->setMaximum(0);
    spinBox->setSpecialValueText(QStringLiteral("Off"));
    spinBox->setSuffix(QStringLiteral(" dB"));
    spinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, Gate);
    spinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    spinBox->setProperty( ArrayDataEditWidget::convertMethodProperty, QStringLiteral("scaleAndAdd(1, -54)"));
    mainlyt->addWidget(spinBox, 7, 3);

    mainlyt->addWidget(new QLabel(tr("Speaker Simulation")), 6, 4);
    QComboBox *spkSimComboBox = new QComboBox();
    spkSimComboBox->addItems( BassPreampSpeakerSimNameList);
    spkSimComboBox->setCurrentIndex(-1);
    spkSimComboBox->setProperty( ArrayDataEditWidget::valuePropertyName, QStringLiteral("currentIndex"));
    spkSimComboBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, SpeakerSimulatorSwitch);
    spkSimComboBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    mainlyt->addWidget( spkSimComboBox, 7, 4);

    mainlyt->addWidget(new QLabel(tr("Limiter")), 6, 5);
    QComboBox *limiterComboBox = new QComboBox();
    limiterComboBox->addItems( OffOnStringList);
    limiterComboBox->setCurrentIndex(-1);
    limiterComboBox->setProperty( ArrayDataEditWidget::valuePropertyName, QStringLiteral("currentIndex"));
    limiterComboBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, Limiter);
    limiterComboBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    mainlyt->addWidget( limiterComboBox, 7, 5);

    mainlyt->addWidget(new QLabel(tr("Comp. Ratio")), 8, 0);
    QComboBox *compRatioComboBox = new QComboBox();
    compRatioComboBox->addItem(QStringLiteral("1 : 1"));
    compRatioComboBox->addItem(QStringLiteral("1.1 : 1"));
    compRatioComboBox->addItem(QStringLiteral("1.3 : 1"));
    compRatioComboBox->addItem(QStringLiteral("1.5 : 1"));
    compRatioComboBox->addItem(QStringLiteral("1.7 : 1"));
    compRatioComboBox->addItem(QStringLiteral("2 : 1"));
    compRatioComboBox->addItem(QStringLiteral("2.5 : 1"));
    compRatioComboBox->addItem(QStringLiteral("3 : 1"));
    compRatioComboBox->addItem(QStringLiteral("3.5 : 1"));
    compRatioComboBox->addItem(QStringLiteral("4 : 1"));
    compRatioComboBox->addItem(QStringLiteral("5 : 1"));
    compRatioComboBox->addItem(QStringLiteral("6 : 1"));
    compRatioComboBox->addItem(QStringLiteral("8 : 1"));
    compRatioComboBox->addItem(QStringLiteral("10 : 1"));
    compRatioComboBox->addItem(QStringLiteral("20 : 1"));
    compRatioComboBox->addItem(QString::fromWCharArray(L"\x221e : 1"));
    compRatioComboBox->setCurrentIndex(-1);
    compRatioComboBox->setProperty( ArrayDataEditWidget::valuePropertyName, QStringLiteral("currentIndex"));
    compRatioComboBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, Ratio);
    compRatioComboBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    mainlyt->addWidget( compRatioComboBox, 9, 0);

    mainlyt->addWidget(new QLabel(tr("Comp. Threshold")), 8, 1);
    spinBox = new QSpinBox();
    spinBox->setMinimum(-54);
    spinBox->setMaximum(0);
    spinBox->setSuffix(QStringLiteral(" dB"));
    spinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, Threshold);
    spinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    spinBox->setProperty( ArrayDataEditWidget::convertMethodProperty, QStringLiteral("scaleAndAdd(1, -54)"));
    mainlyt->addWidget(spinBox, 9, 1);

    mainlyt->addWidget(new QLabel(tr("Comp. Attack")), 8, 2);
    spinBox = new QSpinBox();
    spinBox->setMinimum(0);
    spinBox->setMaximum(120);
    spinBox->setSuffix(QStringLiteral(" ms"));
    spinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, Attack);
    spinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    mainlyt->addWidget(spinBox, 9, 2);

    mainlyt->addWidget(new QLabel(tr("Comp. Release")), 8, 3);
    QComboBox *releaseComboBox = new CompressorReleaseComboBox();
    releaseComboBox->setProperty( ArrayDataEditWidget::valuePropertyName, QStringLiteral("currentIndex"));
    releaseComboBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, Release);
    releaseComboBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    mainlyt->addWidget(releaseComboBox, 9, 3);

    mainlyt->addWidget(new QLabel(tr("Comp. Gain")), 8, 4);
    dspinBox = new QDoubleSpinBox();
    dspinBox->setMinimum(0.0);
    dspinBox->setMaximum(18.0);
    dspinBox->setSingleStep(0.1);
    dspinBox->setDecimals(1);
    dspinBox->setSuffix(QStringLiteral(" dB"));
    dspinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, CompressorGain);
    dspinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    dspinBox->setProperty( ArrayDataEditWidget::convertMethodProperty, QStringLiteral("scaleAndAdd(0.1, 0)"));
    mainlyt->addWidget(dspinBox, 9, 4);

    mainlyt->addWidget(new QLabel(tr("Comp. Knee")), 8, 5);
    QComboBox *kneeComboBox = new QComboBox();
    kneeComboBox->addItem(QStringLiteral("Hard"));
    kneeComboBox->addItem(QStringLiteral("1"));
    kneeComboBox->addItem(QStringLiteral("2"));
    kneeComboBox->addItem(QStringLiteral("3"));
    kneeComboBox->addItem(QStringLiteral("4"));
    kneeComboBox->addItem(QStringLiteral("5"));
    kneeComboBox->setCurrentIndex(-1);
    kneeComboBox->setProperty( ArrayDataEditWidget::valuePropertyName, QStringLiteral("currentIndex"));
    kneeComboBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, Knee);
    kneeComboBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    mainlyt->addWidget(kneeComboBox, 9, 5);

    setLayout(mainlyt);
}

QDoubleSpinBox* BassPreampWidget::createStdGainSpinBox(int offset)
{
    QDoubleSpinBox *dspinBox = new QDoubleSpinBox();
    dspinBox->setMinimum(-15.0);
    dspinBox->setMaximum(15.0);
    dspinBox->setSingleStep(0.25);
    dspinBox->setDecimals(2);
    dspinBox->setSuffix(QStringLiteral(" dB"));
    dspinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, offset);
    dspinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    dspinBox->setProperty( ArrayDataEditWidget::convertMethodProperty, QStringLiteral("scaleAndAdd(0.25, -15.0)"));
    return dspinBox;
}
