#ifndef AMPWIDGET_H
#define AMPWIDGET_H

#include "effecteditbasewidget.h"

class AmpWidget: public EffectEditBaseWidget
{
    Q_OBJECT
public:
    explicit AmpWidget(QWidget *parent = nullptr);
};

#endif // AMPWIDGET_H
