#include "effecteditbasewidget.h"

#include <QDoubleSpinBox>
#include <QSpinBox>

EffectEditBaseWidget::EffectEditBaseWidget(QWidget *parent)
    : QGroupBox(parent)
{

}


QDoubleSpinBox * EffectEditBaseWidget::createStandard10DblSpinBox(int offset)
{
    QDoubleSpinBox *dspinBox = new QDoubleSpinBox();
    dspinBox->setMinimum(0.0);
    dspinBox->setMaximum(10.0);
    dspinBox->setSingleStep(0.1);
    dspinBox->setDecimals(1);
    dspinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, offset);
    dspinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    dspinBox->setProperty( ArrayDataEditWidget::convertMethodProperty, QStringLiteral("scaleAndAdd(0.1, 0)"));
    return dspinBox;
}

QSpinBox * EffectEditBaseWidget::createStandardRawSpinBox(int offset, int minimum, int maximum, int length)
{
    QSpinBox *spinBox = new QSpinBox();
    spinBox->setMinimum(minimum);
    spinBox->setMaximum(maximum);
    spinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, offset);
    spinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, length);
    return spinBox;
}
