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

        EffectLevel = 0x10, //Two bytes
        DirectLevel = 0x12, //Two bytes
        DirectPan = 0x14, //Two bytes
        WaveForm = 0x16,
        LowCutFilter1 = 0x1E
    };
    static const int BandLenght = 11;

    explicit MultibandDelayWidget( EffectTypeId id, QWidget *parent = nullptr);
};

#endif // NOISEGATEWIDGET_H
