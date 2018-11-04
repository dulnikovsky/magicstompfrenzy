#ifndef PATCHLISTCOMBOMODEL_H
#define PATCHLISTCOMBOMODEL_H

#include <QAbstractItemModel>

class PatchListComboModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    PatchListComboModel( QObject *parent = nullptr) : QAbstractItemModel(parent), sourcemodel(nullptr), disabledRow(-1) { }

    void setSourceModel(QAbstractItemModel *model) { beginResetModel(); sourcemodel = model; endResetModel(); }
    void setDisabledRow(int row) { disabledRow = row; }

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    int rowCount(const QModelIndex &parent) const override { return sourcemodel!=nullptr?sourcemodel->rowCount(parent):0; }
    int columnCount(const QModelIndex &) const override { return 1; }

    QModelIndex index(int row, int column, const QModelIndex & = QModelIndex()) const override { return createIndex(row, column); }
    QModelIndex parent(const QModelIndex &) const override { return QModelIndex(); }

    Qt::ItemFlags flags(const QModelIndex &index) const override;
private:
    QAbstractItemModel *sourcemodel;
    int disabledRow;
};

#endif // PATCHLISTCOMBOMODEL_H
