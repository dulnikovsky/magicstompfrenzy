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
#include "delayearlyrefwidget.h"
#include "delaymultiwidget.h"
#include "magicstomptext.h"
#include <QGridLayout>
#include <QDoubleSpinBox>
#include <QLabel>
#include <QSpinBox>
#include <QComboBox>

DelayEarlyRefWidget::DelayEarlyRefWidget(bool isParallel, QWidget *parent) :
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
        mainlyt->addWidget(new QLabel(tr("Delay/ER")), 0, 1);
    else
        mainlyt->addWidget(new QLabel(tr("Delay Balance")), 0, 1);
    spinBox = new QSpinBox();
    spinBox->setMinimum(0);
    spinBox->setMaximum(100);
    spinBox->setSuffix(" %");
    spinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, Balance);
    spinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    mainlyt->addWidget(spinBox, 1, 1);

    QGroupBox *erGroupBox = new QGroupBox("Early Reflections");
    QGridLayout *erLayout = new QGridLayout();

    erLayout->addWidget(new QLabel(tr("Type")), 0, 0);
    QComboBox *typeComboBox = new QComboBox();
    typeComboBox->addItems( EarlyRefTypeNameList);
    typeComboBox->setCurrentIndex(-1);
    typeComboBox->setProperty( ArrayDataEditWidget::valuePropertyName, QStringLiteral("currentIndex"));
    typeComboBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, Type);
    typeComboBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    erLayout->addWidget( typeComboBox, 1, 0);

    erLayout->addWidget(new QLabel(tr("Init Delay")), 0, 1);
    dspinBox = new QDoubleSpinBox();
    dspinBox->setMinimum(0.0);
    dspinBox->setMaximum(500.0);
    dspinBox->setSingleStep(0.1);
    dspinBox->setDecimals(1);
    dspinBox->setSuffix(" ms");
    dspinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, InitDelay);
    dspinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 2);
    dspinBox->setProperty( ArrayDataEditWidget::convertMethodProperty, QStringLiteral("scaleAndAdd(0.1, 0)"));
    erLayout->addWidget(dspinBox, 1, 1);

    erLayout->addWidget(new QLabel(tr("Room Size")), 0, 2);
    dspinBox = new QDoubleSpinBox();
    dspinBox->setMinimum(0.2);
    dspinBox->setMaximum(20.0);
    dspinBox->setSingleStep(0.2);
    dspinBox->setDecimals(1);
    dspinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, RoomSize);
    dspinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    dspinBox->setProperty( ArrayDataEditWidget::convertMethodProperty, QStringLiteral("scaleAndAdd(0.2, 0.2)"));
    erLayout->addWidget(dspinBox, 1, 2);

    erLayout->addWidget(new QLabel(tr("Liveness")), 0, 3);
    spinBox = new QSpinBox();
    spinBox->setMinimum(0);
    spinBox->setMaximum(10);
    spinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, Liveness);
    spinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    erLayout->addWidget(spinBox, 1, 3);

    erLayout->addWidget(new QLabel(tr("Diffusion")), 2, 0);
    spinBox = new QSpinBox();
    spinBox->setMinimum(0);
    spinBox->setMaximum(10);
    spinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, Diffusion);
    spinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    erLayout->addWidget(spinBox, 3, 0);

    erLayout->addWidget(new QLabel(tr("Density")), 2, 1);
    spinBox = new QSpinBox();
    spinBox->setMinimum(0);
    spinBox->setMaximum(100);
    spinBox->setSuffix(" %");
    spinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, Density);
    spinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    erLayout->addWidget(spinBox, 3, 1);

    erLayout->addWidget(new QLabel(tr("ER Number")), 2, 2);
    spinBox = new QSpinBox();
    spinBox->setMinimum(1);
    spinBox->setMaximum(19);
    spinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, ERNumber);
    spinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    spinBox->setProperty( ArrayDataEditWidget::convertMethodProperty, QStringLiteral("scaleAndAdd(1, 1)"));
    erLayout->addWidget(spinBox, 3, 2);

    erGroupBox->setLayout(erLayout);

    mainlyt->addWidget(new DelayMultiWidget, 2, 0, 1, 2);
    mainlyt->addWidget(erGroupBox, 3, 0, 1, 2);

    setLayout(mainlyt);
}
