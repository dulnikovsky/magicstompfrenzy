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
#include "compressorwidget.h"

#include <QGridLayout>
#include <QDoubleSpinBox>
#include <QLabel>
#include <QSpinBox>
#include "compressorreleasecombobox.h"

CompressorWidget::CompressorWidget(
        int thresholdOffset,
        int ratioOffset,
        int attackOffset,
        int releaseOffset,
        int kneeOffset,
        int gainOffset,
        QWidget *parent)
    :EffectEditBaseWidget(parent)
{
    setTitle(tr("Compressor"));

    QDoubleSpinBox *dspinBox;
    QSpinBox *spinBox;
    QGridLayout *mainlyt = new QGridLayout();

    mainlyt->addWidget(new QLabel(tr("Threshold")), 0, 0);
    dspinBox = new QDoubleSpinBox();
    dspinBox->setMinimum(-50.0);
    dspinBox->setMaximum(0.0);
    dspinBox->setSingleStep(0.1);
    dspinBox->setDecimals(1);
    dspinBox->setSuffix(QStringLiteral(" dB"));
    dspinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, thresholdOffset);
    dspinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 2);
    dspinBox->setProperty( ArrayDataEditWidget::convertMethodProperty, QStringLiteral("scaleAndAdd(0.1, -54)"));
    mainlyt->addWidget(dspinBox, 1, 0);

    mainlyt->addWidget(new QLabel(tr("Ratio")), 2, 0);
    QComboBox *ratioComboBox = new QComboBox();
    ratioComboBox->addItem(QStringLiteral("1 : 1"));
    ratioComboBox->addItem(QStringLiteral("1.1 : 1"));
    ratioComboBox->addItem(QStringLiteral("1.3 : 1"));
    ratioComboBox->addItem(QStringLiteral("1.5 : 1"));
    ratioComboBox->addItem(QStringLiteral("1.7 : 1"));
    ratioComboBox->addItem(QStringLiteral("2 : 1"));
    ratioComboBox->addItem(QStringLiteral("2.5 : 1"));
    ratioComboBox->addItem(QStringLiteral("3 : 1"));
    ratioComboBox->addItem(QStringLiteral("3.5 : 1"));
    ratioComboBox->addItem(QStringLiteral("4 : 1"));
    ratioComboBox->addItem(QStringLiteral("5 : 1"));
    ratioComboBox->addItem(QStringLiteral("6 : 1"));
    ratioComboBox->addItem(QStringLiteral("8 : 1"));
    ratioComboBox->addItem(QStringLiteral("10 : 1"));
    ratioComboBox->addItem(QStringLiteral("20 : 1"));
    ratioComboBox->addItem(QString::fromWCharArray(L"\x221e : 1"));
    ratioComboBox->setCurrentIndex(-1);
    ratioComboBox->setProperty( ArrayDataEditWidget::valuePropertyName, QStringLiteral("currentIndex"));
    ratioComboBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, ratioOffset);
    ratioComboBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    mainlyt->addWidget(ratioComboBox, 3, 0);

    mainlyt->addWidget(new QLabel(tr("Attack")), 0, 1);
    spinBox = createStandardRawSpinBox(attackOffset, 0, 120);
    spinBox->setSuffix(QStringLiteral(" ms"));
    mainlyt->addWidget(spinBox, 1, 1);

    mainlyt->addWidget(new QLabel(tr("Release")), 2, 1);
    QComboBox *releaseComboBox = new CompressorReleaseComboBox();
    releaseComboBox->setProperty( ArrayDataEditWidget::valuePropertyName, QStringLiteral("currentIndex"));
    releaseComboBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, releaseOffset);
    releaseComboBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    mainlyt->addWidget(releaseComboBox, 3, 1);

    mainlyt->addWidget(new QLabel(tr("Knee")), 0, 3);
    QComboBox *kneeComboBox = new QComboBox();
    kneeComboBox->addItem(QStringLiteral("Hard"));
    kneeComboBox->addItem(QStringLiteral("1"));
    kneeComboBox->addItem(QStringLiteral("2"));
    kneeComboBox->addItem(QStringLiteral("3"));
    kneeComboBox->addItem(QStringLiteral("4"));
    kneeComboBox->addItem(QStringLiteral("5"));
    kneeComboBox->setCurrentIndex(-1);
    kneeComboBox->setProperty( ArrayDataEditWidget::valuePropertyName, QStringLiteral("currentIndex"));
    kneeComboBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, kneeOffset);
    kneeComboBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    mainlyt->addWidget(kneeComboBox, 1, 3);

    mainlyt->addWidget(new QLabel(tr("Gain")), 2, 3);
    dspinBox = new QDoubleSpinBox();
    dspinBox->setMinimum(0.0);
    dspinBox->setMaximum(18.0);
    dspinBox->setSingleStep(0.5);
    dspinBox->setDecimals(1);
    dspinBox->setSuffix(QStringLiteral(" dB"));
    dspinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, gainOffset);
    dspinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    dspinBox->setProperty( ArrayDataEditWidget::convertMethodProperty, QStringLiteral("scaleAndAdd(0.5, 0)"));
    mainlyt->addWidget(dspinBox, 3, 3);

    setLayout(mainlyt);
}
