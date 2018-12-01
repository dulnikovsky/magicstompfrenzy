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
#include "mbanddynawidget.h"

#include <QGridLayout>

#include <QLabel>
#include <QSpinBox>
#include <QComboBox>
#include <QDoubleSpinBox>
#include "freqspinbox.h"

MBandDynaWidget::MBandDynaWidget( QWidget *parent) :
    EffectEditBaseWidget(parent)
{
    QSpinBox *spinBox;
    QDoubleSpinBox *dspinBox;

    QGridLayout *mainlyt = new QGridLayout();

    mainlyt->addWidget(new QLabel(tr("Type")), 0, 0);
    QComboBox *slopeComboBox = new QComboBox();
    slopeComboBox->addItem(QStringLiteral("-6 dB"));
    slopeComboBox->addItem(QStringLiteral("-12 dB"));
    slopeComboBox->setCurrentIndex(-1);
    slopeComboBox->setProperty( ArrayDataEditWidget::valuePropertyName, QStringLiteral("currentIndex"));
    slopeComboBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, Slope);
    slopeComboBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    mainlyt->addWidget( slopeComboBox, 1, 0);

    mainlyt->addWidget(new QLabel(tr("Low Gain")), 0, 1);
    dspinBox = new QDoubleSpinBox();
    dspinBox->setMinimum(-96.0);
    dspinBox->setMaximum(12.0);
    dspinBox->setSingleStep(0.1);
    dspinBox->setDecimals(1);
    dspinBox->setSuffix(QStringLiteral(" dB"));
    dspinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, LowGain);
    dspinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 2);
    dspinBox->setProperty( ArrayDataEditWidget::convertMethodProperty, QStringLiteral("scaleAndAdd(0.1, -96)"));
    mainlyt->addWidget(dspinBox, 1, 1);

    mainlyt->addWidget(new QLabel(tr("Middle Gain")), 0, 2);
    dspinBox = new QDoubleSpinBox();
    dspinBox->setMinimum(-96.0);
    dspinBox->setMaximum(12.0);
    dspinBox->setSingleStep(0.1);
    dspinBox->setDecimals(1);
    dspinBox->setSuffix(QStringLiteral(" dB"));
    dspinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, MiddleGain);
    dspinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 2);
    dspinBox->setProperty( ArrayDataEditWidget::convertMethodProperty, QStringLiteral("scaleAndAdd(0.1, -96)"));
    mainlyt->addWidget(dspinBox, 1, 2);

    mainlyt->addWidget(new QLabel(tr("High Gain")), 0, 3);
    dspinBox = new QDoubleSpinBox();
    dspinBox->setMinimum(-96.0);
    dspinBox->setMaximum(12.0);
    dspinBox->setSingleStep(0.1);
    dspinBox->setDecimals(1);
    dspinBox->setSuffix(QStringLiteral(" dB"));
    dspinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, HighGain);
    dspinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 2);
    dspinBox->setProperty( ArrayDataEditWidget::convertMethodProperty, QStringLiteral("scaleAndAdd(0.1, -96)"));
    mainlyt->addWidget(dspinBox, 1, 3);

    mainlyt->addWidget(new QLabel(tr("Lookup")), 0, 4);
    dspinBox = new QDoubleSpinBox();
    dspinBox->setMinimum(0.0);
    dspinBox->setMaximum(100.0);
    dspinBox->setSingleStep(0.1);
    dspinBox->setDecimals(1);
    dspinBox->setSuffix(QStringLiteral(" ms"));
    dspinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, LookUp);
    dspinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 2);
    dspinBox->setProperty( ArrayDataEditWidget::convertMethodProperty, QStringLiteral("scaleAndAdd(0.1, 0)"));
    mainlyt->addWidget(dspinBox, 1, 4);

    mainlyt->addWidget(new QLabel(tr("Ceiling(?)")), 2, 0);
    dspinBox = new QDoubleSpinBox();
    dspinBox->setMinimum(-6.0);
    dspinBox->setMaximum(0.1);
    dspinBox->setSingleStep(0.1);
    dspinBox->setDecimals(1);
    dspinBox->setSuffix(QStringLiteral(" dB"));
    dspinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, Ceiling);
    dspinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    dspinBox->setProperty( ArrayDataEditWidget::convertMethodProperty, QStringLiteral("scaleAndAdd(0.1, -6)"));
    mainlyt->addWidget(dspinBox, 3, 0);

    mainlyt->addWidget(new QLabel(tr("L-M Xover")), 2, 1);
    FreqSpinBox *lmspinBox = new FreqSpinBox();
    lmspinBox->setParameters( 21.2, 8000.0, 0, 0x67);
    lmspinBox->setSuffix(QStringLiteral(" Hz"));
    lmspinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, LMXover);
    lmspinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    mainlyt->addWidget(lmspinBox, 3, 1);

    mainlyt->addWidget(new QLabel(tr("M-H Xover")), 2, 2);
    FreqSpinBox *mhspinBox = new FreqSpinBox();
    mhspinBox->setParameters( 21.2, 8000.0, 0, 0x67);
    mhspinBox->setSuffix(QStringLiteral(" Hz"));
    mhspinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, MHXover);
    mhspinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    mainlyt->addWidget(mhspinBox, 3, 2);

    mainlyt->addWidget(new QLabel(tr("Presence")), 2, 3);
    spinBox = new QSpinBox();
    spinBox->setMinimum(-10);
    spinBox->setMaximum(10);
    spinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, Presence);
    spinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    spinBox->setProperty( ArrayDataEditWidget::convertMethodProperty, QStringLiteral("scaleAndAdd( 1, -10)"));
    mainlyt->addWidget(spinBox, 3, 3);

    QGroupBox *filter1GroupBox = new QGroupBox(QStringLiteral("Compressor"));
    QGridLayout *filter1Layout = new QGridLayout();





    filter1GroupBox->setLayout( filter1Layout);


    QGroupBox *filter2GroupBox = new QGroupBox(QStringLiteral("Expander"));
    QGridLayout *filter2Layout = new QGridLayout();


    filter2GroupBox->setLayout(filter2Layout);

    QGroupBox *filter3GroupBox = new QGroupBox(QStringLiteral("Limiter"));
    QGridLayout *filter3Layout = new QGridLayout();





    filter3GroupBox->setLayout(filter3Layout);


    mainlyt->addWidget(filter1GroupBox, 4, 0);
    mainlyt->addWidget(filter2GroupBox, 5, 0);
    mainlyt->addWidget(filter3GroupBox, 6, 0);
    setLayout(mainlyt);
}
