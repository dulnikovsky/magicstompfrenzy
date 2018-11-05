#ifndef BASSPREAMPWIDGET_H
#define BASSPREAMPWIDGET_H

#include "effecteditbasewidget.h"

class BassPreampWidget : public EffectEditBaseWidget
{
    Q_OBJECT
public:
    enum EffectParameterOffsets
    {
        ParametricEQFreq = 0x02, // 2 bytes

        Gain = 0x10, // 2 bytes
        Master = 0x12, // 2 bytes
        Type = 0x16,
        Bass = 0x1E,
        LowMiddle = 0x1F,
        Middle = 0x20,
        HighMiddle = 0x21,
        Treble = 0x22,

        BassFreq = 0x24,
        LowMidFreq = 0x25,
        MiddleFreq = 0x26,
        HighMidFreq = 0x27,
        TrebleFreq = 0x28,

        ParametricEQQ = 0x29,
        ParametricEQGain = 0x2A,

        Gate = 0x2B,
        SpeakerSimulatorSwitch = 0x2C,
        Limiter = 0x2D,
        Ratio = 0x2E,
        Threshold = 0x2F,
        Attack = 0x30,
        Release = 0x31,
        CompressorGain = 0x32,
        Knee = 0x33
    };
    explicit BassPreampWidget( QWidget *parent = nullptr);
private:

    static QDoubleSpinBox * createStdGainSpinBox(int offset);
};

#endif // BASSPREAMPWIDGET_H
