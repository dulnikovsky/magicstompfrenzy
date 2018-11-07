#ifndef DUALPITCHWIDGET_H
#define DUALPITCHWIDGET_H

#include "effecteditbasewidget.h"

class DualPitchWidget: public EffectEditBaseWidget
{
    Q_OBJECT
public:
    explicit DualPitchWidget(QWidget *parent = nullptr);

    enum ParameterOffsets
    {
        FBGain2 = 0x00, // 2Bytes
        Delay1 = 0x10, // 2Bytes
        FBGain1 = 0x12, // 2Bytes
        Delay2 = 0x14, // 2Bytes
        Mode = 0x16,
        Pitch1 = 0x1E,
        Fine1 = 0x1F,
        Level1 = 0x20,
        Pan1 = 0x21,

        Pitch2 = 0x22,
        Fine2 = 0x23,
        Level2 = 0x24,
        Pan2 = 0x25,

        Mix = 0x28
    };
};

#endif // DUALPITCHWIDGET_H
