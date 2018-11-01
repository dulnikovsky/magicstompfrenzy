#ifndef MAGICSTOMP_H
#define MAGICSTOMP_H

const int numOfPatches = 99;
static const int PatchNameLength = 12;

enum MagistompPatchDesc
{
    PatchType,
    Control1 = 2,
    Control2 = 4,
    Control3 = 6,
    PatchName = 16,
    PatchNameLast = PatchName + PatchNameLength,
    PatchCommonLength = 0x20,
    PatchEffectLength = 0x7F,
    PatchTotalLength = PatchCommonLength + PatchEffectLength
};

enum EffectTypeIds
{
    AcousticMulti = 0x00,
    EightBandParallelDelay = 0x01,
    EightBandSeriesDelay = 0x02,
    FourBand2TapModDelay = 0x03,
    TwoBand4TapModDelay = 0x04,
    EightMultiTapModDelay = 0x05,
    TwoBandLong4ShortModDelay = 0x06,
    ShortMediumLongModDelay = 0x07,
    AmpSimulator = 0x08,
    Reverb = 0x09,
    EarlyRef = 0x0A,
    GateReverb = 0x0B,
    ReverseGate = 0x0C,
    MonoDelay = 0x0D,
    StereoDelay = 0x0E,
    ModDelay = 0x0F,
    DelayLCR = 0x10,
    Echo = 0x11,
    Chorus = 0x12,
    Flange = 0x13,
    Symphonic = 0x14,
    Phaser = 0x15,
    AutoPan = 0x16,
    Tremolo = 0x17,
    HQPitch = 0x18,
    DualPitch = 0x19,
    Rotary = 0x1A,
    RingMod = 0x1B,
    ModFilter = 0x1C,
    DigitalDistortion = 0x1D,
    DynaFilter = 0x1E,
    DynaFlange = 0x1F,
    DynaPhaser = 0x20,
    ReverbChorusParallel = 0x21,
    ReverbChorusSerial = 0x22,
    ReverbFlangeParallel = 0x23,
    ReverbFlangeSerial = 0x24,
    ReverbSymphonicParallel = 0x25,
    ReverbSymphonicSerial = 0x26,
    ReverbPan = 0x27,
    DelayEarlyRefParallel = 0x28,
    DelayEarlyRefSerial = 0x29,
    DelayReverbParallel = 0x2A,
    DelayReverbSerial = 0x2B,
    DistortionDelay = 0x2C,
    MultiFilter = 0x2D,
    MBandDyna = 0x2E,
    Distortion = 0x2F,
    VintageFlange = 0x30,
    MonoVintagePhaser = 0x31,
    StereoVintagePhaser = 0x32,
    ThreeBandParametricEQ = 0x33,
    SpringReverb = 0x34,
    TapeEcho = 0x35,
    Compressor = 0x36,
    AmpMultiChorus = 0x37,
    AmpMultiFlange = 0x38,
    AmpMultiTremolo = 0x39,
    AmpMultiPhaser = 0x3A,
    DistorionMultiChorus = 0x3B,
    DistorionMultiFlange = 0x3C,
    DistorionMultiTremolo = 0x3D,
    DistorionMultiPhaser = 0x3E,
    BassPreamp = 0x3F,
    EffectTypeNUMBER
};

#endif
