#ifndef MULTIBANDDELAYWIDGET_H
#define MULTIBANDDELAYWIDGET_H

#include "effecteditbasewidget.h"

class MultibandDelayWidget : public EffectEditBaseWidget
{
    Q_OBJECT
public:

    enum parameterOffsets
    {
        DelayTime1 = 0x00,
        DelayTime2 = 0x02,
        DelayTime3 = 0x04,
        DelayTime4 = 0x06,
        DelayTime5 = 0x08,
        DelayTime6 = 0x0A,
        DelayTime7 = 0x0C,
        DelayTime8 = 0x0E,

        LowCutFilter1 = 0x1E
    };
    static const int BandLenght = 11;

    explicit MultibandDelayWidget( EffectTypeId id, QWidget *parent = nullptr);

    static QDoubleSpinBox * createTimeSpinBox(int offset, double minTime, double maxTime);
};

#endif // NOISEGATEWIDGET_H
