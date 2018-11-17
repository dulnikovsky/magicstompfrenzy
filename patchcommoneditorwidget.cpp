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

    mainLayout->addWidget(new QLabel(tr("Knob 1(?):")), 0, 2);
    QSpinBox *constrolSpinBox = new QSpinBox();
    constrolSpinBox->setRange(0, 127);
    constrolSpinBox->setSingleStep(1);
    constrolSpinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, Control1);
    constrolSpinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 2);
    mainLayout->addWidget(constrolSpinBox, 1, 2);

    mainLayout->addWidget(new QLabel(tr("Knob 2(?):")), 0, 3);
    constrolSpinBox = new QSpinBox();
    constrolSpinBox->setRange(0, 127);
    constrolSpinBox->setSingleStep(1);
    constrolSpinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, Control2);
    constrolSpinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 2);
    mainLayout->addWidget(constrolSpinBox, 1, 3);

    mainLayout->addWidget(new QLabel(tr("Knob 3(?):")), 0, 4);
    constrolSpinBox = new QSpinBox();
    constrolSpinBox->setRange(0, 127);
    constrolSpinBox->setSingleStep(1);
    constrolSpinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, Control3);
    constrolSpinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 2);
    mainLayout->addWidget(constrolSpinBox, 1, 4);

    setLayout( mainLayout);
}
