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

    MidiPortModel(snd_seq_t *handle, Direction direction = ReadablePorts, QObject *parent = Q_NULLPTR);

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

    typedef struct
    {
        int clientId;
        int portId;
    }ClientPortId;

    QList<QPair<ClientPortId, QString>> portList;
};

#endif // MIDIPORTMODEL_H
