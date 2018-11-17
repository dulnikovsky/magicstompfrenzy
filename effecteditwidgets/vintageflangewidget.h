#ifndef VINTAGEFLANGEWIDGET_H
#define VINTAGEFLANGEWIDGET_H

#include "effecteditbasewidget.h"

class VintageFlangeWidget: public EffectEditBaseWidget
{
    Q_OBJECT
public:
    explicit VintageFlangeWidget(QWidget *parent = nullptr);

    enum ParameterOffsets
    {
        Speed = 0x00, // 2Bytes

        Type = 0x16,
        Depth = 0x1E,
        Manual = 0x1F,
        Feedback = 0x20,
        SpeedLRDiff = 0x21,
        Mix = 0x22
    };
};

#endif // VINTAGEFLANGEWIDGET_H
