#include "noisegatewidget.h"
#include <QGridLayout>
#include <QDoubleSpinBox>
#include <QLabel>
#include <QSpinBox>
#include "expspinbox.h"

NoiseGateWidget::NoiseGateWidget(int thresholdOffset,
                                 int attackOffset,
                                 int holdOffset,
                                 int decayOffset,
                                 QWidget *parent)
    :    EffectEditBaseWidget(parent)
{
    setTitle(tr("Noise Gate"));

    QDoubleSpinBox *dspinBox;
    QGridLayout *mainlyt = new QGridLayout();

    mainlyt->addWidget(new QLabel(tr("Threshold")), 0, 0);
    dspinBox = createStandard10DblSpinBox( thresholdOffset);
    mainlyt->addWidget(dspinBox, 1, 0);

    mainlyt->addWidget(new QLabel(tr("Attack")), 2, 0);
    QSpinBox *attackspinBox = createStandardRawSpinBox(attackOffset, 0, 120);
    attackspinBox->setSuffix(" ms");
    mainlyt->addWidget(attackspinBox, 3, 0);

    mainlyt->addWidget(new QLabel(tr("Hold")), 0, 1);
    ExpSpinBox *holdspinBox = new ExpSpinBox();
    holdspinBox->setSuffix(QStringLiteral(" ms"));
    holdspinBox->setParameters(0.2, 2040, 0, 0x6B);
    holdspinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, holdOffset);
    holdspinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    mainlyt->addWidget(holdspinBox, 1, 1);

    mainlyt->addWidget(new QLabel(tr("Decay(?)")), 2, 1);
    QSpinBox *decayspinBox = createStandardRawSpinBox(decayOffset, 0, 0x4F);
    /*QSpinBox *decayspinBox = new QSpinBox();
    decayspinBox->setSuffix(QStringLiteral(" ms"));
    decayspinBox->setMinimum(6);
    decayspinBox->setMaximum(44500);
    decayspinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, decayOffset);
    decayspinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);*/
    mainlyt->addWidget(decayspinBox, 3, 1);

    mainlyt->setRowStretch(4, 16);

    setLayout(mainlyt);
}
