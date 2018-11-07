#ifndef HQPITCHWIDGET_H
#define HQPITCHWIDGET_H

#include "effecteditbasewidget.h"

class HQPitchWidget: public EffectEditBaseWidget
{
    Q_OBJECT
public:
    explicit HQPitchWidget(QWidget *parent = nullptr);

    enum ParameterOffsets
    {
        Delay =0x10, // 2Bytes
        FBGain =0x12, // 2Bytes
        Mode = 0x16,
        Pitch = 0x1E,
        Fine = 0x1F,

        Mix = 0x28
    };
};

#endif // HQPITCHWIDGET_H
