#ifndef AMPMULTIMODULATIONWIDGET_H
#define AMPMULTIMODULATIONWIDGET_H

#include "effecteditbasewidget.h"

class AmpMultiModulationWidget : public EffectEditBaseWidget
{
    Q_OBJECT
public:

    enum EffectType
    {
        Chorus,
        Flange,
        Tremolo,
        Phaser
    };

    explicit AmpMultiModulationWidget(EffectType type, QWidget *parent = nullptr);
};

#endif // AMPMULTIMODULATIONWIDGET_H
