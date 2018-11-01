#include "patcheditorwidget.h"
#include "patchcommoneditorwidget.h"

#include "magicstomp.h"

#include <QLabel>
#include <QVBoxLayout>
#include <QVariant>

#include "effecteditwidgets/ampmultiwidget.h"

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

    switch (arr->at(PatchType+1)) {
    case AmpSimulator:
    case AmpMultiChorus:
    case AmpMultiFlange:
    case AmpMultiPhaser:
    case AmpMultiTremolo:
        mainLayout->addWidget( effectEditWidget = new AmpMultiWidget(), 8);
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
