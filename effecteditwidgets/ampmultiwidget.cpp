#include "ampmultiwidget.h"
#include "ampwidget.h"
#include "noisegatewidget.h"
#include "compressorwidget.h"
#include "ampmultimodulationwidget.h"

#include <QGridLayout>

AmpMultiWidget::AmpMultiWidget(AmpMultiSubtype subtype, QWidget *parent) :
    EffectEditBaseWidget(parent)
{

    QGridLayout *mainlyt = new QGridLayout();

    mainlyt->addWidget( new AmpWidget(), 0, 0, 1, 2);
    mainlyt->addWidget( new NoiseGateWidget(), 1, 0);

    if( subtype != SimulatorOnly)
    {

        mainlyt->addWidget( new CompressorWidget(
                                AmpMultiWidget::CompressorThreshold,
                                AmpMultiWidget::CompressorRatio,
                                AmpMultiWidget::CompressorAttack,
                                AmpMultiWidget::CompressorRelease,
                                AmpMultiWidget::CompressorKnee,
                                AmpMultiWidget::CompressorGain
                                ),
                            1, 1);

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

        mainlyt->addWidget( modWidget , 2, 0);
    }
    setLayout(mainlyt);
}
