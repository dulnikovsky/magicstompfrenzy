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
#include "distortiondelaywidget.h"

#include <QGridLayout>
#include <QDoubleSpinBox>
#include <QLabel>
#include <QSpinBox>
#include <QComboBox>

DistortionDelayWidget::DistortionDelayWidget( bool distortionOnly, QWidget *parent) :
    EffectEditBaseWidget(parent)
{
    QSpinBox *spinBox;
    QDoubleSpinBox *dspinBox;
    QGridLayout *mainlyt = new QGridLayout();

    QGroupBox *distortionGroupBox = new QGroupBox(QStringLiteral("Distortion"));
    QGridLayout *distortionlayout = new QGridLayout();

    distortionlayout->addWidget(new QLabel(tr("Type")), 0, 0);
    QComboBox *distComboBox = new QComboBox();
    distComboBox->addItem(QStringLiteral("Distortion 1"));
    distComboBox->addItem(QStringLiteral("Distortion 2"));
    distComboBox->addItem(QStringLiteral("Over Drive 1"));
    distComboBox->addItem(QStringLiteral("Over Drive 2"));
    distComboBox->addItem(QStringLiteral("Crunch"));
    distComboBox->setCurrentIndex(-1);
    distComboBox->setProperty( ArrayDataEditWidget::valuePropertyName, QStringLiteral("currentIndex"));
    distComboBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, Type);
    distComboBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    distortionlayout->addWidget( distComboBox, 1, 0);

    distortionlayout->addWidget(new QLabel(tr("Drive")), 0, 1);
    spinBox = new QSpinBox();
    spinBox->setMinimum(0);
    spinBox->setMaximum(100);
    spinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, Drive);
    spinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    distortionlayout->addWidget(spinBox, 1, 1);

    distortionlayout->addWidget(new QLabel(tr("Master")), 0, 2);
    spinBox = new QSpinBox();
    spinBox->setMinimum(0);
    spinBox->setMaximum(100);
    spinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, Master);
    spinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    distortionlayout->addWidget(spinBox, 1, 2);

    distortionlayout->addWidget(new QLabel(tr("Tone")), 0, 3);
    spinBox = new QSpinBox();
    spinBox->setMinimum(-10);
    spinBox->setMaximum(10);
    spinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, Tone);
    spinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    spinBox->setProperty( ArrayDataEditWidget::convertMethodProperty, QStringLiteral("scaleAndAdd( 1, -10)"));
    distortionlayout->addWidget(spinBox, 1, 3);

    distortionlayout->addWidget(new QLabel(tr("Noise Gate")), 0, 4);
    spinBox = new QSpinBox();
    spinBox->setMinimum(0);
    spinBox->setMaximum(20);
    spinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, NoiseGate);
    spinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    distortionlayout->addWidget(spinBox, 1, 4);

    distortionGroupBox->setLayout(distortionlayout);

    mainlyt->addWidget(distortionGroupBox, 0, 0);

    if(! distortionOnly)
    {
        QGroupBox *delayGroupBox = new QGroupBox(QStringLiteral("Delay"));
        QGridLayout *delaylayout = new QGridLayout();

        delaylayout->addWidget(new QLabel(tr("Time")), 0, 0);
        dspinBox = new QDoubleSpinBox();
        dspinBox->setMinimum(0.0);
        dspinBox->setMaximum(2725.0);
        dspinBox->setSingleStep(0.2);
        dspinBox->setDecimals(1);
        dspinBox->setSuffix(" ms");
        dspinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, DelayTime);
        dspinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 2);
        dspinBox->setProperty( ArrayDataEditWidget::convertMethodProperty, QStringLiteral("scaleAndAdd(0.2, 0)"));
        delaylayout->addWidget(dspinBox, 1, 0);

        delaylayout->addWidget(new QLabel(tr("Feedback Gain")), 0, 1);
        spinBox = new QSpinBox();
        spinBox->setMinimum(-99);
        spinBox->setMaximum(99);
        spinBox->setSuffix(QStringLiteral(" %"));
        spinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, FeedbackGain);
        spinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 2);
        spinBox->setProperty( ArrayDataEditWidget::convertMethodProperty, QStringLiteral("scaleAndAdd(1, -99)"));
        delaylayout->addWidget(spinBox, 1, 1);

        delaylayout->addWidget(new QLabel(tr("Mod. Freq")), 0, 2);
        dspinBox = new QDoubleSpinBox();
        dspinBox->setMinimum(0.05);
        dspinBox->setMaximum(40.0);
        dspinBox->setSingleStep(0.05);
        dspinBox->setDecimals(2);
        dspinBox->setSuffix(" Hz");
        dspinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, ModFreq);
        dspinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 2);
        dspinBox->setProperty( ArrayDataEditWidget::convertMethodProperty, QStringLiteral("scaleAndAdd(0.05, 0.05)"));
        delaylayout->addWidget(dspinBox, 1, 2);

        delaylayout->addWidget(new QLabel(tr("Mod. Depth")), 0, 3);
        spinBox = new QSpinBox();
        spinBox->setMinimum(0);
        spinBox->setMaximum(100);
        spinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, Depth);
        spinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
        delaylayout->addWidget(spinBox, 1, 3);

        delaylayout->addWidget(new QLabel(tr("High Ratio")), 0, 4);
        dspinBox = new QDoubleSpinBox();
        dspinBox->setMinimum(0.1);
        dspinBox->setMaximum(1.0);
        dspinBox->setSingleStep(0.1);
        dspinBox->setDecimals(1);
        dspinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, HighRatio);
        dspinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
        dspinBox->setProperty( ArrayDataEditWidget::convertMethodProperty, QStringLiteral("scaleAndAdd(0.1, 0.1)"));
        delaylayout->addWidget(dspinBox, 1, 4);

        delaylayout->addWidget(new QLabel(tr("Balance")), 0, 5);
        spinBox = new QSpinBox();
        spinBox->setMinimum(0);
        spinBox->setMaximum(100);
        spinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, Balance);
        spinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
        delaylayout->addWidget(spinBox, 1, 5);

        delayGroupBox->setLayout(delaylayout);

        mainlyt->addWidget(delayGroupBox, 1, 0);
    }

    setLayout(mainlyt);
}
