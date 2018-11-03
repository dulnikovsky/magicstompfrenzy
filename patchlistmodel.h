#ifndef PATCHLISTMODEL_H
#define PATCHLISTMODEL_H

#include <QAbstractItemModel>

class PatchListModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    PatchListModel( const QList<QByteArray> &patchDataList, const QSet<int> &dirtyPatches, QObject *parent = Q_NULLPTR);

    QVariant data(const QModelIndex &index, int role) const override;

    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &) const override { return 2; }

    QModelIndex index(int row, int column, const QModelIndex &parent) const override;
    QModelIndex parent(const QModelIndex &child) const override;

    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

    void patchUpdated( int index);

private:
    const QList<QByteArray> &patchDataRef;
    const QSet<int> &dirtyPatches;
};

#endif // MIDIPORTMODEL_H
