#ifndef CHORUSWIDGET_H
#define CHORUSWIDGET_H

#include "effecteditbasewidget.h"

class ChorusWidget: public EffectEditBaseWidget
{
    Q_OBJECT
public:
    explicit ChorusWidget(QWidget *parent = nullptr);

    enum ParameterOffsets
    {
        ModDelay = 0x00, // 2 Bytes
        Freq = 0x10, //2 bytes
        AMDepth = 0x12, //2 bytes
        PMDepth = 0x14, //2 bytes
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

#endif // CHORUSWIDGET_H
