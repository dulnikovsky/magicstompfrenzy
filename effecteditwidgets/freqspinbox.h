#ifndef FREQSPINBOX_H
#define FREQSPINBOX_H

#include <QAbstractSpinBox>

class FreqSpinBox : public QAbstractSpinBox
{
    Q_OBJECT
    Q_PROPERTY(int rawValue READ RawValue WRITE setRawValue NOTIFY rawValueChanged USER true)
public:
    explicit FreqSpinBox(QWidget *parent = nullptr);

    int RawValue() const { return rawValue; }
    virtual void setRawValue( int val);

    void setParameters(double minFreq, double maxFreq, int minRawVal = 0, int maxRawVal = 0x7F);

    void stepBy(int steps) override;
Q_SIGNALS:
    void rawValueChanged(int);

protected:
    StepEnabled stepEnabled() const override;

private:
    double minFreq;
    double maxFreq;
    int minRawVal;
    int maxRawVal;
    int rawValue;
};

#endif // FREQSPINBOX_H
