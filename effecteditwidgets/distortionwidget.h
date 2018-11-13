#ifndef DISTORTIONWIDGET_H
#define DISTORTIONWIDGET_H

#include "effecteditbasewidget.h"

class DistortionWidget: public EffectEditBaseWidget
{
    Q_OBJECT
public:
    explicit DistortionWidget(QWidget *parent = nullptr);

    enum ParameterOffsets
    {
        EQ1Freq = 0x00, // 2 bytes
        PreEQLevel = 0x02, // 2 bytes

        Gain = 0x10, // 2 bytes
        Master = 0x12, // 2 bytes
        Tone = 0x14, // 2 bytes
        DistortionType = 0x16,

        EQ1Gain = 0x1E,
        EQ1Q = 0x1F,

        EQ2Freq = 0x20,
        EQ2Gain = 0x21,
        EQ2Q = 0x22,

        EQ3Freq = 0x23,
        EQ3Gain = 0x24,
        EQ3Q = 0x25,

        EQ4Freq = 0x26,
        EQ4Gain = 0x27,
        EQ4Q = 0x28,

        PreEQ1Freq = 0x2B,
        PreEQ1Gain = 0x2C,
        PreEQ1Q = 0x2D,

        PreEQ2Freq = 0x2E,
        PreEQ2Gain = 0x2F,
        PreEQ2Q = 0x30,

        PreEQ3Freq = 0x31,
        PreEQ3Gain = 0x32,
        PreEQ3Q = 0x33,

        NoiseGateThreshold = 0x35,
        NoiseGateAttack = 0x36,
        NoiseGateHold = 0x37,
        NoiseGateDecay = 0x38,

        NoiseGateThresholdMulti = 0x3B,
        NoiseGateAttackMulti = 0x3C,
        NoiseGateHoldMulti = 0x3D,
        NoiseGateDecayMulti = 0x3E
    };

};

#endif // DISTORTIONWIDGET_H
