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
#include "rotarywidget.h"

#include <QGridLayout>
#include <QDoubleSpinBox>
#include <QLabel>
#include <QSpinBox>
#include <QComboBox>

RotaryWidget::RotaryWidget( QWidget *parent) :
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

    mainlyt->addWidget(new QLabel(tr("Rotate")), 0, 1);
    QComboBox *rotateComboBox = new QComboBox();
    rotateComboBox->addItem(QStringLiteral("Stop"));
    rotateComboBox->addItem(QStringLiteral("Start"));
    rotateComboBox->setCurrentIndex(-1);
    rotateComboBox->setProperty( ArrayDataEditWidget::valuePropertyName, QStringLiteral("currentIndex"));
    rotateComboBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, Rotate);
    rotateComboBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    mainlyt->addWidget( rotateComboBox, 1, 1);

    mainlyt->addWidget(new QLabel(tr("Slow")), 0, 2);
    dspinBox = new QDoubleSpinBox();
    dspinBox->setMinimum(0.05);
    dspinBox->setMaximum(10.0);
    dspinBox->setSingleStep(0.05);
    dspinBox->setDecimals(2);
    dspinBox->setSuffix(" Hz");
    dspinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, Slow);
    dspinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 2);
    dspinBox->setProperty( ArrayDataEditWidget::convertMethodProperty, QStringLiteral("scaleAndAdd(0.05, 0.05)"));
    mainlyt->addWidget(dspinBox, 1, 2);

    mainlyt->addWidget(new QLabel(tr("Fast")), 0, 3);
    dspinBox = new QDoubleSpinBox();
    dspinBox->setMinimum(0.05);
    dspinBox->setMaximum(10.0);
    dspinBox->setSingleStep(0.05);
    dspinBox->setDecimals(2);
    dspinBox->setSuffix(" Hz");
    dspinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, Fast);
    dspinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 2);
    dspinBox->setProperty( ArrayDataEditWidget::convertMethodProperty, QStringLiteral("scaleAndAdd(0.05, 0.05)"));
    mainlyt->addWidget(dspinBox, 1, 3);

    mainlyt->addWidget(new QLabel(tr("Speed")), 0, 4);
    QComboBox *speedComboBox = new QComboBox();
    speedComboBox->addItem(QStringLiteral("Slow"));
    speedComboBox->addItem(QStringLiteral("Fast"));
    speedComboBox->setCurrentIndex(-1);
    speedComboBox->setProperty( ArrayDataEditWidget::valuePropertyName, QStringLiteral("currentIndex"));
    speedComboBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, Speed);
    speedComboBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    mainlyt->addWidget( speedComboBox, 1, 4);

    mainlyt->addWidget(new QLabel(tr("Drive")), 2, 0);
    spinBox = createStandardRawSpinBox( Drive, 0, 100);
    mainlyt->addWidget( spinBox, 3, 0);

    mainlyt->addWidget(new QLabel(tr("Accel")), 2, 1);
    spinBox = createStandardRawSpinBox( Accel, 0, 10);
    mainlyt->addWidget( spinBox, 3, 1);

    mainlyt->addWidget(new QLabel(tr("Low")), 2, 2);
    spinBox = createStandardRawSpinBox( Low, 0, 100);
    mainlyt->addWidget( spinBox, 3, 2);

    mainlyt->addWidget(new QLabel(tr("High")), 2, 3);
    spinBox = createStandardRawSpinBox( High, 0, 100);
    mainlyt->addWidget( spinBox, 3, 3);

    setLayout(mainlyt);
}
