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
#include "patcheditorwidget.h"
#include "patchcommoneditorwidget.h"

#include "magicstomp.h"

#include <QLabel>
#include <QVBoxLayout>
#include <QVariant>

#include "effecteditwidgets/ampmultiwidget.h"
#include "effecteditwidgets/multibanddelaywidget.h"
#include "effecteditwidgets/compressorwidget.h"
#include "effecteditwidgets/basspreamp.h"
#include "effecteditwidgets/hqpitchwidget.h"
#include "effecteditwidgets/dualpitchwidget.h"
#include "effecteditwidgets/acousticmultiwidget.h"
#include "effecteditwidgets/reverbwidget.h"
#include "effecteditwidgets/gatereverbwidget.h"
#include "effecteditwidgets/choruswidget.h"
#include "effecteditwidgets/flangewidget.h"
#include "effecteditwidgets/symphonicwidget.h"
#include "effecteditwidgets/vintageflangewidget.h"
#include "effecteditwidgets/phaserwidget.h"
#include "effecteditwidgets/vintagephaserwidget.h"
#include "effecteditwidgets/monodelaywidget.h"
#include "effecteditwidgets/stereodelaywidget.h"
#include "effecteditwidgets/moddelaywidget.h"
#include "effecteditwidgets/delaylcrwidget.h"
#include "effecteditwidgets/echowidget.h"
#include "effecteditwidgets/tapeechowidget.h"
#include "effecteditwidgets/tremolowidget.h"
#include "effecteditwidgets/autopanwidget.h"
#include "effecteditwidgets/reverbchoruswidget.h"
#include "effecteditwidgets/reverbflangewidget.h"
#include "effecteditwidgets/reverbpanwidget.h"
#include "effecteditwidgets/delayearlyrefwidget.h"
#include "effecteditwidgets/delayreverbwidget.h"
#include "effecteditwidgets/distortiondelaywidget.h"
#include "effecteditwidgets/multifilterwidget.h"
#include "effecteditwidgets/threebandeqwidget.h"
#include "effecteditwidgets/rotarywidget.h"
#include "effecteditwidgets/ringmodwidget.h"
#include "effecteditwidgets/modfilterwidget.h"
#include "effecteditwidgets/mbanddynawidget.h"
#include "effecteditwidgets/dynafilterwidget.h"
#include "effecteditwidgets/dynaflangewidget.h"
#include "effecteditwidgets/dynaphaserwidget.h"
#include "effecteditwidgets/springreverbwidget.h"

PatchEditorWidget::PatchEditorWidget( QWidget *parent)
    : ArrayDataEditWidget( parent),effectEditWidget(nullptr)
{
    mainLayout = new QVBoxLayout();
    mainLayout->addWidget( new PatchCommonEditorWidget());
    mainLayout->addWidget( copyrightLabel = new QLabel(copyrightStr), 16);
    setLayout( mainLayout);
}


