#include "multibanddelaywidget.h"
#include "delaybandwidget.h"
#include <QGridLayout>
#include <QDoubleSpinBox>
#include <QLabel>
#include <QSpinBox>

MultibandDelayWidget::MultibandDelayWidget(EffectTypeId id, QWidget *parent) :
    EffectEditBaseWidget(parent)
{
    QDoubleSpinBox *dspinBox;
    QGridLayout *mainlyt = new QGridLayout();

    for(int i=0; i<8; i++)
    {
        mainlyt->addWidget( new QLabel(tr("Band ")+ QString::number(i+1)), i, 0);
        mainlyt->addWidget( new DelayBandWidget( LowCutFilter1 + BandLenght*i), i, 2);
    }
    setLayout(mainlyt);
}

QDoubleSpinBox * MultibandDelayWidget::createTimeSpinBox(int offset, double minTime, double maxTime)
{
    QDoubleSpinBox *dspinBox = new QDoubleSpinBox();
    dspinBox->setSuffix(QStringLiteral(" ms"));
    dspinBox->setMinimum(minTime);
    dspinBox->setMaximum(maxTime);
    dspinBox->setSingleStep(0.1);
    dspinBox->setDecimals(1);
    dspinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, offset);
    dspinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 2);
    dspinBox->setProperty( ArrayDataEditWidget::convertMethodProperty, QStringLiteral("scaleAndAdd(0.1, 0.1)"));
    return dspinBox;
}
