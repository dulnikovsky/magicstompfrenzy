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
#include "acousticmultiwidget.h"
#include <QGridLayout>
#include <QDoubleSpinBox>
#include <QLabel>
#include <QSpinBox>
#include <QComboBox>

#include "magicstomptext.h"
#include "freqspinbox.h"

AcousticMultiWidget::AcousticMultiWidget(QWidget *parent) :
    EffectEditBaseWidget(parent)
{
    FreqSpinBox *fspinBox;
    QDoubleSpinBox *dspinBox;
    QGridLayout *mainlyt = new QGridLayout();

    mainlyt->addWidget(new QLabel(tr("Mic Type")), 0, 0);
    QComboBox *micTypeComboBox = new QComboBox();
    micTypeComboBox->addItems( MicTypeNameList);
    micTypeComboBox->setCurrentIndex(-1);
    micTypeComboBox->setProperty( ArrayDataEditWidget::valuePropertyName, QStringLiteral("currentIndex"));
    micTypeComboBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, MicType);
    micTypeComboBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    mainlyt->addWidget( micTypeComboBox, 1, 0);

    mainlyt->addWidget(new QLabel(tr("Blend")), 0, 1);
    dspinBox = createStandard10DblSpinBox( Blend);
    mainlyt->addWidget(dspinBox, 1, 1);

    mainlyt->addWidget(new QLabel(tr("Volume")), 0, 2);
    dspinBox = createStandard10DblSpinBox( Volume);
    mainlyt->addWidget(dspinBox, 1, 2);

    mainlyt->addWidget(new QLabel(tr("Stereo")), 0, 3);
    dspinBox = createStandard10DblSpinBox( Stereo);
    mainlyt->addWidget(dspinBox, 1, 3);

    QGroupBox *eqGroupBox = new QGroupBox(tr("EQ"));
    QGridLayout *eqlyt = new QGridLayout();

    eqlyt->addWidget(new QLabel(tr("Bass")), 0, 0);
    dspinBox = createStd12GainSpinBox( Bass);
    eqlyt->addWidget(dspinBox, 1, 0);

    eqlyt->addWidget(new QLabel(tr("Middle")), 0, 1);
    dspinBox = createStd12GainSpinBox( Middle);
    eqlyt->addWidget(dspinBox, 1, 1);

    eqlyt->addWidget(new QLabel(tr("Treble")), 0, 2);
    dspinBox = createStd12GainSpinBox( Treble);
    eqlyt->addWidget(dspinBox, 1, 2);

    eqlyt->addWidget(new QLabel(tr("Presence")), 0, 3);
    dspinBox = createStd12GainSpinBox( Presence);
    eqlyt->addWidget(dspinBox, 1, 3);

    eqlyt->addWidget(new QLabel(tr("Bass Freq")), 2, 0);
    fspinBox = new FreqSpinBox();
    fspinBox->setParameters(50.0, 400.0);
    fspinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, BassFreq);
    fspinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    eqlyt->addWidget(fspinBox, 3, 0);

    eqlyt->addWidget(new QLabel(tr("Middle Freq")), 2, 1);
    fspinBox = new FreqSpinBox();
    fspinBox->setParameters(200.0, 1600.0);
    fspinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, MiddleFreq);
    fspinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    eqlyt->addWidget(fspinBox, 3, 1);

    eqlyt->addWidget(new QLabel(tr("Treble Freq")), 2, 2);
    fspinBox = new FreqSpinBox();
    fspinBox->setParameters(600.0, 4800.0);
    fspinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, TrebleFreq);
    fspinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    eqlyt->addWidget(fspinBox, 3, 2);

    eqlyt->addWidget(new QLabel(tr("Presence Freq")), 2, 3);
    fspinBox = new FreqSpinBox();
    fspinBox->setParameters(2000.0, 16000.0);
    fspinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, PresenceFreq);
    fspinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    eqlyt->addWidget(fspinBox, 3, 3);

    eqGroupBox->setLayout( eqlyt);
    mainlyt->addWidget(eqGroupBox, 2, 0, 1, 4);

    QGroupBox *limiterGroupBox = new QGroupBox(tr("Limiter"));
    QGridLayout *limiterlyt = new QGridLayout();

    QComboBox *limiterComboBox = new QComboBox();
    limiterComboBox->addItems( OffOnStringList);
    limiterComboBox->setCurrentIndex(-1);
    limiterComboBox->setProperty( ArrayDataEditWidget::valuePropertyName, QStringLiteral("currentIndex"));
    limiterComboBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, Limiter);
    limiterComboBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    limiterlyt->addWidget( limiterComboBox, 0, 0);

    //limiterlyt->addWidget(new QLabel(tr("Level")), 0, 1);
    dspinBox = createStandard10DblSpinBox( LimiterLevel);
    limiterlyt->addWidget(dspinBox, 0, 1);

    limiterGroupBox->setLayout(limiterlyt);
    mainlyt->addWidget(limiterGroupBox, 0, 4, 2, 1);

    QGroupBox *reverbGroupBox = new QGroupBox(tr("Reverb"));
    QGridLayout *reverblyt = new QGridLayout();

    reverblyt->addWidget(new QLabel(tr("Type")), 0, 0);
    QComboBox *reverbComboBox = new QComboBox();
    reverbComboBox->addItems( AcousticReverbTypeNameList);
    reverbComboBox->setCurrentIndex(-1);
    reverbComboBox->setProperty( ArrayDataEditWidget::valuePropertyName, QStringLiteral("currentIndex"));
    reverbComboBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, ReverbType);
    reverbComboBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    reverblyt->addWidget( reverbComboBox, 1, 0);

    reverblyt->addWidget(new QLabel(tr("Level")), 0, 1);
    dspinBox = createStandard10DblSpinBox( ReverbLevel);
    reverblyt->addWidget(dspinBox, 1, 1);
    reverblyt->setRowStretch( 2, 16);

    reverbGroupBox->setLayout(reverblyt);
    mainlyt->addWidget(reverbGroupBox, 2, 4);

    QGroupBox *chorusDelayGroupBox = new QGroupBox(tr("Chorus/Delay"));
    QGridLayout *chdlyt = new QGridLayout();

    chdlyt->addWidget(new QLabel(tr("Type")), 0, 0);
    QComboBox *chdlyComboBox = new QComboBox();
    chdlyComboBox->addItems( AcousticChorusDelayTypeNameList);
    chdlyComboBox->setCurrentIndex(-1);
    chdlyComboBox->setProperty( ArrayDataEditWidget::valuePropertyName, QStringLiteral("currentIndex"));
    chdlyComboBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, ChorusDelayType);
    chdlyComboBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    chdlyt->addWidget( chdlyComboBox, 1, 0);

    chdlyt->addWidget(new QLabel(tr("Speed/Time")), 0, 1);
    dspinBox = createStandard10DblSpinBox( SpeedTime);
    chdlyt->addWidget(dspinBox, 1, 1);

    chdlyt->addWidget(new QLabel(tr("Depth/Feedback")), 0, 2);
    dspinBox = createStandard10DblSpinBox( DepthFeedback);
    chdlyt->addWidget(dspinBox, 1, 2);

    chdlyt->addWidget(new QLabel(tr("Level")), 0, 3);
    dspinBox = createStandard10DblSpinBox( EffectLevel);
    chdlyt->addWidget(dspinBox, 1, 3);

    chorusDelayGroupBox->setLayout(chdlyt);
    mainlyt->addWidget(chorusDelayGroupBox, 3, 0, 1, 4);

    mainlyt->setRowStretch(4,8);
    mainlyt->setColumnStretch(4,8);
    setLayout(mainlyt);
}


