#ifndef PATCHLISTMODEL_H
#define PATCHLISTMODEL_H

#include <QAbstractItemModel>

class PatchListModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    PatchListModel( const QList<QByteArray> &patchDataList, QObject *parent = Q_NULLPTR);

    QVariant data(const QModelIndex &index, int role) const override;

    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &) const override { return 1; }

    QModelIndex index(int row, int column, const QModelIndex &parent) const override;
    QModelIndex parent(const QModelIndex &child) const override;

    void patchUpdated( int index);

private:
    const QList<QByteArray> &patchDataRef;
};

#endif // MIDIPORTMODEL_H
