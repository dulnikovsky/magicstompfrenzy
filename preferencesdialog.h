#ifndef PREFERENCESDIALOG_H
#define PREFERENCESDIALOG_H

#include <QDialog>
#include "midiapplication.h"

class QListView;
class QItemSelection;

class PreferencesDialog : public QDialog
{
    Q_OBJECT
public:
    explicit PreferencesDialog( MidiPortModel *portsInModel, MidiPortModel *portsOutModel, QWidget *parent = nullptr);

signals:
    void midiInPortStatusChanged( MidiClientPortId portId, bool isSelected);
    void midiOutPortStatusChanged( MidiClientPortId portId, bool isSelected);

private slots:
    void midiInselectionChanged(const QItemSelection &selected, const QItemSelection &deselected);
    void midiOutselectionChanged(const QItemSelection &selected, const QItemSelection &deselected);

    void portsInModelDataChanged(const QModelIndex&topLeft, const QModelIndex &bottomRight, const QVector<int> &roles = QVector<int>());
    void portsOutModelDataChanged(const QModelIndex&topLeft, const QModelIndex &bottomRight, const QVector<int> &roles = QVector<int>());

private:
    MidiPortModel *portsInModel;
    MidiPortModel *portsOutModel;
    QListView *portsInListView;
    QListView *portsOutListView;
};

#endif // PATCHCOPYDIALOG_H
