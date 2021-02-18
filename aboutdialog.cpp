/****************************************************************************
**
** Copyright (C) 2019 Robert Vetter.
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
#include "aboutdialog.h"

#include <QGridLayout>
#include <QPushButton>
#include <QApplication>
#include <QLabel>
#include <QDesktopServices>
#include <QUrl>

AboutDialog::AboutDialog(QWidget *parent) : QDialog(parent)
{
    setWindowTitle("About MagicstompFrenzy");

    QGridLayout *mainlyt = new QGridLayout();

    QLabel *appLabel = new QLabel( qApp->applicationName() + " (C) 2018-2021 Robert Vetter. Version: " + qApp->applicationVersion());
    mainlyt->addWidget(appLabel, 0,0, 1, 2);

    mainlyt->addWidget(new QLabel(tr("Online Manual: ")), 1,0);
    QLabel *helpLabel = new QLabel();
    helpLabel->setText("<a href=\"https://github.com/dulnikovsky/magicstompfrenzy/blob/master/README.md\">Magicstompfrenzy Manual on GitHub</a>");
    helpLabel->setTextInteractionFlags(Qt::TextBrowserInteraction);
    connect(helpLabel, &QLabel::linkActivated, []() {
            QDesktopServices::openUrl(QUrl("https://github.com/dulnikovsky/magicstompfrenzy/blob/master/README.md"));
            }
            );

    mainlyt->addWidget(helpLabel,1,1);

    QPushButton *closeButton = new QPushButton(tr("Close"));
    connect( closeButton, SIGNAL(clicked()), this, SLOT(accept()));
    mainlyt->addWidget(closeButton, 2,1);

    setLayout(mainlyt);
}
