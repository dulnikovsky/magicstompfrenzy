#ifndef EFFECTEDITBASEWIDGET_H
#define EFFECTEDITBASEWIDGET_H

#include <QGroupBox>

#include "../magicstomp.h"
#include "../arraydataeditwidget.h"

class QDoubleSpinBox;

class EffectEditBaseWidget : public QGroupBox
{
    Q_OBJECT
public:
    explicit EffectEditBaseWidget(QWidget *parent = nullptr);


static QDoubleSpinBox* createStandardDblSpinBox(int offset);

};

#endif // EFFECTEDITBASEWIDGET_H
