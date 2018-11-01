#include "patchcommoneditorwidget.h"
#include "arraydataeditwidget.h"

#include "magicstomp.h"
#include "magicstomptext.h"

#include <QLineEdit>
#include <QLabel>
#include <QGridLayout>
#include <QSpinBox>
#include <QComboBox>

PatchCommonEditorWidget::PatchCommonEditorWidget(QWidget *parent)
 : QGroupBox( parent)
{
    setTitle(tr("Patch Common Parameters"));

    QGridLayout *mainLayout = new QGridLayout();

    mainLayout->addWidget(new QLabel(tr("Type:")), 0, 0);
    QComboBox *typeComboBox = new QComboBox();
    typeComboBox->addItems( EffectTypeNameList);
    typeComboBox->setCurrentIndex(-1);
    typeComboBox->setProperty( ArrayDataEditWidget::valuePropertyName, QStringLiteral("currentIndex"));
    typeComboBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, PatchType);
    typeComboBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 2);
    mainLayout->addWidget(typeComboBox, 1, 0);

    mainLayout->addWidget(new QLabel(tr("Name:")), 0, 1);
    QLineEdit *nameLineEdit = new QLineEdit();
    nameLineEdit->setMaxLength(PatchNameLength);
    nameLineEdit->setProperty( ArrayDataEditWidget::dataOffsetProperty, PatchName);
    nameLineEdit->setProperty( ArrayDataEditWidget::dataLenghtProperty, PatchNameLength);
    mainLayout->addWidget(nameLineEdit, 1, 1);

    mainLayout->addWidget(new QLabel(tr("Knob 1:")), 0, 2);
    QSpinBox *constrolSpinBox = new QSpinBox();
    constrolSpinBox->setRange(0, 127);
    constrolSpinBox->setSingleStep(1);
    constrolSpinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, Control1);
    constrolSpinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 2);
    mainLayout->addWidget(constrolSpinBox, 1, 2);

    mainLayout->addWidget(new QLabel(tr("Knob 2:")), 0, 3);
    constrolSpinBox = new QSpinBox();
    constrolSpinBox->setRange(0, 127);
    constrolSpinBox->setSingleStep(1);
    constrolSpinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, Control2);
    constrolSpinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 2);
    mainLayout->addWidget(constrolSpinBox, 1, 3);

    mainLayout->addWidget(new QLabel(tr("Knob 3:")), 0, 4);
    constrolSpinBox = new QSpinBox();
    constrolSpinBox->setRange(0, 127);
    constrolSpinBox->setSingleStep(1);
    constrolSpinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, Control3);
    constrolSpinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 2);
    mainLayout->addWidget(constrolSpinBox, 1, 4);

    setLayout( mainLayout);
}
