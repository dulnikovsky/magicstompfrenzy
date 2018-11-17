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
#include "midiportmodel.h"
#ifdef Q_OS_LINUX
#include <alsa/asoundlib.h>
#endif
#ifdef Q_OS_MACOS
#include <AudioToolbox/AudioToolbox.h>
#endif


QVariant MidiPortModel::data(const QModelIndex &index, int role) const
{
    if(role == Qt::DisplayRole)
    {
        return portList.at(index.row()).second;
    }
    else if(role == ClientPortIdRole)
    {
        QVariant valVariant;
        valVariant.setValue( portList.at(index.row()).first);
        return valVariant;
    }
    else if( role == isConnectedRole)
    {
        return connectionsSet.contains(portList.at(index.row()).first);
    }
    return QVariant();
}

int MidiPortModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return portList.size();
}

void MidiPortModel::scan()
{
    beginResetModel();
    portList.clear();
#ifdef Q_OS_LINUX
    snd_seq_client_info_t *cinfo;
    snd_seq_port_info_t *pinfo;
    int count;

    snd_seq_client_info_alloca(&cinfo);
    snd_seq_port_info_alloca(&pinfo);
    snd_seq_client_info_set_client(cinfo, -1);
    while (snd_seq_query_next_client(handle, cinfo) >= 0)
    {
        int clientId = snd_seq_client_info_get_client( cinfo);
        qDebug("Client  %3d '%-16s'", clientId, snd_seq_client_info_get_name( cinfo));
        if( (clientId == SND_SEQ_CLIENT_SYSTEM) || (clientId == snd_seq_client_id(handle)))
            continue;
        /* reset query info */
        snd_seq_port_info_set_client(pinfo, clientId);
        snd_seq_port_info_set_port(pinfo, -1);
        count = 0;
        while (snd_seq_query_next_port(handle, pinfo) >= 0)
        {
            unsigned int cap = snd_seq_port_info_get_capability(pinfo);
            if( ((cap & (SND_SEQ_PORT_CAP_READ|SND_SEQ_PORT_CAP_SUBS_READ)) && direction==ReadablePorts) ||
                    ((cap & (SND_SEQ_PORT_CAP_WRITE|SND_SEQ_PORT_CAP_SUBS_WRITE)) && direction==WritablePorts) )
            {
                MidiClientPortId mcpId( clientId, snd_seq_port_info_get_port(pinfo));
                portList.append(QPair<MidiClientPortId, QString>( mcpId, snd_seq_port_info_get_name(pinfo)));
            }
            count++;
        }
    }
#endif
#ifdef Q_OS_MAC
    char charArr[255];
    if( direction == ReadablePorts)
    {
        unsigned long sourceCount = MIDIGetNumberOfSources();
        qDebug("%ld sources\n", sourceCount);

        for (unsigned int i = 0; i < sourceCount; ++i)
        {
            MIDIEndpointRef src = MIDIGetSource(i);
            CFStringRef modelName = nullptr;
            MIDIObjectGetStringProperty(src, kMIDIPropertyModel, &modelName);
            CFStringGetCString(modelName, charArr, 255, kCFStringEncodingUTF8);

            QString fullName(charArr);

            CFStringRef name = nullptr;
            MIDIObjectGetStringProperty(src, kMIDIPropertyName, &name);
            CFStringGetCString(name, charArr, 255, kCFStringEncodingUTF8);

            fullName.append(" " + QString(charArr));

            portList.append(QPair<MidiClientPortId, QString>( src, fullName));
            qDebug(" source %d: %s %d\n", i, charArr, src);
        }
    }
    else
    {
        unsigned long destCount = MIDIGetNumberOfDestinations();
        qDebug("%ld destinations\n", destCount);
        for (unsigned int i = 0; i < destCount; ++i)
        {
            MIDIEndpointRef dest = MIDIGetDestination(i);
            CFStringRef modelName = nullptr;
            MIDIObjectGetStringProperty(dest, kMIDIPropertyModel, &modelName);

            CFStringGetCString(modelName, charArr, 255, kCFStringEncodingUTF8);

            QString fullName(charArr);

            CFStringRef name = nullptr;
            MIDIObjectGetStringProperty(dest, kMIDIPropertyName, &name);
            CFStringGetCString(name, charArr, 255, kCFStringEncodingUTF8);

            fullName.append(" " + QString(charArr));

            portList.append(QPair<MidiClientPortId, QString>( dest, fullName));
            qDebug(" destination %d: %s %d\n", i, charArr, dest);
        }
    }
#endif
    endResetModel();
}

bool MidiPortModel::connectPorts(MidiClientPortId srcId, MidiClientPortId destId, bool connected)
{
#ifdef Q_OS_LINUX
    snd_seq_addr_t sender, dest;
    snd_seq_port_subscribe_t* subs;
    snd_seq_port_subscribe_alloca(&subs);

    sender.client = static_cast<unsigned char>(srcId.clientId());
    sender.port = static_cast<unsigned char>(srcId.portId());
    dest.client = static_cast<unsigned char>(destId.clientId());
    dest.port = static_cast<unsigned char>(destId.portId());

    snd_seq_port_subscribe_set_sender(subs, &sender);
    snd_seq_port_subscribe_set_dest(subs, &dest);
#endif

    if(connected)
    {
        if(direction == ReadablePorts)
        {
            if(connectionsSet.contains(srcId))
                return true;
            connectionsSet.insert(srcId);
            emitPortChanged(srcId);
        }
        else
        {
            if(connectionsSet.contains(destId))
                return true;
            connectionsSet.insert(destId);
            emitPortChanged(destId);
        }
#ifdef Q_OS_LINUX
        return snd_seq_subscribe_port(handle, subs);
#endif
#ifdef Q_OS_MACOS
        return MIDIPortConnectSource(destId, srcId, nullptr);
#endif
    }
    else
    {
        if(direction == ReadablePorts)
        {
            if(! connectionsSet.contains(srcId))
                return true;
            connectionsSet.remove(srcId);
            emitPortChanged(srcId);
        }
        else
        {
            if(! connectionsSet.contains(destId))
                return true;
            connectionsSet.remove(destId);
            emitPortChanged(destId);
        }
#ifdef Q_OS_LINUX
        return snd_seq_unsubscribe_port(handle, subs);
#endif
#ifdef Q_OS_MACOS
        return MIDIPortDisconnectSource( srcId, destId);
#endif
    }
}

void MidiPortModel::emitPortChanged(MidiClientPortId id)
{
    int row;
    for(row=0; row<portList.size(); row++)
    {
        if( portList.at(row).first == id)
            break;
    }
    if(row < portList.size())
    {
        emit dataChanged( index(row,0), index(row,0));
    }
}

QModelIndex MidiPortModel::index(int row, int column, const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return createIndex( row, column);
}

QModelIndex MidiPortModel::parent(const QModelIndex &child) const
{
    Q_UNUSED(child)
    return QModelIndex();
}
;
