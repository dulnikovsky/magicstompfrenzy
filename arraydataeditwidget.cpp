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
#include "arraydataeditwidget.h"

#include <QKeyEvent>
#include <QMetaProperty>
#include <QAbstractButton>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QComboBox>
#include <QLineEdit>
#include <QChildEvent>
#include "effecteditwidgets/expspinbox.h"
#include "effecteditwidgets/reverbtimespinbox.h"
#include "effecteditwidgets/renardseriesspinbox.h"

ArrayDataEditWidget::ArrayDataEditWidget( QWidget *parent)
        : QWidget( parent), dataArray(nullptr)
{
    setEnabled(false);
}

void ArrayDataEditWidget::setDataArray(QByteArray *arr)
{
    if( arr == nullptr)
        return;
    dataArray = arr;
    refreshData( 0, dataArray->length());
    setEnabled(true);
}

bool ArrayDataEditWidget::event(QEvent *event)
{
    QChildEvent *childev = dynamic_cast<QChildEvent *>(event);
    if(childev == nullptr )
        return QWidget::event(event);

    if(childev->type() != QEvent::ChildAdded )
        return QWidget::event(event);

    QObject *child = childev->child();
    connectObjectToValueChangedSlot( child);
    QList<QWidget *> objectList = child->findChildren<QWidget *>();
    for(int i=0; i < objectList.size(); i++)
        connectObjectToValueChangedSlot( objectList.at(i));

    return QWidget::event(event);
}


void ArrayDataEditWidget::valueChanged()
{
    writeEditedParameter(sender());
}

void ArrayDataEditWidget::refreshData(int offset, int length)
{
    if(dataArray==nullptr)
        return;

    QList<QWidget *> widgetList = this->findChildren<QWidget *>();
    for(int i=0; i< widgetList.size(); i++)
    {
        QWidget *widget = widgetList.at(i);

        unsigned int paramLength = widget->property(dataLenghtProperty).toUInt();
        if( paramLength == 0)
            continue;

        bool ok;
        unsigned int paramOffset = widget->property(dataOffsetProperty).toUInt( &ok);
        if( !ok)
            continue;

        // Loop thru parent widgets as they can contain offset as well
        QWidget *parent = widget->parentWidget();
        while( parent != nullptr)
        {
            QVariant paramOffsetVariant = parent->property(dataOffsetProperty);
            if( paramOffsetVariant.isValid())
                paramOffset += paramOffsetVariant.toUInt();
            parent = parent->parentWidget();
        }

        //TODO Optimize and refresh only affected edit widgets
//        if( intParamOffset < offset || offset > intParamOffset+intParamLength)
//            return;

//        if(offset+length > intParamOffset+intParamLength)
//            return;

        widget->blockSignals(true);

        QByteArray valPropNameArr;
        QVariant valPropName = widget->property(valuePropertyName);
        if( !valPropName.isValid())
            valPropNameArr=widget->metaObject()->userProperty().name();
        else
            valPropNameArr=valPropName.toByteArray();

        if (! valPropNameArr.isEmpty())
        {
            QVariant val;
            QVariant convertMethod = widget->property(convertMethodProperty);
            if(convertMethod.isValid())
            {
                val = invokeConvertMethod(convertMethod.toString(), dataArray, paramOffset, paramLength);
            }
            else
            {
                if( paramLength == 1)
                    val = dataArray->at(paramOffset);
                else
                    val = dataArray->mid(paramOffset, paramLength);
            }
            bool ret;
            if(val.isValid())
            {
                ret = widget->setProperty(valPropNameArr, val);
                if(! ret )
                    ret = widget->setProperty(valPropNameArr, sevenToEight( *dataArray, paramOffset, paramLength));
                if(! ret )
                    qDebug("Property NOT set!!!!");
            }
        }
        widget->blockSignals(false);
    }
}

