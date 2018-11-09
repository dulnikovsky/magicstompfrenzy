#ifndef MIDIPORTMODEL_H
#define MIDIPORTMODEL_H

#include <QAbstractItemModel>

#include "midiapplication.h"

class MidiPortModel : public QAbstractItemModel
{
    Q_OBJECT
public:

    enum UserRoles{ ClientPortIdRole = Qt::UserRole, isConnectedRole};
    enum Direction{ ReadablePorts, WritablePorts };

    MidiPortModel(MidiClientHandle handle,  Direction d = ReadablePorts, QObject *parent = Q_NULLPTR) :
        QAbstractItemModel(parent), handle(handle), direction(d) {}

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
    QSet<MidiClientPortId> connectionsSet;

    void emitPortChanged(MidiClientPortId id);
};

#endif // MIDIPORTMODEL_H
