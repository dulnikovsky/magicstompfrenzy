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
#include "preferencesdialog.h"
#include <QDialogButtonBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QListView>
#include <QLabel>
#include <QCheckBox>
#include <QSpinBox>
#include <QSettings>
#include <QTabWidget>
#include <QComboBox>

#include "midiportmodel.h"

PreferencesDialog::PreferencesDialog(MidiPortModel *portsInModel, MidiPortModel *portsOutModel, QMap<QString, int> &paraToCCMap, QWidget *parent)
    : QDialog(parent), portsInModel(portsInModel), portsOutModel(portsOutModel), paraToCCMap(paraToCCMap)
{
    connect( portsInModel, SIGNAL(dataChanged(QModelIndex,QModelIndex,QVector<int>)),
             this, SLOT(portsInModelDataChanged(QModelIndex,QModelIndex,QVector<int>)));

    connect( portsOutModel, SIGNAL(dataChanged(QModelIndex,QModelIndex,QVector<int>)),
        this, SLOT(portsOutModelDataChanged(QModelIndex,QModelIndex,QVector<int>)));

    setWindowTitle(tr("Preferences"));

    QVBoxLayout *midiConnectionsLayout = new QVBoxLayout();
    midiConnectionsLayout->addWidget(new QLabel(tr("Set the MIDI connections by selecting MIDI ports in both lists:")));
    QHBoxLayout *hlyt = new QHBoxLayout();

    hlyt->addWidget( new QLabel("Incoming MIDI Connections:"));
    portsInListView = new QListView();
    portsInListView->setSelectionMode(QAbstractItemView::ExtendedSelection);
    portsInListView->setModel(portsInModel);
    for( int r=0; r < portsInModel->rowCount(); r++)
    {
        QModelIndex index = portsInModel->index(r,0);
        if( portsInModel->data( index , MidiPortModel::isConnectedRole).toBool())
            portsInListView->selectionModel()->select(index, QItemSelectionModel::Select);
    }
    connect(portsInListView->selectionModel(), SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
            this, SLOT(midiInselectionChanged(QItemSelection,QItemSelection)));

    hlyt->addWidget(portsInListView);

    hlyt->addWidget( new QLabel("Outgoing MIDI Connections:"));
    portsOutListView = new QListView();
    portsOutListView->setSelectionMode(QAbstractItemView::ExtendedSelection);
    portsOutListView->setModel(portsOutModel);
    for( int r=0; r < portsOutModel->rowCount(); r++)
    {
        QModelIndex index = portsOutModel->index(r,0);
        if( portsOutModel->data( index , MidiPortModel::isConnectedRole).toBool())
            portsOutListView->selectionModel()->select(index, QItemSelectionModel::Select);
    }
    connect(portsOutListView->selectionModel(), SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
            this, SLOT(midiOutselectionChanged(QItemSelection,QItemSelection)));
    hlyt->addWidget(portsOutListView);

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Close);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

    midiConnectionsLayout->addLayout(hlyt);

    QCheckBox *restoreConnectionsCheckBox = new QCheckBox(tr("Reconnect at startup"));
    QSettings settings;
    restoreConnectionsCheckBox->setChecked(settings.value(QStringLiteral("RestoreMidiConnectionsAtStartUp"), true).toBool());
    connect(
        restoreConnectionsCheckBox, &QCheckBox::toggled,
        [=]( bool checked) {
            QSettings settings;
            settings.setValue(QStringLiteral("RestoreMidiConnectionsAtStartUp"), checked);
        }
    );
    midiConnectionsLayout->addWidget(restoreConnectionsCheckBox);

    QSpinBox *channelSpinBox = new QSpinBox();
    channelSpinBox->setMinimum(0);
    channelSpinBox->setMaximum(16);
    channelSpinBox->setSpecialValueText(QStringLiteral("OMNI"));
    settings.beginGroup(QStringLiteral("MidiControls"));
    channelSpinBox->setValue(settings.value(QStringLiteral("MIDIChannel"), 0).toInt());
    settings.endGroup();
    connect( channelSpinBox, SIGNAL(valueChanged(int)), this, SIGNAL(midiChannelChanged(int)));
    connect(
        channelSpinBox, qOverload<int>(&QSpinBox::valueChanged),
        [=]( int val) {
            QSettings settings;
            settings.beginGroup(QStringLiteral("MidiControls"));
            settings.setValue(QStringLiteral("MIDIChannel"), val);
            settings.endGroup();
        }
    );

    QGridLayout *controlsGridLayout = new QGridLayout();
    controlsGridLayout->addWidget( new QLabel("MIDI Channel:"), 0, 0);
    controlsGridLayout->addWidget( channelSpinBox, 0, 1);

    controlsGridLayout->addWidget( new QLabel("Control Change Number Assigments:"), 1, 0, 1, 2);

    controlsGridLayout->addWidget( new QLabel("Master:"), 2, 0);
    controlsGridLayout->addWidget( createParaCCSpinBox( QStringLiteral("Master")), 2, 1);
    controlsGridLayout->addWidget( createParaCCModeComboBox( QStringLiteral("Master")), 2, 2);
    controlsGridLayout->addWidget( createParaCCInitModeComboBox( QStringLiteral("Master")), 2, 3);
    controlsGridLayout->addWidget( new QLabel("Master Volume Control of the Preamp and Distortion"), 2, 4);

    controlsGridLayout->addWidget( new QLabel("Gain:"), 3, 0);
    controlsGridLayout->addWidget( createParaCCSpinBox(QStringLiteral("Gain")), 3, 1);
    controlsGridLayout->addWidget( createParaCCModeComboBox(QStringLiteral("Gain")), 3, 2);
    controlsGridLayout->addWidget( createParaCCInitModeComboBox(QStringLiteral("Gain")), 3, 3);
    controlsGridLayout->addWidget( new QLabel("Gain Control of the Preamp and Distortion"), 3, 4);

    controlsGridLayout->addWidget( new QLabel("Effect Level:"), 4, 0);
    controlsGridLayout->addWidget( createParaCCSpinBox(QStringLiteral("EffectLevel")), 4, 1);
    controlsGridLayout->addWidget( createParaCCModeComboBox(QStringLiteral("EffectLevel")), 4, 2);
    controlsGridLayout->addWidget( createParaCCInitModeComboBox(QStringLiteral("EffectLevel")), 4, 3);
    controlsGridLayout->addWidget( new QLabel("Effect Level of all Multiband Delays"), 4, 4);

    controlsGridLayout->setColumnStretch( 5, 4);
    controlsGridLayout->setRowStretch( 8, 8);

    QVBoxLayout *mainLayout = new QVBoxLayout();
    QTabWidget *tabWidget = new QTabWidget();
    mainLayout->addWidget(tabWidget);
    QWidget *tab1Widget = new QWidget();
    tab1Widget->setLayout(midiConnectionsLayout);
    tabWidget->addTab(tab1Widget, tr("MIDI Connections"));

    QWidget *tab2Widget = new QWidget();
    tab2Widget->setLayout(controlsGridLayout);
    tabWidget->addTab(tab2Widget, tr("MIDI Controls"));

    mainLayout->addWidget(buttonBox);

    setLayout(mainLayout);

    QPalette palette = this->palette();
    QColor color = palette.color(QPalette::Active, QPalette::Highlight);
    palette.setColor(QPalette::Inactive, QPalette::Highlight, color);
    color = palette.color(QPalette::Active, QPalette::HighlightedText);
    palette.setColor(QPalette::Inactive, QPalette::HighlightedText, color);
    setPalette(palette);
}

