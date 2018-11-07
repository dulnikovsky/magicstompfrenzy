#ifndef BASSFREQSPINBOX_H
#define BASSFREQSPINBOX_H

#include "freqspinbox.h"

class BassFreqSpinBox : public FreqSpinBox
{
    Q_OBJECT
public:
    explicit BassFreqSpinBox(QWidget *parent = nullptr);

    void setRawValue(int val) override;

    void stepBy(int val) override;

protected:
    StepEnabled stepEnabled() const override;

private:
    void setParametersForVal(int val);
};

#endif // BASSFREQSPINBOX_H
