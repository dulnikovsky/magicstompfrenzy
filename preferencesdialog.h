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
#ifndef PREFERENCESDIALOG_H
#define PREFERENCESDIALOG_H

#include <QDialog>
#include "midiapplication.h"

class QListView;
class QItemSelection;

class PreferencesDialog : public QDialog
{
    Q_OBJECT
public:
    explicit PreferencesDialog( MidiPortModel *portsInModel, MidiPortModel *portsOutModel, QWidget *parent = nullptr);

signals:
    void midiInPortStatusChanged( MidiClientPortId portId, bool isSelected);
    void midiOutPortStatusChanged( MidiClientPortId portId, bool isSelected);

private slots:
    void midiInselectionChanged(const QItemSelection &selected, const QItemSelection &deselected);
    void midiOutselectionChanged(const QItemSelection &selected, const QItemSelection &deselected);

    void portsInModelDataChanged(const QModelIndex&topLeft, const QModelIndex &bottomRight, const QVector<int> &roles = QVector<int>());
    void portsOutModelDataChanged(const QModelIndex&topLeft, const QModelIndex &bottomRight, const QVector<int> &roles = QVector<int>());

private:
    MidiPortModel *portsInModel;
    MidiPortModel *portsOutModel;
    QListView *portsInListView;
    QListView *portsOutListView;
};

#endif // PATCHCOPYDIALOG_H
