#ifndef FREQSPINBOX_H
#define FREQSPINBOX_H

#include "expspinbox.h"

class FreqSpinBox : public ExpSpinBox
{
    Q_OBJECT
public:
    explicit FreqSpinBox(QWidget *parent = nullptr);
    virtual QString convertToString() const override;
};

#endif // FREQSPINBOX_H
