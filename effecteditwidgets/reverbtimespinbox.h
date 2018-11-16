#ifndef REVERBTIMESPINBOX_H
#define REVERBTIMESPINBOX_H

#include <QAbstractSpinBox>

class ReverbTimeSpinBox : public QAbstractSpinBox
{
    Q_OBJECT
    Q_PROPERTY(int rawValue READ RawValue WRITE setRawValue NOTIFY rawValueChanged USER true)
public:
    explicit ReverbTimeSpinBox(QWidget *parent = nullptr);

    int RawValue() const { return rawValue; }
    virtual void setRawValue( int val);

    void setParameters(int minRawVal = 0, int maxRawVal = 0x7F);
    void stepBy(int steps) override;

    void setSuffix(const QString &str) { suffix = str; }
    QString Suffix() const { return suffix;}
Q_SIGNALS:
    void rawValueChanged(int);

protected:
    StepEnabled stepEnabled() const override;

private:
    QString suffix;
    int minRawVal;
    int maxRawVal;
    int rawValue;
};

#endif // REVERBTIMESPINBOX_H
