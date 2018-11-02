#ifndef DELAYBANDWIDGET_H
#define DELAYBANDWIDGET_H

#include "effecteditbasewidget.h"

class QGridLayout;

class DelayBandWidget : public EffectEditBaseWidget
{
    Q_OBJECT
public:
    explicit DelayBandWidget( int offset, QWidget *parent = nullptr);
};

#endif // DELAYBANDWIDGET_H
