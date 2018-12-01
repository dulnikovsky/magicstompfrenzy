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
#include "threebandeqwidget.h"

#include <QGridLayout>

#include <QLabel>
#include <QDoubleSpinBox>
#include "freqspinbox.h"

ThreeBandEqWidget::ThreeBandEqWidget( QWidget *parent) :
    EffectEditBaseWidget(parent)
{
    QDoubleSpinBox *dspinBox;
    FreqSpinBox *freqSpinBox;

    QGridLayout *mainlyt = new QGridLayout();

    mainlyt->addWidget(new QLabel(tr("Level")), 0, 0);
    dspinBox = createStandard10DblSpinBox(Level);
    dspinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 2);
    mainlyt->addWidget(dspinBox, 1, 0);

    QGroupBox *filter1GroupBox = new QGroupBox(QStringLiteral("Band 1"));
    QGridLayout *filter1Layout = new QGridLayout();

    filter1Layout->addWidget(new QLabel(tr("Freq")), 0, 0);
    freqSpinBox = new FreqSpinBox();
    freqSpinBox->setParameters(20.0, 20000.0, 0, 0xFF);
    freqSpinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, EQ1Freq);
    freqSpinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 2);
    filter1Layout->addWidget( freqSpinBox, 1, 0);

    filter1Layout->addWidget(new QLabel(tr("Q")), 0, 1);
    ExpSpinBox *extSpinBox = new ExpSpinBox();
    extSpinBox->setParameters(0.1, 20.0);
    extSpinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, EQ1Q);
    extSpinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    filter1Layout->addWidget(extSpinBox, 1, 1);

    filter1Layout->addWidget(new QLabel(tr("Gain")), 0, 2);
    dspinBox = createStd12GainSpinBox(EQ1Gain);
    filter1Layout->addWidget(dspinBox, 1, 2);

    filter1GroupBox->setLayout( filter1Layout);


    QGroupBox *filter2GroupBox = new QGroupBox(QStringLiteral("Band 2"));
    QGridLayout *filter2Layout = new QGridLayout();

    filter2Layout->addWidget(new QLabel(tr("Freq")), 0, 0);
    freqSpinBox = new FreqSpinBox();
    freqSpinBox->setParameters(20.0, 20000.0, 0, 0xFF);
    freqSpinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, EQ2Freq);
    freqSpinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 2);
    filter2Layout->addWidget( freqSpinBox, 1, 0);

    filter2Layout->addWidget(new QLabel(tr("Q")), 0, 1);
    extSpinBox = new ExpSpinBox();
    extSpinBox->setParameters(0.1, 20.0);
    extSpinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, EQ2Q);
    extSpinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    filter2Layout->addWidget(extSpinBox, 1, 1);

    filter2Layout->addWidget(new QLabel(tr("Gain")), 0, 2);
    dspinBox = createStd12GainSpinBox(EQ2Gain);
    filter2Layout->addWidget(dspinBox, 1, 2);

    filter2GroupBox->setLayout(filter2Layout);

    QGroupBox *filter3GroupBox = new QGroupBox(QStringLiteral("Band 3"));
    QGridLayout *filter3Layout = new QGridLayout();

    filter3Layout->addWidget(new QLabel(tr("Freq")), 0, 0);
    freqSpinBox = new FreqSpinBox();
    freqSpinBox->setParameters(20.0, 20000.0, 0, 0xFF);
    freqSpinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, EQ3Freq);
    freqSpinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 2);
    filter3Layout->addWidget( freqSpinBox, 1, 0);

    filter3Layout->addWidget(new QLabel(tr("Q")), 0, 1);
    extSpinBox = new ExpSpinBox();
    extSpinBox->setParameters(0.1, 20.0);
    extSpinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, EQ3Q);
    extSpinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    filter3Layout->addWidget(extSpinBox, 1, 1);

    filter3Layout->addWidget(new QLabel(tr("Gain")), 0, 2);
    dspinBox = createStd12GainSpinBox(EQ3Gain);
    filter3Layout->addWidget(dspinBox, 1, 2);


    filter3GroupBox->setLayout(filter3Layout);


    mainlyt->addWidget(filter1GroupBox, 2, 0);
    mainlyt->addWidget(filter2GroupBox, 3, 0);
    mainlyt->addWidget(filter3GroupBox, 4, 0);
    setLayout(mainlyt);
}
