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
#include <QListView>
#include <QLabel>
#include <QCheckBox>
#include <QSettings>

#include "midiportmodel.h"

PreferencesDialog::PreferencesDialog(MidiPortModel *portsInModel, MidiPortModel *portsOutModel, QWidget *parent)
    : QDialog(parent), portsInModel(portsInModel), portsOutModel(portsOutModel)
{
    connect( portsInModel, SIGNAL(dataChanged(QModelIndex,QModelIndex,QVector<int>)),
             this, SLOT(portsInModelDataChanged(QModelIndex,QModelIndex,QVector<int>)));

    connect( portsOutModel, SIGNAL(dataChanged(QModelIndex,QModelIndex,QVector<int>)),
        this, SLOT(portsOutModelDataChanged(QModelIndex,QModelIndex,QVector<int>)));

    setWindowTitle(tr("Preferences"));

    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addWidget(new QLabel(tr("Set the MIDI connections by selecting MIDI ports in both lists:")));
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

    mainLayout->addLayout(hlyt);

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

    mainLayout->addWidget(restoreConnectionsCheckBox);
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
    if( topLeft.data( MidiPortModel::isConnectedRole).toBool())
        portsInListView->selectionModel()->select(topLeft, QItemSelectionModel::Select);
    else
        portsInListView->selectionModel()->select(topLeft, QItemSelectionModel::Deselect);
}
void PreferencesDialog::portsOutModelDataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &roles)
{
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
