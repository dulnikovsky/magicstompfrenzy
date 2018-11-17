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
#include "delaybandwidget.h"
#include "multibanddelaywidget.h"

#include <QGridLayout>
#include <QDoubleSpinBox>
#include <QLabel>
#include <QComboBox>
#include <QSpinBox>

DelayBandWidget::DelayBandWidget(int offset, double minTime, double maxTime, bool tapOnly, QWidget *parent) :
    EffectEditBaseWidget(parent)
{
    this->setProperty( ArrayDataEditWidget::dataOffsetProperty, offset);

    int col = 0;

    QDoubleSpinBox *dspinBox;
    QLabel *label;
    QGridLayout *mainlyt = new QGridLayout();
    mainlyt->setSpacing(0);
    mainlyt->setContentsMargins(2,2,2,2);

    mainlyt->addWidget( label = new QLabel(tr("Time")), 0, col);
    label->setEnabled( ! tapOnly);
    dspinBox = createTimeSpinBox(((offset - MultibandDelayWidget::LowCutFilter1)/MultibandDelayWidget::BandLenght)*2 - offset, minTime, maxTime);
    mainlyt->addWidget(dspinBox, 1, col++);
    dspinBox->setEnabled( ! tapOnly);

    mainlyt->addWidget( label = new QLabel(tr("Low Cut Filter")), 0, col);
    label->setEnabled( ! tapOnly);
    dspinBox = createStandard10DblSpinBox(0);
    mainlyt->addWidget(dspinBox, 1, col++);
    dspinBox->setEnabled( ! tapOnly);

    mainlyt->addWidget( label = new QLabel(tr("High Cut Filter")), 0, col);
    label->setEnabled( ! tapOnly);
    dspinBox = createStandard10DblSpinBox(1);
    mainlyt->addWidget(dspinBox, 1, col++);
    dspinBox->setEnabled( ! tapOnly);

    mainlyt->addWidget( label = new QLabel(tr("Feedback")), 0, col);
    label->setEnabled( ! tapOnly);
    dspinBox = createStandard10DblSpinBox(2);
    mainlyt->addWidget(dspinBox, 1, col++);
    dspinBox->setEnabled( ! tapOnly);

    mainlyt->addWidget( new QLabel(tr("Wave")), 0, col);
    QComboBox *comboBox = new QComboBox();
    comboBox->setCurrentIndex(-1);
    comboBox->setProperty( ArrayDataEditWidget::valuePropertyName, QStringLiteral("currentIndex"));
    comboBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, 3);
    comboBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    comboBox->addItem(tr("Sine"));
    comboBox->addItem(tr("Other"));
    mainlyt->addWidget(comboBox, 1, col++);

    mainlyt->addWidget(new QLabel(tr("Phase")), 0, col);
    comboBox = new QComboBox();
    comboBox->setCurrentIndex(-1);
    comboBox->setProperty( ArrayDataEditWidget::valuePropertyName, QStringLiteral("currentIndex"));
    comboBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, 4);
    comboBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    comboBox->addItem(tr("Normal"));
    comboBox->addItem(tr("Reverse"));
    mainlyt->addWidget(comboBox, 1, col++);

    mainlyt->addWidget(new QLabel(tr("Tap")), 0, col);
    QSpinBox *spinBox = createStandardRawSpinBox(5, 0, 100);
    spinBox->setSuffix(QStringLiteral(" %"));
    mainlyt->addWidget(spinBox, 1, col++);

    mainlyt->addWidget(new QLabel(tr("Speed")), 0, col);
    dspinBox = createStandard10DblSpinBox(6);
    mainlyt->addWidget(dspinBox, 1, col++);

    mainlyt->addWidget(new QLabel(tr("Depth")), 0, col);
    dspinBox = createStandard10DblSpinBox(7);
    mainlyt->addWidget(dspinBox, 1, col++);

    mainlyt->addWidget(new QLabel(tr("Pan")), 0, col);
    dspinBox = new QDoubleSpinBox();
    dspinBox->setMinimum(-10.0);
    dspinBox->setMaximum(10.0);
    dspinBox->setSingleStep(0.1);
    dspinBox->setDecimals(1);
    dspinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, 8);
    dspinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    dspinBox->setProperty( ArrayDataEditWidget::convertMethodProperty, QStringLiteral("scaleAndAdd(0.2, -10)"));
    mainlyt->addWidget(dspinBox, 1, col++);

    mainlyt->addWidget(new QLabel(tr("Level")), 0, col);
    dspinBox = createStandard10DblSpinBox(9);
    mainlyt->addWidget(dspinBox, 1, col++);

    mainlyt->addWidget(new QLabel(tr("Sync")), 0, col);
    spinBox = createStandardRawSpinBox(10, 0, 100);
    spinBox->setProperty( ArrayDataEditWidget::convertMethodProperty, QStringLiteral("scaleAndAdd(1, 1)"));
    mainlyt->addWidget(spinBox, 1, col++);

    setLayout(mainlyt);
}

QDoubleSpinBox * DelayBandWidget::createTimeSpinBox(int offset, double minTime, double maxTime)
{
    QDoubleSpinBox *dspinBox = new QDoubleSpinBox();
    dspinBox->setSuffix(QStringLiteral(" ms"));
    dspinBox->setMinimum(minTime);
    dspinBox->setMaximum(maxTime);
    dspinBox->setSingleStep(0.1);
    dspinBox->setDecimals(1);
    dspinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, offset);
    dspinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 2);
    if(maxTime > 5000.0)
        dspinBox->setProperty( ArrayDataEditWidget::convertMethodProperty, QStringLiteral("scaleAndAdd(0.5, 0.5)"));
    else if(maxTime > 2000.0)
        dspinBox->setProperty( ArrayDataEditWidget::convertMethodProperty, QStringLiteral("scaleAndAdd(0.2, 0.2)"));
    else
        dspinBox->setProperty( ArrayDataEditWidget::convertMethodProperty, QStringLiteral("scaleAndAdd(0.1, 0.1)"));
    return dspinBox;
}
