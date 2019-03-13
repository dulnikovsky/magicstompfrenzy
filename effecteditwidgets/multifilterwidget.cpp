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
#include "multifilterwidget.h"

#include <QGridLayout>

#include <QLabel>
#include <QSpinBox>
#include "renardseriesspinbox.h"
#include <QComboBox>

MultiFilterWidget::MultiFilterWidget( QWidget *parent) :
    EffectEditBaseWidget(parent)
{
    QSpinBox *spinBox;

    QGridLayout *mainlyt = new QGridLayout();

    mainlyt->addWidget(new QLabel(tr("Mix")), 0, 0);
    spinBox = new QSpinBox();
    spinBox->setMinimum(0);
    spinBox->setMaximum(100);
    spinBox->setSuffix(" %");
    spinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, Mix);
    spinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    mainlyt->addWidget(spinBox, 1, 0);

    QGroupBox *filter1GroupBox = new QGroupBox(QStringLiteral("Filter 1"));
    QGridLayout *filter1Layout = new QGridLayout();

    filter1Layout->addWidget(new QLabel(tr("Type")), 0, 0);
    QComboBox *distComboBox = new QComboBox();
    distComboBox->addItem(QStringLiteral("Low Pass Filter"));
    distComboBox->addItem(QStringLiteral("High Pass Filter"));
    distComboBox->addItem(QStringLiteral("Band Pass Filter"));
    distComboBox->setCurrentIndex(-1);
    distComboBox->setProperty( ArrayDataEditWidget::valuePropertyName, QStringLiteral("currentIndex"));
    distComboBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, Type1);
    distComboBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    filter1Layout->addWidget( distComboBox, 1, 0);

    filter1Layout->addWidget(new QLabel(tr("Freqency (Hz)")), 0, 1);
    RenardSeriesSpinBox *rspinBox = new RenardSeriesSpinBox();
    rspinBox->setRawOffsetValue( 58);
    rspinBox->setParameters( 40, 0, 0x6E );
    rspinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, Freq1);
    rspinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    filter1Layout->addWidget(rspinBox, 1, 1);

    filter1Layout->addWidget(new QLabel(tr("Resonance")), 0, 2);
    spinBox = new QSpinBox();
    spinBox->setMinimum(0);
    spinBox->setMaximum(20);
    spinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, Resonance1);
    spinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    filter1Layout->addWidget(spinBox, 1, 2);

    filter1Layout->addWidget(new QLabel(tr("Level")), 0, 3);
    spinBox = new QSpinBox();
    spinBox->setMinimum(0);
    spinBox->setMaximum(100);
    spinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, Level1);
    spinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    filter1Layout->addWidget(spinBox, 1, 3);

    filter1GroupBox->setLayout( filter1Layout);


    QGroupBox *filter2GroupBox = new QGroupBox(QStringLiteral("Filter 2"));
    QGridLayout *filter2Layout = new QGridLayout();

    filter2Layout->addWidget(new QLabel(tr("Type")), 0, 0);
    distComboBox = new QComboBox();
    distComboBox->addItem(QStringLiteral("Low Pass Filter"));
    distComboBox->addItem(QStringLiteral("High Pass Filter"));
    distComboBox->addItem(QStringLiteral("Band Pass Filter"));
    distComboBox->setCurrentIndex(-1);
    distComboBox->setProperty( ArrayDataEditWidget::valuePropertyName, QStringLiteral("currentIndex"));
    distComboBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, Type2);
    distComboBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    filter2Layout->addWidget( distComboBox, 1, 0);

    filter2Layout->addWidget(new QLabel(tr("Freqency (Hz)")), 0, 1);
    rspinBox = new RenardSeriesSpinBox();
    rspinBox->setRawOffsetValue( 58);
    rspinBox->setParameters( 40, 0, 0x6E );
    rspinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, Freq2);
    rspinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    filter2Layout->addWidget(rspinBox, 1, 1);

    filter2Layout->addWidget(new QLabel(tr("Resonance")), 0, 2);
    spinBox = new QSpinBox();
    spinBox->setMinimum(0);
    spinBox->setMaximum(20);
    spinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, Resonance2);
    spinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    filter2Layout->addWidget(spinBox, 1, 2);

    filter2Layout->addWidget(new QLabel(tr("Level")), 0, 3);
    spinBox = new QSpinBox();
    spinBox->setMinimum(0);
    spinBox->setMaximum(100);
    spinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, Level2);
    spinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    filter2Layout->addWidget(spinBox, 1, 3);

    filter2GroupBox->setLayout(filter2Layout);

    QGroupBox *filter3GroupBox = new QGroupBox(QStringLiteral("Filter 3"));
    QGridLayout *filter3Layout = new QGridLayout();

    filter3Layout->addWidget(new QLabel(tr("Type")), 0, 0);
    distComboBox = new QComboBox();
    distComboBox->addItem(QStringLiteral("Low Pass Filter"));
    distComboBox->addItem(QStringLiteral("High Pass Filter"));
    distComboBox->addItem(QStringLiteral("Band Pass Filter"));
    distComboBox->setCurrentIndex(-1);
    distComboBox->setProperty( ArrayDataEditWidget::valuePropertyName, QStringLiteral("currentIndex"));
    distComboBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, Type3);
    distComboBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    filter3Layout->addWidget( distComboBox, 1, 0);

    filter3Layout->addWidget(new QLabel(tr("Freqency (Hz)")), 0, 1);
    rspinBox = new RenardSeriesSpinBox();
    rspinBox->setRawOffsetValue( 58);
    rspinBox->setParameters( 40, 0, 0x6E );
    rspinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, Freq3);
    rspinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    filter3Layout->addWidget(rspinBox, 1, 1);

    filter3Layout->addWidget(new QLabel(tr("Resonance")), 0, 2);
    spinBox = new QSpinBox();
    spinBox->setMinimum(0);
    spinBox->setMaximum(20);
    spinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, Resonance3);
    spinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    filter3Layout->addWidget(spinBox, 1, 2);

    filter3Layout->addWidget(new QLabel(tr("Level")), 0, 3);
    spinBox = new QSpinBox();
    spinBox->setMinimum(0);
    spinBox->setMaximum(100);
    spinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, Level3);
    spinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    filter3Layout->addWidget(spinBox, 1, 3);

    filter3GroupBox->setLayout(filter3Layout);


    mainlyt->addWidget(filter1GroupBox, 2, 0);
    mainlyt->addWidget(filter2GroupBox, 3, 0);
    mainlyt->addWidget(filter3GroupBox, 4, 0);
    setLayout(mainlyt);
}
