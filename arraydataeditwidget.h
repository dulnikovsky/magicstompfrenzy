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
#ifndef ARRAYDATAEDITWIDGET_H
#define ARRAYDATAEDITWIDGET_H

#include <QWidget>

class ArrayDataEditWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ArrayDataEditWidget( QWidget *parent = nullptr);

    QByteArray *DataArray() const { return dataArray; }
    virtual void setDataArray(QByteArray *arr);

    void refreshData(int offset, int length);

    static quint64 sevenToEight( const QByteArray &array, int offset, int length);
    static void eightToSeven( quint64 val, QByteArray &array, int offset, int length);

    constexpr static const char *dataOffsetProperty="offset";
    constexpr static const char *dataLenghtProperty="length";
    constexpr static const char *valuePropertyName="valuePropertyName";
    constexpr static const char *convertMethodProperty="convertMethod";

protected:
    bool event(QEvent *event) override;
    virtual bool writeEditedParameter(QObject *editor);

signals:
    void parameterAboutToBeChanged(int offset, int length, QWidget *editWidget);
    void parameterChanged(int offset, int length, QWidget *editWidget);

private slots:
    void valueChanged();

private:
    QByteArray *dataArray;

    void connectObjectToValueChangedSlot( QObject *widget);

    bool parseConvertMethodString(const QString &sourceStr, QString &methodName, QStringList &srguments);

    QVariant invokeConvertMethod(const QString &method, const QByteArray *data, int offset, int length);

    bool invokeConvertMethodBackwards(const QString &method, const QVariant &value, QByteArray *data, int offset, int length);

    static double scaleAndAdd( double scalingFactor, double augend, double srcValue);
    static double addAndScale( double augend, double scalingFactor, double srcValue);
};

#endif // ARRAYDATAEDITWIDGET_H
