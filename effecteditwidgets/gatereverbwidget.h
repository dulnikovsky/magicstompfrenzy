#ifndef GATEREVERBWIDGET_H
#define GATEREVERBWIDGET_H

#include "effecteditbasewidget.h"

class GateReverbWidget: public EffectEditBaseWidget
{
    Q_OBJECT
public:
    explicit GateReverbWidget(bool isEarlyRefReverb = false, QWidget *parent = nullptr);

    enum ParameterOffsets
    {
        InitDelay = 0x10, // 2 Bytes
        FBGain = 0x12, // 2 Bytes
        RoomSize = 0x14, // 2 Bytes
        Type = 0x16,

        Liveness = 0x1F,
        Diffusion = 0x20,
        Density = 0x21,
        ERNUmber = 0x22,
        HighRatio = 0x25,
        HPF = 0x26,
        LPF = 0x27,

        Mix = 0x28
    };
};

#endif // GATEREVERBWIDGET_H
