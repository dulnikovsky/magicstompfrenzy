#include "expspinbox.h"
#include <QtMath>
#include <QLineEdit>

ExpSpinBox::ExpSpinBox(QWidget *parent) :
    QAbstractSpinBox(parent), realValue(0.0), minRealVal(20.0), maxRealVal(20000.0), minRawVal(0), maxRawVal(0x7F), rawValue(minRawVal)
{
    setReadOnly(true); // TODO: Accept input from the QLineEdit of this spinbox
}

void ExpSpinBox::setParameters(double minRVal, double maxRVal, int minR , int maxR)
{
    minRealVal = minRVal;
    maxRealVal = maxRVal;
    minRawVal = minR;
    maxRawVal = maxR;
    update();
}

void ExpSpinBox::setRawValue( int val)
{
    double maxExponent = qLn(maxRealVal) / qLn(minRealVal);
    double exponentStep = ((maxExponent-1) / ( maxRawVal - minRawVal ));
    realValue = qPow(minRealVal, (1 + (exponentStep * (val - minRawVal))));

    lineEdit()->setText(convertToString());

    rawValue = val;
    emit rawValueChanged( rawValue);
}

QString ExpSpinBox::convertToString() const
{
    QString txt;
    double val = RealValue();
    if( val < 1.0)
        txt = QString::number( val, 'f', 3 );
    else if( val < 10.0)
        txt = QString::number( val, 'f', 2 );
    else
        txt = QString::number( val, 'f', 1 );
    return txt + suffix;
}

void ExpSpinBox::stepBy(int steps)
{
    int newval = rawValue + steps;
    if( newval >= minRawVal && newval <= maxRawVal)
        setRawValue( newval);
}

QAbstractSpinBox::StepEnabled ExpSpinBox::stepEnabled() const
{
    StepEnabled enabled = QAbstractSpinBox::StepNone;

    if( rawValue >= minRawVal && rawValue < maxRawVal)
        enabled |= QAbstractSpinBox::StepUpEnabled;

    if( rawValue <= maxRawVal && rawValue > minRawVal)
        enabled |= QAbstractSpinBox::StepDownEnabled;

    return enabled;
}
