#include "bassfreqspinbox.h"

BassFreqSpinBox::BassFreqSpinBox(QWidget *parent )
    : FreqSpinBox( parent)
{

}

void BassFreqSpinBox::setRawValue(int val)
{
    setParametersForVal(val);
    FreqSpinBox::setRawValue(val);
}

void BassFreqSpinBox::stepBy(int val)
{
    setParametersForVal(RawValue()+val);
    FreqSpinBox::stepBy(val);
}

BassFreqSpinBox::StepEnabled BassFreqSpinBox::stepEnabled() const
{
    if( RawValue() == 0x4A || RawValue() == 0x49 )
    {
        StepEnabled enabled = QAbstractSpinBox::StepNone;
        enabled |= QAbstractSpinBox::StepUpEnabled;
        enabled |= QAbstractSpinBox::StepDownEnabled;
        return enabled;
    }
    else
        return FreqSpinBox::stepEnabled();
}

void BassFreqSpinBox::setParametersForVal(int val)
{
    if( val < 0x4A)
        setParameters( 20.0, 100.0, 0, 0x49);
    else
        setParameters( 100.0, 320.0, 0x4A, 0x7F);
}
