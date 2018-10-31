#include "patcheditorwidget.h"
#include "patchcommoneditorwidget.h"

#include <QLineEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>

PatchEditorWidget::PatchEditorWidget( QWidget *parent)
    : ArrayDataEditWidget( parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addWidget( new PatchCommonEditorWidget());
    mainLayout->addStretch(2);
    setLayout( mainLayout);
}
