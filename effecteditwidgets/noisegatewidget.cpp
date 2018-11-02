#include "noisegatewidget.h"
#include "ampmultiwidget.h"
#include <QGridLayout>
#include <QDoubleSpinBox>
#include <QLabel>
#include <QSpinBox>

NoiseGateWidget::NoiseGateWidget(QWidget *parent) :
    EffectEditBaseWidget(parent)
{
    setTitle(tr("Noise Gate"));

    QDoubleSpinBox *dspinBox;
    QGridLayout *mainlyt = new QGridLayout();

    mainlyt->addWidget(new QLabel(tr("Threshold")), 0, 0);
    dspinBox = createStandard10DblSpinBox( AmpMultiWidget::NoiseGateThreshold);
    mainlyt->addWidget(dspinBox, 1, 0);

    mainlyt->addWidget(new QLabel(tr("Attack")), 2, 0);
    QSpinBox *attackspinBox = createStandardRawSpinBox(AmpMultiWidget::NoiseGateAttack, 0, 120);
    attackspinBox->setSuffix(" ms");
    mainlyt->addWidget(attackspinBox, 3, 0);

    mainlyt->addWidget(new QLabel(tr("Hold(?)")), 0, 1);
    QSpinBox *holdspinBox = createStandardRawSpinBox(AmpMultiWidget::NoiseGateHold, 0, 0x6B);
    /*holdspinBox = new QDoubleSpinBox();
    holdspinBox->setSuffix(QStringLiteral(" ms"));
    holdspinBox->setMinimum(0.02);
    holdspinBox->setMaximum(2040);
    holdspinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, AmpMultiWidget::NoiseGateHold);
    holdspinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);*/
    mainlyt->addWidget(holdspinBox, 1, 1);

    mainlyt->addWidget(new QLabel(tr("Decay(?)")), 2, 1);
    QSpinBox *decayspinBox = createStandardRawSpinBox(AmpMultiWidget::NoiseGateDecay, 0, 0x4F);
    /*QSpinBox *decayspinBox = new QSpinBox();
    decayspinBox->setSuffix(QStringLiteral(" ms"));
    decayspinBox->setMinimum(6);
    decayspinBox->setMaximum(44500);
    decayspinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, AmpMultiWidget::NoiseGateDecay);
    decayspinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);*/
    mainlyt->addWidget(decayspinBox, 3, 1);

    setLayout(mainlyt);
}
