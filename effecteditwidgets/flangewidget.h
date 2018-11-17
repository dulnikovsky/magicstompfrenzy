#ifndef FLANGEWIDGET_H
#define FLANGEWIDGET_H

#include "effecteditbasewidget.h"

class FlangeWidget: public EffectEditBaseWidget
{
    Q_OBJECT
public:
    explicit FlangeWidget(QWidget *parent = nullptr);

    enum ParameterOffsets
    {
        ModDelay = 0x00, // 2 Bytes
        Freq = 0x10, //2 bytes
        Depth = 0x12, //2 bytes
        FBGain = 0x14, //2 bytes
        Wave =0x16,

        LSHFreq = 0x1E,
        LSHGain = 0x1F,

        EQFreq = 0x20,
        EQGain = 0x21,
        EQQ = 0x22,

        HSHFreq = 0x23,
        HSHGain = 0x24,

        Mix = 0x28
    };
};

#endif // FLANGEWIDGET_H
