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
#include "progresswidget.h"

#include <QProgressBar>
#include <QPushButton>
#include <QHBoxLayout>

ProgressWidget::ProgressWidget(QWidget *parent)
    : QWidget(parent)
{
    QHBoxLayout *lyt = new QHBoxLayout();
    progressBar = new QProgressBar();
    cancelButton = new QPushButton(tr("Cancel"));
    connect(cancelButton, SIGNAL(pressed()), this, SIGNAL(cancel()));
    lyt->addWidget(progressBar);
    lyt->addWidget(cancelButton);
    setLayout(lyt);
}

void ProgressWidget::setFormat(const QString &format)
{
    progressBar->setFormat(format);
}

void ProgressWidget::setRange(int minimum, int maximum)
{
    progressBar->setRange( minimum, maximum);
}

void ProgressWidget::setValue( int val)
{
    progressBar->setValue( val);
}
