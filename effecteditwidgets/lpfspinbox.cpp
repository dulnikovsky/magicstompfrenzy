#include "lpfspinbox.h"

LpfSpinBox::LpfSpinBox(QWidget *parent )
    : FreqSpinBox( parent)
{

}

void LpfSpinBox::setRawValue(int val)
{
    setParametersForVal(val);
    FreqSpinBox::setRawValue(val);
}

void LpfSpinBox::stepBy(int steps)
{
    int newval = RawValue() + steps;
    setRawValue( newval);
}

LpfSpinBox::StepEnabled LpfSpinBox::stepEnabled() const
{
    StepEnabled enabled = QAbstractSpinBox::StepNone;
    if( RawValue() == 0x0C || RawValue() == 0x0D || RawValue() == 0x64)
    {
        enabled |= QAbstractSpinBox::StepUpEnabled;
        enabled |= QAbstractSpinBox::StepDownEnabled;
        return enabled;
    }
    else if(RawValue() == 0x65)
    {
        enabled |= QAbstractSpinBox::StepDownEnabled;
        return enabled;
    }
    else
        return FreqSpinBox::stepEnabled();
}

QString LpfSpinBox::convertToString() const
{
    if(RawValue() == 0x65)
        return "Thru";
    return FreqSpinBox::convertToString();
}

void LpfSpinBox::setParametersForVal(int val)
{
    if( val < 0x0D)
        setParameters( 50.0, 100.0, 0, 0x0C);
    else
        setParameters( 106.0, 16000.0, 0x0D, 0x64);
}
