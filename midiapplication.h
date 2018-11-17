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
#ifndef MIDIAPPLICATION_H
#define MIDIAPPLICATION_H

#include <QApplication>
#include <QSet>

#ifdef Q_OS_LINUX
typedef struct _snd_seq snd_seq_t;
typedef snd_seq_t* MidiClientHandle;

#include "midiportidalsa.h"
Q_DECLARE_METATYPE(MidiPortIdAlsa)

class MidiInThread;
class MidiSender;

#endif

#ifdef Q_OS_MACOS
typedef quint32 MidiClientHandle;
typedef quint32 MidiClientPortId;

class MIDINotification;
class MIDIPacketList;
class MIDISysexSendRequest;
#endif


class MidiPortModel;
class MidiEvent;

class MidiApplication : public QApplication
{
    Q_OBJECT
public:
    MidiApplication(int &argc, char **argv);

    MidiPortModel *ReadablePortsModel() { return readablePortsModel;}
    MidiPortModel *WritablePortsModel() { return writablePortsModel;}

    bool event(QEvent *) override;

signals:
    void midiEventReceived(MidiEvent *);

public slots:
    bool changeReadableMidiPortStatus( MidiClientPortId mcpId, bool connect );
    bool changeWritebleeMidiPortStatus( MidiClientPortId mcpId, bool connect );

    void sendMidiEvent(MidiEvent *ev);

private slots:

    void onPortConnectionStatusChanged(MidiClientPortId srcId, MidiClientPortId destId, bool isConnected);
    void onPortClientPortStatusChanged(MidiClientPortId mpId, bool isExisting);

    void isQuitting();

private:
#ifdef Q_OS_LINUX
    MidiInThread *midiInThread;
    QThread *midiOutThread;
    MidiSender *midiSender;
#endif
#ifdef Q_OS_MACOS
    static void MIDIEngineNotifyProc(const MIDINotification *message, void *refCon);
    static void MIDIEngineReadProc(const MIDIPacketList *pktlist, void *arg, void *connRefCon);
    static void sysexCompletionProc(MIDISysexSendRequest *req);
#endif

    MidiPortModel *readablePortsModel;
    MidiPortModel *writablePortsModel;

    MidiClientHandle handle;

    void midiSystemInit();

    MidiClientPortId thisInPort;
    MidiClientPortId thisOutPort;
};

#endif // MIDIAPPLICATION_H
