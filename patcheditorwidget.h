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
#ifndef PATCHEDITORWIDGET_H
#define PATCHEDITORWIDGET_H

#include "arraydataeditwidget.h"

class QVBoxLayout;
class QLabel;
class PatchCommonEditorWidget;

class PatchEditorWidget : public ArrayDataEditWidget
{
    Q_OBJECT
public:
    explicit PatchEditorWidget(QWidget *parent = nullptr);
    void setDataArray(QByteArray *arr) override;

signals:
    void patchTypeEditorChanged(int typeId);

private:
    QVBoxLayout *mainLayout;
    QWidget *effectEditWidget;
    QLabel *copyrightLabel;
    PatchCommonEditorWidget *patchCommonEditorWidget;
    constexpr static const char *copyrightStr="MagicstompFrenzy (C) 2018 - 2021 Robert Vetter";
};

#endif // PATCHCOMMONEDITOR_H