bool ArrayDataEditWidget::writeEditedParameter(QObject *editor)
{
    if(dataArray==nullptr)
        return false;

    QByteArray valPropNameArr;
    QVariant valPropName = editor->property(valuePropertyName);
    if( !valPropName.isValid())
        valPropNameArr=editor->metaObject()->userProperty().name();
    else
        valPropNameArr=valPropName.toByteArray();

    if (! valPropNameArr.isEmpty())
    {
        QVariant paramLength;
        paramLength=editor->property(dataLenghtProperty);
        if(! paramLength.isValid())
            return false;

        int intParamLenght = paramLength.toInt();

        int intParamOffset=0;
        QVariant paramOffset = editor->property(dataOffsetProperty);
        if(paramOffset.isValid())
            intParamOffset += paramOffset.toInt();

        QObject *parent = editor->parent();
        while( parent != this && parent != nullptr)
        {
            QVariant paramOffset = parent->property(dataOffsetProperty);
            if(paramOffset.isValid())
                intParamOffset += paramOffset.toInt();
            parent=parent->parent();
        }

        {
            QVariant newVal = editor->property(valPropNameArr);
            if(newVal.isValid())
            {
               emit parameterAboutToBeChanged(intParamOffset, intParamLenght, dynamic_cast<QWidget *>(editor));
               QVariant convertMethod = editor->property(convertMethodProperty);
               if(convertMethod.isValid())
               {
                   invokeConvertMethodBackwards(convertMethod.toString(), newVal, dataArray, intParamOffset, intParamLenght);
               }
               else
               {
                   if( dynamic_cast<QLineEdit *>(editor))
                   {
                       QString theString = newVal.toString();
                       if(theString.length() <= intParamLenght)
                           theString.resize(intParamLenght, ' ');
                       else
                          theString.truncate(intParamLenght-1);

                       QByteArray arr = theString.toLocal8Bit();
                       dataArray->replace(intParamOffset, intParamLenght, arr);
                   }
                   else
                   {
                       eightToSeven(newVal.toInt(), *dataArray, intParamOffset, intParamLenght);
                   }
               }
               emit parameterChanged(intParamOffset, intParamLenght, dynamic_cast<QWidget *>(editor));
               return true;
            }
        }
    }
    return false;
}

void ArrayDataEditWidget::connectObjectToValueChangedSlot( QObject *object)
{
    QVariant offset, length;
    offset = object->property(dataOffsetProperty);
    length = object->property(dataLenghtProperty);

    if(!(offset.isValid() && length.isValid()))
        return;

    QSpinBox *sbox = dynamic_cast<QSpinBox *>(object);
    if( sbox != nullptr)
    {
        connect(sbox, SIGNAL(valueChanged(int)), this, SLOT(valueChanged()));
        return;
    }
    QDoubleSpinBox *dbox = dynamic_cast<QDoubleSpinBox*>(object);
    if( dbox != nullptr)
    {
        connect(dbox, SIGNAL(valueChanged(double)), this, SLOT(valueChanged()));
        return;
    }
    QComboBox *cbox = dynamic_cast<QComboBox *>(object);
    if( cbox != nullptr)
    {
        connect(cbox, SIGNAL(currentIndexChanged(int)), this, SLOT(valueChanged()));
        return;
    }
    QAbstractButton *button = dynamic_cast<QAbstractButton *>(object);
    if( button != nullptr)
    {
        connect(button, SIGNAL(toggled(bool)), this, SLOT(valueChanged()));
        return;
    }
    QLineEdit *lineedit = dynamic_cast<QLineEdit *>(object);
    if( lineedit != nullptr)
    {
        connect(lineedit, SIGNAL(textEdited(QString)), this, SLOT(valueChanged()));
        return;
    }
    ExpSpinBox *exbox = dynamic_cast<ExpSpinBox *>(object);
    if( exbox != nullptr)
    {
        connect(exbox, SIGNAL(rawValueChanged(int)), this, SLOT(valueChanged()));
        return;
    }
    ReverbTimeSpinBox *revtimebox = dynamic_cast<ReverbTimeSpinBox *>(object);
    if( revtimebox != nullptr)
    {
        connect(revtimebox, SIGNAL(rawValueChanged(int)), this, SLOT(valueChanged()));
        return;
    }
    RenardSeriesSpinBox *rsbox = dynamic_cast<RenardSeriesSpinBox *>(object);
    if( rsbox != nullptr)
    {
        connect(rsbox, SIGNAL(rawValueChanged(int)), this, SLOT(valueChanged()));
        return;
    }
}

