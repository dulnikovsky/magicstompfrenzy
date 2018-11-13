#ifndef EXPSPINBOX_H
#define EXPSPINBOX_H

#include <QAbstractSpinBox>

class ExpSpinBox : public QAbstractSpinBox
{
    Q_OBJECT
    Q_PROPERTY(int rawValue READ RawValue WRITE setRawValue NOTIFY rawValueChanged USER true)
public:
    explicit ExpSpinBox(QWidget *parent = nullptr);

    int RawValue() const { return rawValue; }
    virtual void setRawValue( int val);

    double RealValue() const { return realValue; }
    void setParameters(double minRealVal, double maxRealVal, int minRawVal = 0, int maxRawVal = 0x7F);
    void stepBy(int steps) override;

    void setSuffix(const QString &str) { suffix = str; }
    QString Suffix() const { return suffix;}
Q_SIGNALS:
    void rawValueChanged(int);

protected:
    virtual QString convertToString() const;
    StepEnabled stepEnabled() const override;

private:
    QString suffix;
    double realValue;
    double minRealVal;
    double maxRealVal;
    int minRawVal;
    int maxRawVal;
    int rawValue;
};

#endif // EXPSPINBOX_H
