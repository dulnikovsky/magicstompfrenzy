#include "preferencesdialog.h"
#include <QDialogButtonBox>
#include <QHBoxLayout>
#include <QListView>
#include <QLabel>

#include "midiportmodel.h"

PreferencesDialog::PreferencesDialog(MidiPortModel *portsInModel, MidiPortModel *portsOutModel, QWidget *parent)
    : QDialog(parent), portsInModel(portsInModel), portsOutModel(portsOutModel)
{
    setWindowTitle(tr("Preferences"));

    QHBoxLayout *hlyt = new QHBoxLayout();

    hlyt->addWidget( new QLabel("Incoming MIDI Connections:"));
    portsInListView = new QListView();
    portsInListView->setModel(portsInModel);
    for( int r=0; r < portsInModel->rowCount(); r++)
    {
        QModelIndex index = portsInModel->index(r,0);
        if( portsInModel->data( index , MidiPortModel::isConnectedRole).toBool())
            portsInListView->selectionModel()->select(index, QItemSelectionModel::Select);
    }
    connect(portsInListView->selectionModel(), SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
            this, SLOT(midiInselectionChanged(QItemSelection,QItemSelection)));

    hlyt->addWidget(portsInListView);

    hlyt->addWidget( new QLabel("Outgoing MIDI Connections:"));
    portsOutListView = new QListView();
    portsOutListView->setModel(portsOutModel);
    for( int r=0; r < portsOutModel->rowCount(); r++)
    {
        QModelIndex index = portsOutModel->index(r,0);
        if( portsOutModel->data( index , MidiPortModel::isConnectedRole).toBool())
            portsOutListView->selectionModel()->select(index, QItemSelectionModel::Select);
    }
    connect(portsOutListView->selectionModel(), SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
            this, SLOT(midiOutselectionChanged(QItemSelection,QItemSelection)));
    hlyt->addWidget(portsOutListView);

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Close);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

    hlyt->addWidget(buttonBox);

    setLayout(hlyt);
}

void PreferencesDialog::midiInselectionChanged(const QItemSelection &selected, const QItemSelection &deselected)
{
    QModelIndexList indexList = selected.indexes();
    for( int i=0; i<indexList.size(); i++)
    {
        emit midiInPortStatusChanged( qvariant_cast<MidiClientPortId>( indexList.at(i).data(MidiPortModel::ClientPortIdRole)), true);
    }

    indexList = deselected.indexes();
    for( int i=0; i<indexList.size(); i++)
    {
        emit midiInPortStatusChanged( qvariant_cast<MidiClientPortId>( indexList.at(i).data(MidiPortModel::ClientPortIdRole)), false);
    }
}

void PreferencesDialog::midiOutselectionChanged(const QItemSelection &selected, const QItemSelection &deselected)
{
    QModelIndexList indexList = selected.indexes();
    for( int i=0; i<indexList.size(); i++)
    {
        emit midiOutPortStatusChanged( qvariant_cast<MidiClientPortId>( indexList.at(i).data(MidiPortModel::ClientPortIdRole)), true);
    }

    indexList = deselected.indexes();
    for( int i=0; i<indexList.size(); i++)
    {
        emit midiOutPortStatusChanged( qvariant_cast<MidiClientPortId>( indexList.at(i).data(MidiPortModel::ClientPortIdRole)), false);
    }
}
