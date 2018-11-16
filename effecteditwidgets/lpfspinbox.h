#ifndef LPFPINBOX_H
#define LPFPINBOX_H

#include "freqspinbox.h"

class LpfSpinBox : public FreqSpinBox
{
    Q_OBJECT
public:
    explicit LpfSpinBox(QWidget *parent = nullptr);

    void setRawValue(int val) override;

    void stepBy(int val) override;

protected:
    StepEnabled stepEnabled() const override;
    QString convertToString() const override;

private:
    void setParametersForVal(int val);
};

#endif // LPFPINBOX_H
