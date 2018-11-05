#ifndef DELAYBANDWIDGET_H
#define DELAYBANDWIDGET_H

#include "effecteditbasewidget.h"

class QGridLayout;

class DelayBandWidget : public EffectEditBaseWidget
{
    Q_OBJECT
public:
    explicit DelayBandWidget( int offset, double minTime, double maxTime, bool tapOnly = true, QWidget *parent = nullptr);

private:
    static QDoubleSpinBox * createTimeSpinBox(int offset, double minTime, double maxTime);
};

#endif // DELAYBANDWIDGET_H
