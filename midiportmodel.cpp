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
#ifdef Q_OS_LINUX
    else if(role == ClientIdRole)
    {
        return portList.at(index.row()).first.clientId;
    }
#endif
    else if(role == PortIdRole)
    {
#ifdef Q_OS_LINUX
        return portList.at(index.row()).first.portId;
#endif
#ifdef Q_OS_MACOS
        return portList.at(index.row()).first;
#endif
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
                ClientPortId cpid;
                cpid.clientId = clientId;
                cpid.portId = snd_seq_port_info_get_port(pinfo);
                portList.append(QPair<ClientPortId, QString>( cpid, snd_seq_port_info_get_name(pinfo)));
                qDebug("\tPort  %3d '%-16s'", cpid.portId, snd_seq_port_info_get_name(pinfo));
            }
            count++;
        }
    }
#endif
#ifdef Q_OS_MAC
    if( direction == ReadablePorts)
    {
        unsigned long sourceCount = MIDIGetNumberOfSources();
        qDebug("%ld sources\n", sourceCount);

        for (unsigned int i = 0; i < sourceCount; ++i)
        {
            MIDIEndpointRef src = MIDIGetSource(i);
            CFStringRef endpointName = nullptr;
            MIDIObjectGetStringProperty(src, kMIDIPropertyModel, &endpointName);
            char endpointNameC[255];
            CFStringGetCString(endpointName, endpointNameC, 255, kCFStringEncodingUTF8);
            portList.append(QPair<ClientPortId, QString>( src, endpointNameC));
            qDebug(" source %d: %s %d\n", i, endpointNameC, src);
        }
    }
    else
    {
        unsigned long destCount = MIDIGetNumberOfDestinations();
        qDebug("%ld destinations\n", destCount);
        for (unsigned int i = 0; i < destCount; ++i)
        {
            MIDIEndpointRef dest = MIDIGetDestination(i);
            CFStringRef endpointName = nullptr;
            MIDIObjectGetStringProperty(dest, kMIDIPropertyModel, &endpointName);
            char endpointNameC[255];
            CFStringGetCString(endpointName, endpointNameC, 255, kCFStringEncodingUTF8);
            portList.append(QPair<ClientPortId, QString>( dest, endpointNameC));
            qDebug(" destination %d: %s %d\n", i, endpointNameC, dest);
        }
    }
#endif
    endResetModel();
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
