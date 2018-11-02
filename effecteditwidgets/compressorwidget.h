#ifndef COMPRESSORIDGET_H
#define COMPRESSORIDGET_H

#include "effecteditbasewidget.h"

class CompressorWidget : public EffectEditBaseWidget
{
    Q_OBJECT
public:

    enum ParameterOffsets
    {
        Threshold = 0x00, // 2 bytes
        Ratio = 0x1E,
        Attack = 0x1F,
        Release = 0x20,
        Knee = 0x21,
        Gain = 0x22
    };

    explicit CompressorWidget(
            int thresholdOffset,
            int ratioOffset,
            int attackOffset,
            int releaseOffset,
            int kneeOffset,
            int gainOffset,
            QWidget *parent = nullptr);


};

#endif // COMPRESSORIDGET_H
