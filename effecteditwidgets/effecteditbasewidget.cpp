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
#include "effecteditbasewidget.h"

#include <QDoubleSpinBox>
#include <QSpinBox>

EffectEditBaseWidget::EffectEditBaseWidget(QWidget *parent)
    : QGroupBox(parent)
{

}


QDoubleSpinBox * EffectEditBaseWidget::createStandard10DblSpinBox(int offset)
{
    QDoubleSpinBox *dspinBox = new QDoubleSpinBox();
    dspinBox->setMinimum(0.0);
    dspinBox->setMaximum(10.0);
    dspinBox->setSingleStep(0.1);
    dspinBox->setDecimals(1);
    dspinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, offset);
    dspinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    dspinBox->setProperty( ArrayDataEditWidget::convertMethodProperty, QStringLiteral("scaleAndAdd(0.1, 0)"));
    return dspinBox;
}

QSpinBox * EffectEditBaseWidget::createStandardRawSpinBox(int offset, int minimum, int maximum, int length)
{
    QSpinBox *spinBox = new QSpinBox();
    spinBox->setMinimum(minimum);
    spinBox->setMaximum(maximum);
    spinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, offset);
    spinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, length);
    return spinBox;
}

QDoubleSpinBox* EffectEditBaseWidget::createStd12GainSpinBox(int offset)
{
    QDoubleSpinBox *dspinBox = new QDoubleSpinBox();
    dspinBox->setMinimum(-12.0);
    dspinBox->setMaximum(12.0);
    dspinBox->setSingleStep(0.2);
    dspinBox->setDecimals(1);
    dspinBox->setSuffix(QStringLiteral(" dB"));
    dspinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, offset);
    dspinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    dspinBox->setProperty( ArrayDataEditWidget::convertMethodProperty, QStringLiteral("scaleAndAdd(0.2, -12.0)"));
    return dspinBox;
}
