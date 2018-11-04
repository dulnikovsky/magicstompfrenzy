#include "patcheditorwidget.h"
#include "patchcommoneditorwidget.h"
#include "effecteditwidgets/compressorwidget.h"

#include "magicstomp.h"

#include <QLabel>
#include <QVBoxLayout>
#include <QVariant>

#include "effecteditwidgets/ampmultiwidget.h"
#include "effecteditwidgets/multibanddelaywidget.h"

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

    EffectTypeId patchType = (EffectTypeId)arr->at(PatchType+1);
    switch(patchType)
    {

    case EightBandParallelDelay:
    case EightBandSeriesDelay:
    case FourBand2TapModDelay:
    case TwoBand4TapModDelay:
    case EightMultiTapModDelay:
    case TwoBandLong4ShortModDelay:
    case ShortMediumLongModDelay:
        mainLayout->addWidget( effectEditWidget = new MultibandDelayWidget(patchType), 8);
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
        mainLayout->addWidget( effectEditWidget = new AmpMultiWidget(AmpMultiWidget::SimulatorOnly), 8);
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
    default:
        mainLayout->addWidget(effectEditWidget = new QWidget());
        copyrightLabel->setText(QString("No editor created yet!\n")+copyrightStr);
        break;
    }
    effectEditWidget->setProperty( ArrayDataEditWidget::dataOffsetProperty, QVariant(PatchCommonLength));
    mainLayout->addWidget( copyrightLabel, 16);
    refreshData(0, PatchTotalLength);
}
