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
#include "reverbchoruswidget.h"
#include "reverbmultiwidget.h"
#include <QGridLayout>
#include <QDoubleSpinBox>
#include <QLabel>
#include <QSpinBox>
#include <QComboBox>

ReverbChorusWidget::ReverbChorusWidget(bool isParallel, QWidget *parent) :
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

    if(isParallel)
        mainlyt->addWidget(new QLabel(tr("Reverb/Chorus")), 0, 1);
    else
        mainlyt->addWidget(new QLabel(tr("Reverb Balance")), 0, 1);
    spinBox = new QSpinBox();
    spinBox->setMinimum(0);
    spinBox->setMaximum(100);
    spinBox->setSuffix(" %");
    spinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, Balance);
    spinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    mainlyt->addWidget(spinBox, 1, 1);

    QGroupBox *chorusGroupBox = new QGroupBox("Chorus");
    QGridLayout *chorusLayout = new QGridLayout();

    chorusLayout->addWidget(new QLabel(tr("Wave")), 0, 0);
    QComboBox *waveComboBox = new QComboBox();
    waveComboBox->addItem(QStringLiteral("Sine"));
    waveComboBox->addItem(QStringLiteral("Triangle"));
    waveComboBox->setCurrentIndex(-1);
    waveComboBox->setProperty( ArrayDataEditWidget::valuePropertyName, QStringLiteral("currentIndex"));
    waveComboBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, Wave);
    waveComboBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    chorusLayout->addWidget( waveComboBox, 1, 0);

    chorusLayout->addWidget(new QLabel(tr("Freq")), 0, 1);
    dspinBox = new QDoubleSpinBox();
    dspinBox->setMinimum(0.05);
    dspinBox->setMaximum(40.0);
    dspinBox->setSingleStep(0.05);
    dspinBox->setDecimals(2);
    dspinBox->setSuffix(" Hz");
    dspinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, Freq);
    dspinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 2);
    dspinBox->setProperty( ArrayDataEditWidget::convertMethodProperty, QStringLiteral("scaleAndAdd(0.05, 0.05)"));
    chorusLayout->addWidget(dspinBox, 1, 1);

    chorusLayout->addWidget(new QLabel(tr("Mod Delay")), 0, 2);
    dspinBox = new QDoubleSpinBox();
    dspinBox->setMinimum(0.0);
    dspinBox->setMaximum(500.0);
    dspinBox->setSingleStep(0.1);
    dspinBox->setDecimals(1);
    dspinBox->setSuffix(" ms");
    dspinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, ModDelay);
    dspinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 2);
    dspinBox->setProperty( ArrayDataEditWidget::convertMethodProperty, QStringLiteral("scaleAndAdd(0.1, 0)"));
    chorusLayout->addWidget(dspinBox, 1, 2);

    chorusLayout->addWidget(new QLabel(tr("AM Depth")), 2, 0);
    spinBox = new QSpinBox();
    spinBox->setMinimum(0);
    spinBox->setMaximum(100);
    spinBox->setSuffix(" %");
    spinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, AMDepth);
    spinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    chorusLayout->addWidget(spinBox, 3, 0);

    chorusLayout->addWidget(new QLabel(tr("PM Depth")), 2, 1);
    spinBox = new QSpinBox();
    spinBox->setMinimum(0);
    spinBox->setMaximum(100);
    spinBox->setSuffix(" %");
    spinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, PMDepth);
    spinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    chorusLayout->addWidget(spinBox, 3, 1);

    chorusGroupBox->setLayout(chorusLayout);

    mainlyt->addWidget(new ReverbMultiWidget(), 2, 0, 1, 2);
    mainlyt->addWidget(chorusGroupBox, 3, 0, 1, 2);

    setLayout(mainlyt);
}
