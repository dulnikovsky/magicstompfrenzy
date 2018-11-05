#ifndef MIDIPORTMODEL_H
#define MIDIPORTMODEL_H

#include <QAbstractItemModel>

#include "midiapplication.h"

class MidiPortModel : public QAbstractItemModel
{
    Q_OBJECT
public:

    enum UserRoles{ ClientIdRole = Qt::UserRole, PortIdRole};
    enum Direction{ ReadablePorts, WritablePorts };

    MidiPortModel(MidiClientHandle handle, Direction d = ReadablePorts, QObject *parent = Q_NULLPTR) :
        QAbstractItemModel(parent), handle(handle), direction(d) {}

    QVariant data(const QModelIndex &index, int role) const override;

    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &) const override { return 1; }

    QModelIndex index(int row, int column, const QModelIndex &parent) const override;
    QModelIndex parent(const QModelIndex &child) const override;

public slots:
    void scan();

private:
    MidiClientHandle handle;

    Direction direction;

#ifdef Q_OS_LINUX
    typedef struct
    {
        int clientId;
        int portId;
    }ClientPortId;
#endif
#ifdef Q_OS_MAC
    typedef unsigned int ClientPortId;
#endif

    QList<QPair<ClientPortId, QString>> portList;
};

#endif // MIDIPORTMODEL_H