void PatchEditorWidget::setDataArray(QByteArray *arr)
{
    qDebug("PatchEditorWidget: New data array");
    ArrayDataEditWidget::setDataArray(arr);
    if(arr == nullptr || arr->size() != PatchTotalLength)
        return;

    copyrightLabel->setText(copyrightStr);
    mainLayout->removeWidget( copyrightLabel);
    if(effectEditWidget != nullptr)
    {
        mainLayout->removeWidget( effectEditWidget);
        delete effectEditWidget;
    }

    EffectTypeId patchType = static_cast<EffectTypeId>(arr->at(PatchType+1)); // only last byte is used in PatchType
    switch(patchType)
    {
    case AcousticMulti:
        mainLayout->addWidget( effectEditWidget = new AcousticMultiWidget(), 8);
        break;
    case EightBandParallelDelay:
    case EightBandSeriesDelay:
    case FourBand2TapModDelay:
    case TwoBand4TapModDelay:
    case EightMultiTapModDelay:
    case TwoBandLong4ShortModDelay:
    case ShortMediumLongModDelay:
        mainLayout->addWidget( effectEditWidget = new MultibandDelayWidget(patchType), 8);
        break;
    case Reverb:
        mainLayout->addWidget( effectEditWidget = new ReverbWidget(), 8);
        break;
    case EarlyRef:
        mainLayout->addWidget( effectEditWidget = new GateReverbWidget(true), 8);
        break;
    case GateReverb:
    case ReverseGate:
        mainLayout->addWidget( effectEditWidget = new GateReverbWidget(), 8);
        break;
    case Chorus:
        mainLayout->addWidget( effectEditWidget = new ChorusWidget(), 8);
        break;
    case Flange:
        mainLayout->addWidget( effectEditWidget = new FlangeWidget(), 8);
        break;
    case VintageFlange:
        mainLayout->addWidget( effectEditWidget = new VintageFlangeWidget(), 8);
        break;
    case Symphonic:
        mainLayout->addWidget( effectEditWidget = new SymphonicWidget(), 8);
        break;
    case Phaser:
        mainLayout->addWidget( effectEditWidget = new PhaserWidget(), 8);
        break;
    case MonoVintagePhaser:
        mainLayout->addWidget( effectEditWidget = new VintagePhaserWidget(), 8);
        break;
    case StereoVintagePhaser:
        mainLayout->addWidget( effectEditWidget = new VintagePhaserWidget(false), 8);
        break;
    case Compressor:
        mainLayout->addWidget( effectEditWidget =
                new CompressorWidget(
                        CompressorWidget::Threshold,
                        CompressorWidget::Ratio,
                        CompressorWidget::Attack,
                        CompressorWidget::Release,
                        CompressorWidget::Knee,
                        CompressorWidget::Gain )
                , 8);
        break;
    case AmpSimulator:
        mainLayout->addWidget( effectEditWidget = new AmpMultiWidget(AmpMultiWidget::AmpSimulatorOnly), 8);
        break;
    case Distortion:
        mainLayout->addWidget( effectEditWidget = new AmpMultiWidget(AmpMultiWidget::DistortionOnly), 8);
        break;
    case AmpMultiChorus:
        mainLayout->addWidget( effectEditWidget = new AmpMultiWidget(AmpMultiWidget::AmpChorus), 8);
        break;
    case AmpMultiFlange:
        mainLayout->addWidget( effectEditWidget = new AmpMultiWidget(AmpMultiWidget::AmpFlange), 8);
        break;
    case AmpMultiPhaser:
        mainLayout->addWidget( effectEditWidget = new AmpMultiWidget(AmpMultiWidget::AmpPhaser), 8);
        break;
    case AmpMultiTremolo:
        mainLayout->addWidget( effectEditWidget = new AmpMultiWidget(AmpMultiWidget::AmpTremolo), 8);
        break;
    case DistorionMultiChorus:
        mainLayout->addWidget( effectEditWidget = new AmpMultiWidget(AmpMultiWidget::DistortionChorus), 8);
        break;
    case DistorionMultiFlange:
        mainLayout->addWidget( effectEditWidget = new AmpMultiWidget(AmpMultiWidget::DistortionFlange), 8);
        break;
    case DistorionMultiPhaser:
        mainLayout->addWidget( effectEditWidget = new AmpMultiWidget(AmpMultiWidget::DistortionPhaser), 8);
        break;
    case DistorionMultiTremolo:
        mainLayout->addWidget( effectEditWidget = new AmpMultiWidget(AmpMultiWidget::DistortionTremolo), 8);
        break;
    case HQPitch:
        mainLayout->addWidget( effectEditWidget = new HQPitchWidget(), 8);
        break;
    case DualPitch:
        mainLayout->addWidget( effectEditWidget = new DualPitchWidget(), 8);
        break;
    case BassPreamp:
        mainLayout->addWidget( effectEditWidget = new BassPreampWidget(), 8);
        break;
    case MonoDelay:
        mainLayout->addWidget( effectEditWidget = new MonoDelayWidget(), 8);
        break;
    case StereoDelay:
        mainLayout->addWidget( effectEditWidget = new StereoDelayWidget(), 8);
        break;
    case ModDelay:
        mainLayout->addWidget( effectEditWidget = new ModDelayWidget(), 8);
        break;
    case DelayLCR:
        mainLayout->addWidget( effectEditWidget = new DelayLCRWidget(), 8);
        break;
    case Echo:
        mainLayout->addWidget( effectEditWidget = new EchoWidget(), 8);
        break;
    case TapeEcho:
        mainLayout->addWidget( effectEditWidget = new TapeEchoWidget(), 8);
        break;
    case Tremolo:
        mainLayout->addWidget( effectEditWidget = new TremoloWidget(), 8);
        break;
    case AutoPan:
        mainLayout->addWidget( effectEditWidget = new AutoPanWidget(), 8);
        break;
    case ReverbChorusParallel:
        mainLayout->addWidget( effectEditWidget = new ReverbChorusWidget(), 8);
        break;
    case ReverbChorusSerial:
        mainLayout->addWidget( effectEditWidget = new ReverbChorusWidget(false), 8);
        break;
    case ReverbFlangeParallel:
        mainLayout->addWidget( effectEditWidget = new ReverbFlangeWidget(), 8);
        break;
    case ReverbFlangeSerial:
        mainLayout->addWidget( effectEditWidget = new ReverbFlangeWidget(false), 8);
        break;
    case ReverbSymphonicParallel:
        mainLayout->addWidget( effectEditWidget = new ReverbFlangeWidget(true, true), 8);
        break;
    case ReverbSymphonicSerial:
        mainLayout->addWidget( effectEditWidget = new ReverbFlangeWidget(false, true), 8);
        break;
    case ReverbPan:
        mainLayout->addWidget( effectEditWidget = new ReverbPanWidget(), 8);
        break;
    case DelayEarlyRefParallel:
        mainLayout->addWidget( effectEditWidget = new DelayEarlyRefWidget(), 8);
        break;
    case DelayEarlyRefSerial:
        mainLayout->addWidget( effectEditWidget = new DelayEarlyRefWidget(false), 8);
        break;
    case DelayReverbParallel:
        mainLayout->addWidget( effectEditWidget = new DelayReverbWidget(), 8);
        break;
    case DelayReverbSerial:
        mainLayout->addWidget( effectEditWidget = new DelayReverbWidget(false), 8);
        break;
    case DistortionDelay:
        mainLayout->addWidget( effectEditWidget = new DistortionDelayWidget(), 8);
        break;
    case MultiFilter:
        mainLayout->addWidget( effectEditWidget = new MultiFilterWidget(), 8);
        break;
    case ThreeBandParametricEQ:
        mainLayout->addWidget( effectEditWidget = new ThreeBandEqWidget(), 8);
        break;
    case Rotary:
        mainLayout->addWidget( effectEditWidget = new RotaryWidget(), 8);
        break;
    case RingMod:
        mainLayout->addWidget( effectEditWidget = new RingModWidget(), 8);
        break;
    case ModFilter:
        mainLayout->addWidget( effectEditWidget = new ModFilterWidget(), 8);
        break;
    case DigitalDistortion:
        mainLayout->addWidget( effectEditWidget = new DistortionDelayWidget( true), 8);
        break;
    case MBandDyna:
        mainLayout->addWidget( effectEditWidget = new MBandDynaWidget(), 8);
        break;
    case DynaFilter:
        mainLayout->addWidget( effectEditWidget = new DynaFilterWidget(), 8);
        break;
    case DynaFlange:
        mainLayout->addWidget( effectEditWidget = new DynaFlangeWidget(), 8);
        break;
    case DynaPhaser:
        mainLayout->addWidget( effectEditWidget = new DynaPhaserWidget(), 8);
        break;
    case SpringReverb:
        mainLayout->addWidget( effectEditWidget = new SpringReverbWidget(), 8);
        break;
    default:
        mainLayout->addWidget(effectEditWidget = new QWidget());
        copyrightLabel->setText(QString("No editor created yet!\n")+copyrightStr);
        break;
    }
    effectEditWidget->setProperty( ArrayDataEditWidget::dataOffsetProperty, QVariant(PatchCommonLength));
    mainLayout->addWidget( copyrightLabel, 16);
    refreshData(0, PatchTotalLength);
}