void PreferencesDialog::portsInModelDataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &roles)
{
    Q_UNUSED(bottomRight)
    Q_UNUSED(roles)

    if( topLeft.data( MidiPortModel::isConnectedRole).toBool())
        portsInListView->selectionModel()->select(topLeft, QItemSelectionModel::Select);
    else
        portsInListView->selectionModel()->select(topLeft, QItemSelectionModel::Deselect);
}
void PreferencesDialog::portsOutModelDataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &roles)
{
    Q_UNUSED(bottomRight)
    Q_UNUSED(roles)

    if( topLeft.data( MidiPortModel::isConnectedRole).toBool())
        portsOutListView->selectionModel()->select(topLeft, QItemSelectionModel::Select);
    else
        portsOutListView->selectionModel()->select(topLeft, QItemSelectionModel::Deselect);
}

void PreferencesDialog::midiInselectionChanged(const QItemSelection &selected, const QItemSelection &deselected)
{
    QModelIndexList indexList = selected.indexes();
    for( int i=0; i<indexList.size(); i++)
    {
        emit midiInPortStatusChanged( qvariant_cast<MidiClientPortId>( indexList.at(i).data(MidiPortModel::ClientPortIdRole)), true);
    }

    indexList = deselected.indexes();
    for( int i=0; i<indexList.size(); i++)
    {
        emit midiInPortStatusChanged( qvariant_cast<MidiClientPortId>( indexList.at(i).data(MidiPortModel::ClientPortIdRole)), false);
    }
}

