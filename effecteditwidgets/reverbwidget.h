#ifndef REVERBWIDGET_H
#define REVERBWIDGET_H

#include "effecteditbasewidget.h"

class ReverbWidget: public EffectEditBaseWidget
{
    Q_OBJECT
public:
    explicit ReverbWidget(QWidget *parent = nullptr);

    enum ParameterOffsets
    {
        HighRatio = 0x00, // 2 Bytes
        InitDelay = 0x10, // 2 Bytes
        ERRevDelay = 0x12, // 2 Bytes
        Time = 0x14, // 2 Bytes
        Type = 0x16,

        LowRatio = 0x1E,
        Diffusion = 0x1F,
        Density = 0x20,
        ERRevBalance = 0x21,
        HPF = 0x22,
        LPF = 0x23,
        GateLevel = 0x24,
        GateAttack = 0x25,
        GateHold = 0x26,
        GateDecay = 0x27,
        Mix = 0x28
    };
};

#endif // REVERBWIDGET_H
