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
#include "modfilterwidget.h"

#include <QGridLayout>
#include <QDoubleSpinBox>
#include <QLabel>
#include <QSpinBox>
#include <QComboBox>

ModFilterWidget::ModFilterWidget( QWidget *parent) :
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

    mainlyt->addWidget(new QLabel(tr("Type")), 0, 1);
    QComboBox *typeComboBox = new QComboBox();
    typeComboBox->addItem(QStringLiteral("Low Pass Filter"));
    typeComboBox->addItem(QStringLiteral("High Pass Filter"));
    typeComboBox->addItem(QStringLiteral("Band Pass Filter"));
    typeComboBox->setCurrentIndex(-1);
    typeComboBox->setProperty( ArrayDataEditWidget::valuePropertyName, QStringLiteral("currentIndex"));
    typeComboBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, Type);
    typeComboBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    mainlyt->addWidget( typeComboBox, 1, 1);

    mainlyt->addWidget(new QLabel(tr("Freq")), 0, 2);
    dspinBox = new QDoubleSpinBox();
    dspinBox->setMinimum(0.05);
    dspinBox->setMaximum(40.0);
    dspinBox->setSingleStep(0.05);
    dspinBox->setDecimals(2);
    dspinBox->setSuffix(" Hz");
    dspinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, Freq);
    dspinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 2);
    dspinBox->setProperty( ArrayDataEditWidget::convertMethodProperty, QStringLiteral("scaleAndAdd(0.05, 0.05)"));
    mainlyt->addWidget(dspinBox, 1, 2);

    mainlyt->addWidget(new QLabel(tr("Depth")), 0, 3);
    spinBox = createStandardRawSpinBox( Depth, 0, 100);
    spinBox->setSuffix(QStringLiteral(" %"));
    mainlyt->addWidget( spinBox, 1, 3);


    mainlyt->addWidget(new QLabel(tr("Phase")), 2, 0);
    dspinBox = new QDoubleSpinBox();
    dspinBox->setMinimum(0.0);
    dspinBox->setMaximum(354.375);
    dspinBox->setSingleStep(5.625);
    dspinBox->setDecimals(2);
    dspinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, Phase);
    dspinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    dspinBox->setProperty( ArrayDataEditWidget::convertMethodProperty, QStringLiteral("scaleAndAdd(5.625, 0)"));
    mainlyt->addWidget(dspinBox, 3, 0);

    mainlyt->addWidget(new QLabel(tr("Offset")), 2, 1);
    spinBox = createStandardRawSpinBox( Offset, 0, 100);
    mainlyt->addWidget( spinBox, 3, 1);

    mainlyt->addWidget(new QLabel(tr("Resonance")), 2, 2);
    spinBox = createStandardRawSpinBox( Resonance, 0, 20);
    mainlyt->addWidget( spinBox, 3, 2);

    mainlyt->addWidget(new QLabel(tr("Level")), 2, 3);
    spinBox = createStandardRawSpinBox( Level, 0, 100);
    mainlyt->addWidget( spinBox, 3, 3);

    setLayout(mainlyt);
}