void PreferencesDialog::midiOutselectionChanged(const QItemSelection &selected, const QItemSelection &deselected)
{
    QModelIndexList indexList = selected.indexes();
    for( int i=0; i<indexList.size(); i++)
    {
        emit midiOutPortStatusChanged( qvariant_cast<MidiClientPortId>( indexList.at(i).data(MidiPortModel::ClientPortIdRole)), true);
    }

    indexList = deselected.indexes();
    for( int i=0; i<indexList.size(); i++)
    {
        emit midiOutPortStatusChanged( qvariant_cast<MidiClientPortId>( indexList.at(i).data(MidiPortModel::ClientPortIdRole)), false);
    }
}

QSpinBox *PreferencesDialog::createParaCCSpinBox(const QString &name)
{
    QSpinBox *spinbox= new QSpinBox();
    spinbox->setMaximum(127);
    spinbox->setObjectName( name);

    QMap<QString, int>::iterator iter = paraToCCMap.find(name);
    if(iter != paraToCCMap.end())
    {
        spinbox->setValue( iter.value() & 0x7F);
    }
    connect(spinbox, SIGNAL(valueChanged(int)), this, SLOT(paraCCSpinBoxValueChanged(int)));
    return spinbox;
}

void PreferencesDialog::paraCCSpinBoxValueChanged(int val)
{
    QObject *obj = QObject::sender();
    QString name = obj->objectName();

    QMap<QString, int>::iterator iter = paraToCCMap.find(name);
    if(iter != paraToCCMap.end())
    {
        int oldVal = iter.value();
        iter.value() = (iter.value() & 0xFF00) | (val & 0x7F);
        emit paramToCCChanged(name, iter.value(), oldVal);
    }
}

QComboBox *PreferencesDialog::createParaCCModeComboBox(const QString &name)
{
    QComboBox *cbox = new QComboBox();
    cbox->setObjectName( name);

    static const QStringList ccModeStringList = { "Continous", "Switch - Latch Mode"};
    cbox->addItems(ccModeStringList);

    QMap<QString, int>::iterator iter = paraToCCMap.find(name);
    if(iter != paraToCCMap.end())
    {
        cbox->setCurrentIndex( (iter.value() & 0x0F00) >> 8 );
    }
    connect( cbox, SIGNAL(currentIndexChanged(int)), this, SLOT(paraCCModeComboBoxValueChanged(int)));
    return cbox;
}

void PreferencesDialog::paraCCModeComboBoxValueChanged(int val)
{
    QObject *obj = QObject::sender();
    QString name = obj->objectName();

    QMap<QString, int>::iterator iter = paraToCCMap.find(name);
    if(iter != paraToCCMap.end())
    {
        int oldVal = iter.value();
        iter.value() = (iter.value() & 0xF0FF) | (val << 8);
        emit paramToCCChanged(name, iter.value(), oldVal);
    }
}

QComboBox *PreferencesDialog::createParaCCInitModeComboBox(const QString &name)
{
    QComboBox *cbox = new QComboBox();
    cbox->setObjectName( name);

    static const QStringList ccModeStringList = { "Minimum", "Patch Value" };
    cbox->addItems(ccModeStringList);

    QMap<QString, int>::iterator iter = paraToCCMap.find(name);
    if(iter != paraToCCMap.end())
    {
        cbox->setCurrentIndex( (iter.value() & 0xF000) >> 12 );
    }
    connect( cbox, SIGNAL(currentIndexChanged(int)), this, SLOT(paraCCInitModeComboBoxValueChanged(int)));
    return cbox;
}

void PreferencesDialog::paraCCInitModeComboBoxValueChanged(int val)
{
    QObject *obj = QObject::sender();
    QString name = obj->objectName();

    QMap<QString, int>::iterator iter = paraToCCMap.find(name);
    if(iter != paraToCCMap.end())
    {
        int oldVal = iter.value();
        iter.value() = (iter.value() & 0x0FFF) | (val << 12);
        emit paramToCCChanged(name, iter.value(), oldVal);
    }
}
