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
#ifndef MIDISENDER_H
#define MIDISENDER_H

#include <QObject>

typedef struct _snd_seq snd_seq_t;
#include "midiportidalsa.h"

class MidiSender : public QObject
{
    Q_OBJECT
public:
    explicit MidiSender(snd_seq_t *handle, MidiClientPortId outport, QObject *parent = nullptr) : QObject(parent), handle(handle), outport(outport) {}

    bool event(QEvent *) override;

signals:

public slots:

private:
    snd_seq_t *handle;
    MidiClientPortId outport;
};

#endif // MIDISENDER_H
