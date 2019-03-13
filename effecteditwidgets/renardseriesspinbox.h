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
#ifndef RENARDSERIESBOX_H
#define RENARDSERIESBOX_H

#include <QAbstractSpinBox>

class RenardSeriesSpinBox : public QAbstractSpinBox
{
    Q_OBJECT
    Q_PROPERTY(int rawValue READ RawValue WRITE setRawValue NOTIFY rawValueChanged USER true)
public:
    explicit RenardSeriesSpinBox(QWidget *parent = nullptr);

    int RawValue() const { return rawValue; }
    virtual void setRawValue( int val);

    int RawOffsetValue() const { return rawOffset; }
    void setRawOffsetValue( int val) { rawOffset = val; }

    void setParameters(int divideSteps = 40, int minRawVal = 0, int maxRawVal = 0x7F);
    void stepBy(int steps) override;

    void setSuffix(const QString &str) { suffix = str; }
    QString Suffix() const { return suffix;}
Q_SIGNALS:
    void rawValueChanged(int);

protected:
    virtual QString convertToString() const;
    StepEnabled stepEnabled() const override;

private:
    int divideSteps;
    int minRawVal;
    int maxRawVal;
    int rawValue;
    int rawOffset;
    QString suffix;
};

#endif // RENARDSERIESBOX_H
