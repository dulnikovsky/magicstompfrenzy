/****************************************************************************
**
** Copyright (C) 2018 Robert Vetter.
**
** This file is part of the MagicstompFrenzy - an editor for Yamaha Magicstomp
** effect processor
**
** THIS CODE IS PROVIDED *AS IS* WITHOUT WARRANTY OF
** ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING ANY
** IMPLIED WARRANTIES OF FITNESS FOR A PARTICULAR
** PURPOSE, MERCHANTABILITY, OR NON-INFRINGEMENT.
**
** GNU General Public License Usage
** This file may be used under the terms of the GNU
** General Public License version 2.0 or (at your option) the GNU General
** Public license version 3 or any later version . The licenses are
** as published by the Free Software Foundation and appearing in the file LICENSE
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-2.0.html and
** https://www.gnu.org/licenses/gpl-3.0.html.
**/
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
