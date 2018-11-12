#include "patchcopydialog.h"
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QComboBox>
#include <QLabel>

#include "patchlistmodel.h"
#include "patchlistcombomodel.h"

PatchCopyDialog::PatchCopyDialog(PatchListModel *model, const QString& patchToCopyName, QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle(tr("Copy Patch"));

    PatchListComboModel *comboModel = new PatchListComboModel(this);
    //comboModel->setDisabledRow( patchToCopyIdx);
    comboModel->setSourceModel(model);

    QVBoxLayout *vlyt = new QVBoxLayout();

    QString txt = tr("Copy Patch '%1' to User patch:").arg(patchToCopyName);

    QLabel *infoLobale = new QLabel(txt);
    vlyt->addWidget(infoLobale);

    targetPatchCombo = new QComboBox();
    targetPatchCombo->setModel(comboModel);
    vlyt->addWidget(targetPatchCombo);

    vlyt->addWidget(new QLabel(tr("INFO: Target patch will be overwritten.")));

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

    vlyt->addWidget(buttonBox);

    setLayout(vlyt);
}

int PatchCopyDialog::targetPatchIndex() const
{
    return targetPatchCombo->currentIndex();
}
