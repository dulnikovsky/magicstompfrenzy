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
#include "ampmultiwidget.h"
#include "ampwidget.h"
#include "distortionwidget.h"
#include "noisegatewidget.h"
#include "compressorwidget.h"
#include "ampmultimodulationwidget.h"
#include "ampmultidelaywidget.h"
#include "ampmultireverbwidget.h"

#include <QGridLayout>

AmpMultiWidget::AmpMultiWidget(AmpMultiSubtype subtype, QWidget *parent) :
    EffectEditBaseWidget(parent)
{

    QGridLayout *mainlyt = new QGridLayout();

    if(subtype == AmpSimulatorOnly || subtype==AmpChorus || subtype==AmpFlange || subtype==AmpTremolo || subtype==AmpPhaser)
    {
        mainlyt->addWidget( new AmpWidget(), 0, 0);
        mainlyt->addWidget( new NoiseGateWidget(AmpMultiWidget::NoiseGateThreshold,
                                                AmpMultiWidget::NoiseGateAttack,
                                                AmpMultiWidget::NoiseGateHold,
                                                AmpMultiWidget::NoiseGateDecay),
                                                0, 1);
    }
    else
    {
        mainlyt->addWidget( new DistortionWidget(), 0, 0);
        if(subtype == DistortionOnly)
        {
            mainlyt->addWidget( new NoiseGateWidget(DistortionWidget::NoiseGateThreshold,
                                                DistortionWidget::NoiseGateAttack,
                                                DistortionWidget::NoiseGateHold,
                                                DistortionWidget::NoiseGateDecay),
                                                0, 1);
        }
        else
        {
            mainlyt->addWidget( new NoiseGateWidget(DistortionWidget::NoiseGateThresholdMulti,
                                                DistortionWidget::NoiseGateAttackMulti,
                                                DistortionWidget::NoiseGateHoldMulti,
                                                DistortionWidget::NoiseGateDecayMulti),
                                                0, 1);
        }
    }

    if( subtype != AmpSimulatorOnly && subtype != DistortionOnly)
    {

        mainlyt->addWidget( new CompressorWidget(
                                AmpMultiWidget::CompressorThreshold,
                                AmpMultiWidget::CompressorRatio,
                                AmpMultiWidget::CompressorAttack,
                                AmpMultiWidget::CompressorRelease,
                                AmpMultiWidget::CompressorKnee,
                                AmpMultiWidget::CompressorGain
                                ),
                            1, 0);

        QWidget *modWidget;
        if( subtype==AmpChorus || subtype==DistortionChorus)
            modWidget = new AmpMultiModulationWidget(AmpMultiModulationWidget::Chorus);
        else if(subtype==AmpFlange || subtype==DistortionFlange)
            modWidget = new AmpMultiModulationWidget(AmpMultiModulationWidget::Flange);
        else if(subtype==AmpTremolo || subtype==DistortionTremolo)
            modWidget = new AmpMultiModulationWidget(AmpMultiModulationWidget::Tremolo);
        else if(subtype==AmpPhaser || subtype==DistortionPhaser)
            modWidget = new AmpMultiModulationWidget(AmpMultiModulationWidget::Phaser);
        else
            modWidget = new QWidget(); // should never get here ;-). But avoid crash anyway

        mainlyt->addWidget( modWidget , 1, 1);

        mainlyt->addWidget( new AmpMultiDelayWidget(), 2, 0);

        mainlyt->addWidget( new AmpMultiReverbWidget(), 2, 1);
    }
    setLayout(mainlyt);
}