QVariant ArrayDataEditWidget::invokeConvertMethod(const QString &method, const QByteArray *data, int offset, int length)
{
    QVariant valVariant;

    QString methodName;
    QStringList argList;
    if(parseConvertMethodString(method, methodName, argList)==false)
        return valVariant;

    if(methodName==QStringLiteral("scaleAndAdd"))
    {
        Q_ASSERT(argList.size()==2);

        quint64 val = sevenToEight(*data, offset, length);
        return scaleAndAdd(argList.at(0).toDouble(), argList.at(1).toDouble(), val);
    }
    if(methodName==QStringLiteral("invertedBool"))
    {
        Q_ASSERT(length==1);
        bool val = data->at(offset) & 0x01;
        return !val;
    }

    return valVariant;
}

bool ArrayDataEditWidget::invokeConvertMethodBackwards(const QString &method, const QVariant &value, QByteArray *data, int offset, int length)
{
    QString methodName;
    QStringList argList;
    if(parseConvertMethodString(method, methodName, argList)==false)
        return false;

    if(methodName==QStringLiteral("scaleAndAdd"))
    {
        Q_ASSERT(argList.size()==2);

        double valReal = value.toDouble();
        valReal = addAndScale( -(argList.at(1).toDouble()), 1.0 / argList.at(0).toDouble(), valReal);
        eightToSeven(valReal , *data, offset, length );
        return true;
    }
    if(methodName==QStringLiteral("invertedBool"))
    {
        Q_ASSERT(length==1);
        uint8_t valInt = ! value.toBool();
        eightToSeven(valInt, *data, offset, length );
        return true;
    }

    return true;
}

bool ArrayDataEditWidget::parseConvertMethodString(const QString &sourceStr, QString &methodName, QStringList &srguments)
{
    int openBracketIndex = sourceStr.indexOf('(');
    int closeBracketIndex = -1;
    if(openBracketIndex > 0)
    {
        closeBracketIndex=sourceStr.indexOf(')');
    }

    if(openBracketIndex == -1 || closeBracketIndex == -1 || closeBracketIndex < openBracketIndex)
        return false;

    methodName=sourceStr.left(openBracketIndex);
    srguments = sourceStr.mid(openBracketIndex+1, closeBracketIndex - (openBracketIndex+1)).split(',');

    return true;
}

double ArrayDataEditWidget::scaleAndAdd( double scalingFactor, double augend, double srcValue)
{
    return (scalingFactor*srcValue)+augend;
}

double ArrayDataEditWidget::addAndScale( double augend, double scalingFactor, double srcValue)
{
    return scalingFactor*(srcValue+augend);
}

quint64 ArrayDataEditWidget::sevenToEight( const QByteArray &array, int offset, int length)
{
    Q_ASSERT(length <= 8);
    Q_ASSERT(offset+length <= array.size());

    quint64 res=0;
    for(int i=offset+(length-1), c=0; i>=offset; i--, c++)
    {
        res |= (static_cast<unsigned int>(array.at(i) & 0x7F)) << 7*c;
    }
    return res;
}

void ArrayDataEditWidget::eightToSeven( quint64 val, QByteArray &destArray, int offset, int length)
{
    Q_ASSERT(length <= 8);
    Q_ASSERT(offset+length <= destArray.size());

    for(int i=offset, s=length-1; i<offset+length; i++, s--)
    {
        destArray[i] = (val >> (s*8-s)) &0x7F;
    }
}
