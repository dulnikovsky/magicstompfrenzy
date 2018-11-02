#ifndef EFFECTEDITBASEWIDGET_H
#define EFFECTEDITBASEWIDGET_H

#include <QGroupBox>

#include "../magicstomp.h"
#include "../arraydataeditwidget.h"

class QDoubleSpinBox;
class QSpinBox;

class EffectEditBaseWidget : public QGroupBox
{
    Q_OBJECT
public:
    explicit EffectEditBaseWidget(QWidget *parent = nullptr);


static QDoubleSpinBox* createStandard10DblSpinBox(int offset);
static QSpinBox* createStandardRawSpinBox(int offset, int minimum, int maximum, int length = 1);

};

#endif // EFFECTEDITBASEWIDGET_H
