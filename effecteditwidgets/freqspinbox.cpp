#include "freqspinbox.h"
#include <QtMath>
#include <QLineEdit>

FreqSpinBox::FreqSpinBox(QWidget *parent) :
    QAbstractSpinBox(parent), minFreq(20.0), maxFreq(20000.0), minRawVal(0), maxRawVal(0x7F), rawValue(minRawVal)
{

}

void FreqSpinBox::setParameters(double minF, double maxF, int minR , int maxR)
{
    minFreq = minF;
    maxFreq = maxF;
    minRawVal = minR;
    maxRawVal = maxR;
    update();
}

void FreqSpinBox::setRawValue( int val)
{
    double maxExponent = qLn(maxFreq) / qLn(minFreq);
    double exponentStep = ((maxExponent-1) / ( maxRawVal - minRawVal ));
    double result = qPow(minFreq, (1 + (exponentStep * (val - minRawVal))));

    QString txt;
    if( result < 100.0)
        txt = QString::number( result, 'f', 1 ) + QStringLiteral(" Hz");
    else if( result < 1000.0)
        txt = QString::number( result, 'f', 0 ) + QStringLiteral(" Hz");
    else
        txt = QString::number( result/1000, 'f', 2 ) + QStringLiteral(" kHz");

    lineEdit()->setText( txt );

    rawValue = val;
    emit rawValueChanged( rawValue);
}

void FreqSpinBox::stepBy(int steps)
{
    int newval = rawValue + steps;
    if( newval >= minRawVal && newval <= maxRawVal)
        setRawValue( newval);
}

QAbstractSpinBox::StepEnabled FreqSpinBox::stepEnabled() const
{
    StepEnabled enabled = QAbstractSpinBox::StepNone;

    if( rawValue >= minRawVal && rawValue < maxRawVal)
        enabled |= QAbstractSpinBox::StepUpEnabled;

    if( rawValue <= maxRawVal && rawValue > minRawVal)
        enabled |= QAbstractSpinBox::StepDownEnabled;

    return enabled;
}
