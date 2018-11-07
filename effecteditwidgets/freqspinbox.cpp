#include "freqspinbox.h"
#include <QtMath>
#include <QLineEdit>

FreqSpinBox::FreqSpinBox(QWidget *parent) :
    ExpSpinBox(parent)
{

}

QString FreqSpinBox::convertToString() const
{
    QString txt;
    double val = RealValue();
    if( val < 100.0)
        txt = QString::number( val, 'f', 1 ) + QStringLiteral(" Hz");
    else if( val < 1000.0)
        txt = QString::number( val, 'f', 0 ) + QStringLiteral(" Hz");
    else
        txt = QString::number( val/1000, 'f', 2 ) + QStringLiteral(" kHz");
    return txt;
}
