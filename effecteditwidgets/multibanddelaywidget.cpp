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
#include "multibanddelaywidget.h"
#include "delaybandwidget.h"
#include <QGridLayout>
#include <QDoubleSpinBox>
#include <QComboBox>
#include <QLabel>
#include <QSpinBox>

MultibandDelayWidget::MultibandDelayWidget(EffectTypeId effectid, QWidget *parent) :
    EffectEditBaseWidget(parent)
{
    QDoubleSpinBox *dspinBox;

    QGridLayout *headerRowLayout = new QGridLayout();

    headerRowLayout->addWidget(new QLabel(tr("Effect Level")), 0, 0);
    dspinBox = createStandard10DblSpinBox( EffectLevel);
    dspinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 2);
    headerRowLayout->addWidget(dspinBox, 1, 0);

    headerRowLayout->addWidget(new QLabel(tr("Direct Level")), 0, 1);
    dspinBox = createStandard10DblSpinBox( DirectLevel);
    dspinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 2);
    headerRowLayout->addWidget(dspinBox, 1, 1);

    headerRowLayout->addWidget(new QLabel(tr("Direct Pan")), 0, 2);
    dspinBox = new QDoubleSpinBox();
    dspinBox->setMinimum(-10.0);
    dspinBox->setMaximum(10.0);
    dspinBox->setSingleStep(0.1);
    dspinBox->setDecimals(1);
    dspinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, DirectPan);
    dspinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 2);
    dspinBox->setProperty( ArrayDataEditWidget::convertMethodProperty, QStringLiteral("scaleAndAdd(0.2, -10)"));
    headerRowLayout->addWidget(dspinBox, 1, 2);

    headerRowLayout->addWidget(new QLabel(tr("Waveform")), 0, 3);
    QComboBox *waveComboBox = new QComboBox();
    waveComboBox->setCurrentIndex(-1);
    waveComboBox->setProperty( ArrayDataEditWidget::valuePropertyName, QStringLiteral("currentIndex"));
    waveComboBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, WaveForm);
    waveComboBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    waveComboBox->addItem(tr("Triangle"));
    waveComboBox->addItem(tr("Saw Up"));
    waveComboBox->addItem(tr("Saw Down"));

    headerRowLayout->addWidget(waveComboBox, 1, 3);

    headerRowLayout->setColumnStretch(4,8);

    QGridLayout *gridlyt = new QGridLayout();
    gridlyt->setSpacing(0);
    gridlyt->setContentsMargins(4,4,4,4);
    gridlyt->addLayout(headerRowLayout, 0, 1, 1, 6);

    if(effectid == EightBandParallelDelay || effectid == EightBandSeriesDelay)
    {
        for(int i=0; i<8; i++)
        {
            gridlyt->addWidget( new QLabel(tr("Band ")+ QString::number(i+1)), i+1, 0);
            gridlyt->addWidget( new DelayBandWidget( LowCutFilter1 + BandLenght*i, 0.1, 696.0, false), i+1, 1);
        }
    }
    else if(effectid == FourBand2TapModDelay )
    {
        for(int i=0; i<8; i++)
        {
            gridlyt->addWidget( new QLabel(tr("Band ")+ QString::number(i/2+1) + tr(":Tap ")+ QString::number(i%2+1)), i+1, 0);
            gridlyt->addWidget( new DelayBandWidget( LowCutFilter1 + BandLenght*i, 0.1, 1430.0, i%2), i+1, 1);
        }
    }
    else if(effectid == TwoBand4TapModDelay )
    {
        for(int i=0; i<8; i++)
        {
            gridlyt->addWidget( new QLabel(tr("Band ")+ QString::number(i/4+1) + tr(":Tap ")+ QString::number(i%4+1)), i+1, 0);
            gridlyt->addWidget( new DelayBandWidget( LowCutFilter1 + BandLenght*i, 0.2, 2920.0, i%4), i+1, 1);
        }
    }
    else if(effectid == EightMultiTapModDelay )
    {
        for(int i=0; i<8; i++)
        {
            gridlyt->addWidget( new QLabel(tr("Tap ")+ QString::number(i%8+1)), i+1, 0);
            gridlyt->addWidget( new DelayBandWidget( LowCutFilter1 + BandLenght*i, 0.2, 5890.0, i%8), i+1, 1);
        }
    }
    else if(effectid == TwoBandLong4ShortModDelay )
    {
        gridlyt->addWidget( new QLabel( tr("Long Band 1:Tap 1")), 1, 0);
        gridlyt->addWidget( new DelayBandWidget( LowCutFilter1 + BandLenght*0, 0.1, 1430.0, false), 1, 1);

        gridlyt->addWidget( new QLabel( tr("Long Band 1:Tap 2")), 2, 0);
        gridlyt->addWidget( new DelayBandWidget( LowCutFilter1 + BandLenght*1, 0.1, 1430.0, true), 2, 1);

        gridlyt->addWidget( new QLabel( tr("Long Band 2:Tap 1")), 3, 0);
        gridlyt->addWidget( new DelayBandWidget( LowCutFilter1 + BandLenght*2, 0.1, 1430.0, false), 3, 1);

        gridlyt->addWidget( new QLabel( tr("Long Band 2:Tap 2")), 4, 0);
        gridlyt->addWidget( new DelayBandWidget( LowCutFilter1 + BandLenght*3, 0.1, 1430.0, true), 4, 1);
        for(int i=4; i<8; i++)
        {
            gridlyt->addWidget( new QLabel( tr("Short Band ")+ QString::number(i-3)), i+1, 0);
            gridlyt->addWidget( new DelayBandWidget( LowCutFilter1 + BandLenght*i, 0.1, 696.0, false), i+1, 1);
        }
    }
    else if(effectid == ShortMediumLongModDelay )
    {
        gridlyt->addWidget( new QLabel( tr("Short Band")), 1, 0);
        gridlyt->addWidget( new DelayBandWidget( LowCutFilter1 + BandLenght*0, 0.1, 696.0, false), 1, 1);

        gridlyt->addWidget( new QLabel( tr("Medium Band Tap 1")), 2, 0);
        gridlyt->addWidget( new DelayBandWidget( LowCutFilter1 + BandLenght*1, 0.2, 2180.0, false), 2, 1);

        gridlyt->addWidget( new QLabel( tr("Medium Band Tap 2")), 3, 0);
        gridlyt->addWidget( new DelayBandWidget( LowCutFilter1 + BandLenght*2, 0.2, 2180.0, true), 3, 1);

        gridlyt->addWidget( new QLabel( tr("Medium Band Tap 3")), 4, 0);
        gridlyt->addWidget( new DelayBandWidget( LowCutFilter1 + BandLenght*3, 0.2, 2180.0, true), 4, 1);

        gridlyt->addWidget( new QLabel(tr("Long Band Tap 1")), 5, 0);
        gridlyt->addWidget( new DelayBandWidget( LowCutFilter1 + BandLenght*4, 0.1, 2920.0, false), 5, 1);
        for(int i=5; i<8; i++)
        {
            gridlyt->addWidget( new QLabel(tr("Long Band ")+tr("Tap ")+ QString::number(i%4+1)), i+1, 0);
            gridlyt->addWidget( new DelayBandWidget( LowCutFilter1 + BandLenght*i, 0.1, 2920.0, true), i+1, 1);
        }
    }

    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addLayout( headerRowLayout);
    mainLayout->addLayout( gridlyt);
    setLayout(mainLayout);
}


