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
#include "ampwidget.h"
#include "magicstomptext.h"
#include "ampmultiwidget.h"
#include <QGridLayout>
#include <QDoubleSpinBox>
#include <QLabel>
#include <QComboBox>

AmpWidget::AmpWidget(QWidget *parent) :
    EffectEditBaseWidget(parent)
{
    setTitle(tr("Amp"));

    QDoubleSpinBox *dspinBox;
    QGridLayout *mainlyt = new QGridLayout();

    mainlyt->addWidget(new QLabel(tr("Amp Type")), 0, 0);
    QComboBox *typeComboBox = new QComboBox();
    typeComboBox->addItems( GuitarAmpTypeNameList);
    typeComboBox->setCurrentIndex(-1);
    typeComboBox->setProperty( ArrayDataEditWidget::valuePropertyName, QStringLiteral("currentIndex"));
    typeComboBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, AmpMultiWidget::AmpType);
    typeComboBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    mainlyt->addWidget( typeComboBox, 1, 0);

    mainlyt->addWidget(new QLabel(tr("Speaker Simulator")), 2, 0);
    QComboBox *speakerComboBox = new QComboBox();
    speakerComboBox->addItems( GuitarCabTypeNameList);
    speakerComboBox->setCurrentIndex(-1);
    speakerComboBox->setProperty( ArrayDataEditWidget::valuePropertyName, QStringLiteral("currentIndex"));
    speakerComboBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, AmpMultiWidget::SpeakerSimulator);
    speakerComboBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    mainlyt->addWidget( speakerComboBox, 3, 0);

    mainlyt->addWidget(new QLabel(tr("Gain")), 0, 1);
    dspinBox = createStandard10DblSpinBox( AmpMultiWidget::Gain);
    dspinBox->setObjectName( QStringLiteral("Gain"));
    mainlyt->addWidget(dspinBox, 1, 1);

    mainlyt->addWidget(new QLabel(tr("Master")), 0, 2);
    dspinBox = createStandard10DblSpinBox( AmpMultiWidget::Master);
    dspinBox->setObjectName( QStringLiteral("Master"));
    mainlyt->addWidget(dspinBox, 1, 2);

    mainlyt->addWidget(new QLabel(tr("Tone")), 0, 3);
    dspinBox = createStandard10DblSpinBox( AmpMultiWidget::Tone);
    mainlyt->addWidget(dspinBox, 1, 3);

    mainlyt->addWidget(new QLabel(tr("Presence")), 0, 4);
    dspinBox = createStandard10DblSpinBox( AmpMultiWidget::Presence);
    mainlyt->addWidget(dspinBox, 1, 4);

    mainlyt->addWidget(new QLabel(tr("Bass")), 2, 1);
    dspinBox = createStandard10DblSpinBox( AmpMultiWidget::Bass);
    mainlyt->addWidget(dspinBox, 3, 1);

    mainlyt->addWidget(new QLabel(tr("Low Middle")), 2, 2);
    dspinBox = createStandard10DblSpinBox( AmpMultiWidget::LowMiddle);
    mainlyt->addWidget(dspinBox, 3, 2);

    mainlyt->addWidget(new QLabel(tr("High Middle")), 2, 3);
    dspinBox = createStandard10DblSpinBox( AmpMultiWidget::HighMiddle);
    mainlyt->addWidget(dspinBox, 3, 3);

    mainlyt->addWidget(new QLabel(tr("Treble")), 2, 4);
    dspinBox = createStandard10DblSpinBox( AmpMultiWidget::Treble);
    mainlyt->addWidget(dspinBox, 3, 4);

    setLayout(mainlyt);
}
