#ifndef MIDIPORTMODEL_H
#define MIDIPORTMODEL_H

#include <QAbstractItemModel>

#ifdef Q_OS_LINUX
typedef struct _snd_seq snd_seq_t;
#endif

class MidiPortModel : public QAbstractItemModel
{
    Q_OBJECT
public:

    enum UserRoles{ ClientIdRole = Qt::UserRole, PortIdRole};
    enum Direction{ ReadablePorts, WritablePorts };

#ifdef Q_OS_LINUX
    MidiPortModel(snd_seq_t *handle, Direction direction = ReadablePorts, QObject *parent = Q_NULLPTR) : QAbstractItemModel(parent), direction(d) {}
#endif
#ifdef Q_OS_MACOS
    MidiPortModel( Direction d = ReadablePorts, QObject *parent = Q_NULLPTR) : QAbstractItemModel(parent), direction(d) {}
#endif
    QVariant data(const QModelIndex &index, int role) const override;

    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &) const override { return 1; }

    QModelIndex index(int row, int column, const QModelIndex &parent) const override;
    QModelIndex parent(const QModelIndex &child) const override;

public slots:
    void scan();

private:
#ifdef Q_OS_LINUX
    snd_seq_t *handle;
#endif
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
