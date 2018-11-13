#ifndef ACOUSTICMULTIWIDGET_H
#define ACOUSTICMULTIWIDGET_H

#include "effecteditbasewidget.h"

class AcousticMultiWidget: public EffectEditBaseWidget
{
    Q_OBJECT
public:
    explicit AcousticMultiWidget(QWidget *parent = nullptr);

    enum ParameterOffsets
    {
        MicType = 0x16,

        Blend = 0x1E,
        Bass = 0x1F,
        Middle = 0x20,
        Treble = 0x21,
        Presence = 0x22,

        Volume = 0x23,
        Stereo = 0x24,
        BassFreq = 0x25,
        MiddleFreq = 0x26,
        TrebleFreq = 0x27,
        PresenceFreq = 0x28,
        Limiter = 0x29,
        ChorusDelayType = 0x2B,
        ReverbType = 0x2D,
        LimiterLevel = 0x2F,

        SpeedTime = 0x30,
        DepthFeedback = 0x31,
        EffectLevel = 0x32,
        ReverbLevel = 0x33

    };
private:

};

#endif // ACOUSTICMULTIWIDGET_H
