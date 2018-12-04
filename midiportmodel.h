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
#ifndef MIDIPORTMODEL_H
#define MIDIPORTMODEL_H

#include <QAbstractItemModel>

#include "midiapplication.h"

#if defined(Q_OS_LINUX) || defined(Q_OS_MACOS)
typedef QSet<MidiClientPortId> ConnectionsContainer;
#endif

#ifdef Q_OS_WIN
typedef QMap<MidiClientPortId, void *> ConnectionsContainer;
#endif

class MidiPortModel : public QAbstractItemModel
{
    Q_OBJECT
public:

    enum UserRoles{ ClientPortIdRole = Qt::UserRole, isConnectedRole};
    enum Direction{ ReadablePorts, WritablePorts };

    MidiPortModel(MidiClientHandle handle,  Direction d = ReadablePorts, QObject *parent = Q_NULLPTR) :
        QAbstractItemModel(parent), handle(handle), direction(d) {}

    const ConnectionsContainer &currentConnections() const { return connectionsCont; }

    QVariant data(const QModelIndex &index, int role) const override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &) const override { return 1; }

    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &child) const override;

public slots:
    void scan();
    bool connectPorts(MidiClientPortId src, MidiClientPortId dest, bool connected);

private:
    MidiClientHandle handle;
    Direction direction;

    QList<QPair<MidiClientPortId, QString>> portList;
    ConnectionsContainer connectionsCont;

    void emitPortChanged(MidiClientPortId id);
};

#endif // MIDIPORTMODEL_H
