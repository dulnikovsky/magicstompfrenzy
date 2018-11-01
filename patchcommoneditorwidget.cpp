#include "patchcommoneditorwidget.h"
#include "arraydataeditwidget.h"

#include "magicstomp.h"

#include <QLineEdit>
#include <QLabel>
#include <QVBoxLayout>
#include <QSpinBox>

PatchCommonEditorWidget::PatchCommonEditorWidget(QWidget *parent)
 : QGroupBox( parent)
{
    setTitle(tr("Patch Common Parameters"));

    QVBoxLayout *mainLayout = new QVBoxLayout();

    mainLayout->addWidget(new QLabel(tr("Type: HEX")));
    QSpinBox *typeSpinBox = new QSpinBox();
    typeSpinBox->setRange(0, EffectTypeNUMBER -1);
    typeSpinBox->setSingleStep(1);
    typeSpinBox->setDisplayIntegerBase(16);
    typeSpinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, PatchType);
    typeSpinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 2);
    mainLayout->addWidget(typeSpinBox);

    mainLayout->addWidget(new QLabel(tr("Name:")));
    QLineEdit *nameLineEdit = new QLineEdit();
    nameLineEdit->setMaxLength(PatchNameLength);
    nameLineEdit->setProperty( ArrayDataEditWidget::dataOffsetProperty, PatchName);
    nameLineEdit->setProperty( ArrayDataEditWidget::dataLenghtProperty, PatchNameLength);
    mainLayout->addWidget(nameLineEdit);

    QSpinBox *constrolSpinBox = new QSpinBox();
    constrolSpinBox->setRange(0, 127);
    constrolSpinBox->setSingleStep(1);
    constrolSpinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, Control1);
    constrolSpinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 2);
    mainLayout->addWidget(constrolSpinBox);

    constrolSpinBox = new QSpinBox();
    constrolSpinBox->setRange(0, 127);
    constrolSpinBox->setSingleStep(1);
    constrolSpinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, Control2);
    constrolSpinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 2);
    mainLayout->addWidget(constrolSpinBox);

    constrolSpinBox = new QSpinBox();
    constrolSpinBox->setRange(0, 127);
    constrolSpinBox->setSingleStep(1);
    constrolSpinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, Control3);
    constrolSpinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 2);
    mainLayout->addWidget(constrolSpinBox);


    mainLayout->addStretch(1);
    setLayout( mainLayout);
}
