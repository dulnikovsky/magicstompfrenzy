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
#include "dynafilterwidget.h"

#include <QGridLayout>
#include <QLabel>
#include <QSpinBox>
#include <QComboBox>

DynaFilterWidget::DynaFilterWidget( QWidget *parent) :
    EffectEditBaseWidget(parent)
{
    QSpinBox *spinBox;

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

    mainlyt->addWidget(new QLabel(tr("Decay(?)")), 0, 2);
    spinBox = createStandardRawSpinBox( Decay, 0, 0xFF);
    spinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 2);
    mainlyt->addWidget( spinBox, 1, 2);

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

    mainlyt->addWidget(new QLabel(tr("Resonance")), 2, 2);
    spinBox = createStandardRawSpinBox( Resonance, 0, 20);
    mainlyt->addWidget( spinBox, 3, 2);

    mainlyt->addWidget(new QLabel(tr("Level")), 2, 3);
    spinBox = createStandardRawSpinBox( Level, 0, 100);
    mainlyt->addWidget( spinBox, 3, 3);

    setLayout(mainlyt);
}
