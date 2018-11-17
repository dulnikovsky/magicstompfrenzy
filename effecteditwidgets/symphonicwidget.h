#ifndef SYMPHONICWIDGET_H
#define SYMPHONICWIDGET_H

#include "effecteditbasewidget.h"

class SymphonicWidget: public EffectEditBaseWidget
{
    Q_OBJECT
public:
    explicit SymphonicWidget(QWidget *parent = nullptr);

    enum ParameterOffsets
    {
        Freq = 0x10, //2 bytes
        Depth = 0x12, //2 bytes
        ModDelay = 0x14, //2 bytes
        Wave =0x16,

        LSHFreq = 0x1E,
        LSHGain = 0x1F,

        EQFreq = 0x20,
        EQGain = 0x21,
        EQQ = 0x22,

        HSHFreq = 0x24,
        HSHGain = 0x25,

        Mix = 0x28
    };
};

#endif // FLANGEWIDGET_H
