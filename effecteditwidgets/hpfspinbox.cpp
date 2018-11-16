#include "hpfspinbox.h"

HpfSpinBox::HpfSpinBox(QWidget *parent )
    : FreqSpinBox( parent)
{

}

void HpfSpinBox::setRawValue(int val)
{
    setParametersForVal(val);
    FreqSpinBox::setRawValue(val);
}

void HpfSpinBox::stepBy(int val)
{
    setParametersForVal(RawValue()+val);
    FreqSpinBox::stepBy(val);
}

HpfSpinBox::StepEnabled HpfSpinBox::stepEnabled() const
{
    if( RawValue() == 0x1C || RawValue() == 0x1D )
    {
        StepEnabled enabled = QAbstractSpinBox::StepNone;
        enabled |= QAbstractSpinBox::StepUpEnabled;
        enabled |= QAbstractSpinBox::StepDownEnabled;
        return enabled;
    }
    else
        return FreqSpinBox::stepEnabled();
}

QString HpfSpinBox::convertToString() const
{
    if(RawValue() == 0x00)
        return "Thru";
    return FreqSpinBox::convertToString();
}

void HpfSpinBox::setParametersForVal(int val)
{
    if( val < 0x1D)
        setParameters( 20.0, 100.0, 0, 0x1C);
    else
        setParameters( 106.0, 8000.0, 0x1D, 0x68);
}
