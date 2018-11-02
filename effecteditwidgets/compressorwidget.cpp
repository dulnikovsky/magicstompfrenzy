#include "compressorwidget.h"

#include <QGridLayout>
#include <QDoubleSpinBox>
#include <QLabel>
#include <QSpinBox>

CompressorWidget::CompressorWidget(
        int thresholdOffset,
        int ratioOffset,
        int attackOffset,
        int releaseOffset,
        int kneeOffset,
        int gainOffset,
        QWidget *parent)
    :EffectEditBaseWidget(parent)
{
    setTitle(tr("Compressor"));

    QDoubleSpinBox *dspinBox;
    QSpinBox *spinBox;
    QGridLayout *mainlyt = new QGridLayout();

    mainlyt->addWidget(new QLabel(tr("Threshold")), 0, 0);
    dspinBox = new QDoubleSpinBox();
    dspinBox->setMinimum(-50.0);
    dspinBox->setMaximum(0.0);
    dspinBox->setSingleStep(0.1);
    dspinBox->setDecimals(1);
    dspinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, thresholdOffset);
    dspinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 2);
    dspinBox->setProperty( ArrayDataEditWidget::convertMethodProperty, QStringLiteral("scaleAndAdd(0.1, -54)"));
    mainlyt->addWidget(dspinBox, 1, 0);

    mainlyt->addWidget(new QLabel(tr("Ratio(?)")), 2, 0);
    spinBox = createStandardRawSpinBox(ratioOffset, 0, 0x0F);
    mainlyt->addWidget(spinBox, 3, 0);

    mainlyt->addWidget(new QLabel(tr("Attack")), 0, 1);
    spinBox = createStandardRawSpinBox(attackOffset, 0, 120);
    mainlyt->addWidget(spinBox, 1, 1);

    mainlyt->addWidget(new QLabel(tr("Release(?)")), 2, 1);
    spinBox = createStandardRawSpinBox(releaseOffset, 0, 0x7F);
    mainlyt->addWidget(spinBox, 3, 1);

    mainlyt->addWidget(new QLabel(tr("Knee(?)")), 0, 3);
    spinBox = createStandardRawSpinBox(kneeOffset, 0, 5);
    mainlyt->addWidget(spinBox, 1, 3);

    mainlyt->addWidget(new QLabel(tr("Gain")), 2, 3);
    dspinBox = new QDoubleSpinBox();
    dspinBox->setMinimum(0.0);
    dspinBox->setMaximum(18.0);
    dspinBox->setSingleStep(0.5);
    dspinBox->setDecimals(1);
    dspinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, gainOffset);
    dspinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    dspinBox->setProperty( ArrayDataEditWidget::convertMethodProperty, QStringLiteral("scaleAndAdd(0.5, 0)"));
    mainlyt->addWidget(dspinBox, 3, 3);

    setLayout(mainlyt);
}
