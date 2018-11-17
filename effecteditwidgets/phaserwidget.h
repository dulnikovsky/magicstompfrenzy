#ifndef PHASERWIDGET_H
#define PHASERWIDGET_H

#include "effecteditbasewidget.h"

class PhaserWidget: public EffectEditBaseWidget
{
    Q_OBJECT
public:
    explicit PhaserWidget(QWidget *parent = nullptr);

    enum ParameterOffsets
    {
        Offset= 0x00, // 2 Bytes
        Freq = 0x10, //2 bytes
        Depth = 0x12, //2 bytes
        FBGain = 0x14, //2 bytes
        Stage =0x16,

        Phase = 0x1E,
        LSHFreq = 0x1F,
        LSHGain = 0x20,
        HSHFreq = 0x21,
        HSHGain = 0x22,

        Mix = 0x28
    };
};

#endif // PHASERWIDGET_H
