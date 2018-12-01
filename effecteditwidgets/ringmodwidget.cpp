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
#include "ringmodwidget.h"

#include <QGridLayout>
#include <QDoubleSpinBox>
#include <QLabel>
#include <QSpinBox>
#include <QComboBox>

RingModWidget::RingModWidget( QWidget *parent) :
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

    mainlyt->addWidget(new QLabel(tr("Source")), 0, 1);
    QComboBox *rotateComboBox = new QComboBox();
    rotateComboBox->addItem(QStringLiteral("OSC"));
    rotateComboBox->addItem(QStringLiteral("Self"));
    rotateComboBox->setCurrentIndex(-1);
    rotateComboBox->setProperty( ArrayDataEditWidget::valuePropertyName, QStringLiteral("currentIndex"));
    rotateComboBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, Source);
    rotateComboBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    mainlyt->addWidget( rotateComboBox, 1, 1);

    mainlyt->addWidget(new QLabel(tr("OSC Freq")), 0, 2);
    dspinBox = new QDoubleSpinBox();
    dspinBox->setMinimum(0.00);
    dspinBox->setMaximum(5000.0);
    dspinBox->setSingleStep(0.5);
    dspinBox->setDecimals(1);
    dspinBox->setSuffix(" Hz");
    dspinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, OSCFreq);
    dspinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 2);
    dspinBox->setProperty( ArrayDataEditWidget::convertMethodProperty, QStringLiteral("scaleAndAdd(0.5, 0.0)"));
    mainlyt->addWidget(dspinBox, 1, 2);

    mainlyt->addWidget(new QLabel(tr("FM Freq")), 0, 3);
    dspinBox = new QDoubleSpinBox();
    dspinBox->setMinimum(0.05);
    dspinBox->setMaximum(40.0);
    dspinBox->setSingleStep(0.05);
    dspinBox->setDecimals(2);
    dspinBox->setSuffix(" Hz");
    dspinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, FMFreq);
    dspinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 2);
    dspinBox->setProperty( ArrayDataEditWidget::convertMethodProperty, QStringLiteral("scaleAndAdd(0.05, 0.05)"));
    mainlyt->addWidget(dspinBox, 1, 3);

    mainlyt->addWidget(new QLabel(tr("FM Depth")), 0, 4);
    spinBox = createStandardRawSpinBox( FMDepth, 0, 100);
    spinBox->setSuffix(QStringLiteral(" %"));
    mainlyt->addWidget( spinBox, 1, 4);

    setLayout(mainlyt);
}
