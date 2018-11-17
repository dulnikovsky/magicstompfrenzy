#ifndef VINTAGEPHASERWIDGET_H
#define VINTAGEPHASERWIDGET_H

#include "effecteditbasewidget.h"

class VintagePhaserWidget: public EffectEditBaseWidget
{
    Q_OBJECT
public:
    explicit VintagePhaserWidget(bool isMono = true, QWidget *parent = nullptr);

    enum ParameterOffsets
    {
        Mode = 0x00, // 2 Bytes
        Stage =0x16,

        Speed = 0x1E,
        Depth = 0x1F,
        Manual = 0x20,
        Feedback = 0x21,
        Color = 0x22,
        Spread = 0x23
    };
};

#endif // VINTAGEPHASERWIDGET_H
