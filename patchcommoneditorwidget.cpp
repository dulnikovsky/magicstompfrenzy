#include "patchcommoneditorwidget.h"
#include "arraydataeditwidget.h"

#include <QLineEdit>
#include <QLabel>
#include <QVBoxLayout>

PatchCommonEditorWidget::PatchCommonEditorWidget(QWidget *parent)
 : QGroupBox( parent)
{
    setTitle(tr("Patch Common Parameters"));

    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addWidget(new QLabel(tr("Name:")));
    QLineEdit *nameLineEdit = new QLineEdit();
    nameLineEdit->setMaxLength(12);
    nameLineEdit->setProperty( ArrayDataEditWidget::dataOffsetProperty, 16);
    nameLineEdit->setProperty( ArrayDataEditWidget::dataLenghtProperty, 12);

    mainLayout->addWidget(nameLineEdit);
    mainLayout->addStretch(1);
    setLayout( mainLayout);
}
