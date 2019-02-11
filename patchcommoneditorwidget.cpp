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
#include "patchcommoneditorwidget.h"
#include "arraydataeditwidget.h"

#include "magicstomp.h"
#include "magicstomptext.h"

#include "knobparametermodel.h"
#include "knobparameters.h"

#include <QLineEdit>
#include <QLabel>
#include <QGridLayout>
#include <QSpinBox>
#include <QComboBox>

PatchCommonEditorWidget::PatchCommonEditorWidget(QWidget *parent)
 : QGroupBox( parent), knobparametermodel(nullptr)
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

    //connect(typeComboBox, SIGNAL(onPatchTypeChanged(int)), this, SLOT(typeComboChanged(int)));

    mainLayout->addWidget(new QLabel(tr("Name:")), 0, 1);
    QLineEdit *nameLineEdit = new QLineEdit();
    //nameLineEdit->setValidator(new QRegExpValidator( QRegExp("[a-z-A-Z_]+"), this ));
    nameLineEdit->setMaxLength(PatchNameLength);
    nameLineEdit->setProperty( ArrayDataEditWidget::dataOffsetProperty, PatchName);
    nameLineEdit->setProperty( ArrayDataEditWidget::dataLenghtProperty, PatchNameLength);
    mainLayout->addWidget(nameLineEdit, 1, 1);

    mainLayout->addWidget(new QLabel(tr("Knob 1(?):")), 0, 2);
    knob1ComboBox = new QComboBox();
    knob1ComboBox->setProperty( ArrayDataEditWidget::valuePropertyName, QStringLiteral("currentIndex"));
    knob1ComboBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, Control1);
    knob1ComboBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 2);
    mainLayout->addWidget(knob1ComboBox, 1, 2);

    mainLayout->addWidget(new QLabel(tr("Knob 2(?):")), 0, 3);
    knob2ComboBox = new QComboBox();
    knob2ComboBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, Control2);
    knob2ComboBox->setProperty( ArrayDataEditWidget::valuePropertyName, QStringLiteral("currentIndex"));
    knob2ComboBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 2);
    mainLayout->addWidget(knob2ComboBox, 1, 3);

    mainLayout->addWidget(new QLabel(tr("Knob 3(?):")), 0, 4);
    knob3ComboBox = new QComboBox();
    knob3ComboBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, Control3);
    knob3ComboBox->setProperty( ArrayDataEditWidget::valuePropertyName, QStringLiteral("currentIndex"));
    knob3ComboBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 2);
    mainLayout->addWidget(knob3ComboBox, 1, 4);

    setLayout( mainLayout);
}

void PatchCommonEditorWidget::onPatchTypeChanged(int type)
{
    qDebug("Patch Type Changed");

    knob1ComboBox->blockSignals(true);
    knob2ComboBox->blockSignals(true);
    knob3ComboBox->blockSignals(true);

    knob1ComboBox->clear();
    knob2ComboBox->clear();
    knob3ComboBox->clear();

    if( knobparametermodel )
        knobparametermodel->deleteLater();

    knobparametermodel = nullptr;

    switch (type) {
    case AcousticMulti:
        knobparametermodel = new KnobParameterModel( AcousticMultiKnobParametes, 127, this);
        break;
    default:
        break;
    }

    if( knobparametermodel )
    {
        knob1ComboBox->setModel( knobparametermodel );
        knob2ComboBox->setModel( knobparametermodel );
        knob3ComboBox->setModel( knobparametermodel );
    }

    knob1ComboBox->blockSignals(false);
    knob2ComboBox->blockSignals(false);
    knob3ComboBox->blockSignals(false);
}
