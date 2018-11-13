#ifndef AMPMULTIWIDGET_H
#define AMPMULTIWIDGET_H

#include "effecteditbasewidget.h"

class AmpMultiWidget : public EffectEditBaseWidget
{
    Q_OBJECT
public:
    enum EffectParameterOffsets
    {
        CompressorThreshold = 0x04, // 2 bytes
        ChorusFlangerDelay = 0x06, // 2 bytes
        DelayFeedback = 0x08, // 2 bytes

        ReverbIniDelay = 0x0A, // 2 bytes

        AmpType = 0x16,
        SpeakerSimulator = 0x17,
        Gain = 0x1E,
        Master = 0x1F,
        Tone = 0x22,
        Treble = 0x24,
        HighMiddle = 0x25,
        LowMiddle = 0x26,
        Bass = 0x27,
        Presence = 0x28,
        NoiseGateThreshold = 0x2A,
        NoiseGateAttack = 0x2B,
        NoiseGateHold = 0x2C,
        NoiseGateDecay = 0x2D,

        CompressorRatio = 0x34,
        CompressorAttack = 0x35,
        CompressorRelease = 0x36,
        CompressorKnee = 0x37,
        CompressorGain = 0x38,

        ModWave = 0x19,
        ModSpeed = 0x3F,
        ModDepth = 0x40,
        ChorusLevel = 0x41,
        ModFeedback = 0x41, //!!! Yes, that's right
        FlangePhaserLevel = 0x42,

        DelayTapL = 0x4A,
        DelayTapR = 0x4B,
        DelayFeedbackGain = 0x4C,
        DelayHeigh = 0x4D,
        DelayLevel = 0x4E,

        DelayHPF = 0x52,
        DelayLPF = 0x53,

        ReverbTime = 0x55,
        ReverbHigh = 0x56,
        ReverbDiffusion = 0x57,
        ReverbDensity = 0x58,
        ReverbLevel = 0x59
    };

    enum AmpMultiSubtype
    {
        AmpSimulatorOnly,
        DistortionOnly,
        AmpChorus,
        AmpFlange,
        AmpTremolo,
        AmpPhaser,
        DistortionChorus,
        DistortionFlange,
        DistortionTremolo,
        DistortionPhaser
    };

    explicit AmpMultiWidget(AmpMultiSubtype subtype , QWidget *parent = nullptr);
};

#endif // AMPMULTIWIDGET_H
