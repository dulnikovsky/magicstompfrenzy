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
#ifndef EXPSPINBOX_H
#define EXPSPINBOX_H

#include <QAbstractSpinBox>

class ExpSpinBox : public QAbstractSpinBox
{
    Q_OBJECT
    Q_PROPERTY(int rawValue READ RawValue WRITE setRawValue NOTIFY rawValueChanged USER true)
public:
    explicit ExpSpinBox(QWidget *parent = nullptr);

    int RawValue() const { return rawValue; }
    virtual void setRawValue( int val);

    double RealValue() const { return realValue; }
    void setParameters(double minRealVal, double maxRealVal, int minRawVal = 0, int maxRawVal = 0x7F);
    void stepBy(int steps) override;

    void setSuffix(const QString &str) { suffix = str; }
    QString Suffix() const { return suffix;}
Q_SIGNALS:
    void rawValueChanged(int);

protected:
    virtual QString convertToString() const;
    StepEnabled stepEnabled() const override;

private:
    QString suffix;
    double realValue;
    double minRealVal;
    double maxRealVal;
    int minRawVal;
    int maxRawVal;
    int rawValue;
};

#endif // EXPSPINBOX_H
