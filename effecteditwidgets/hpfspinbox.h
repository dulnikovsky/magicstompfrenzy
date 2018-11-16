#ifndef HPFPINBOX_H
#define HPFPINBOX_H

#include "freqspinbox.h"

class HpfSpinBox : public FreqSpinBox
{
    Q_OBJECT
public:
    explicit HpfSpinBox(QWidget *parent = nullptr);

    void setRawValue(int val) override;

    void stepBy(int val) override;

protected:
    StepEnabled stepEnabled() const override;
    QString convertToString() const override;

private:
    void setParametersForVal(int val);
};

#endif // HPFPINBOX_H
