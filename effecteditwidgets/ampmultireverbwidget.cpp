#include "ampmultireverbwidget.h"
#include "ampmultiwidget.h"
#include "reverbtimespinbox.h"
#include <QGridLayout>
#include <QDoubleSpinBox>
#include <QLabel>
#include <QSpinBox>

AmpMultiReverbWidget::AmpMultiReverbWidget(QWidget *parent) :
    EffectEditBaseWidget(parent)
{
    setTitle(tr("Reverb"));

    QDoubleSpinBox *dspinBox;
    QSpinBox *spinBox;
    QGridLayout *mainlyt = new QGridLayout();

    mainlyt->addWidget(new QLabel(tr("Level")), 0, 0);
    dspinBox = createStandard10DblSpinBox( AmpMultiWidget::ReverbLevel);
    mainlyt->addWidget(dspinBox, 1, 0);

    mainlyt->addWidget(new QLabel(tr("Time")), 2, 0);
    ReverbTimeSpinBox *revTimeSpinBox = new ReverbTimeSpinBox();
    revTimeSpinBox->setParameters(0, 0x53);
    revTimeSpinBox->setSuffix(" ms");
    revTimeSpinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, AmpMultiWidget::ReverbTime);
    revTimeSpinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    mainlyt->addWidget(revTimeSpinBox, 3, 0);

    mainlyt->addWidget(new QLabel(tr("High")), 0, 1);
    dspinBox = new QDoubleSpinBox();
    dspinBox->setMinimum(0.0);
    dspinBox->setMaximum(1.0);
    dspinBox->setSingleStep(0.1);
    dspinBox->setDecimals(1);
    dspinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, AmpMultiWidget::ReverbHigh);
    dspinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    dspinBox->setProperty( ArrayDataEditWidget::convertMethodProperty, QStringLiteral("scaleAndAdd(0.1, 0)"));
    mainlyt->addWidget(dspinBox, 1, 1);

    mainlyt->addWidget(new QLabel(tr("Diffusion")), 2, 1);
    spinBox = createStandardRawSpinBox( AmpMultiWidget::ReverbDiffusion, 0, 10);
    mainlyt->addWidget(spinBox, 3, 1);

    mainlyt->addWidget(new QLabel(tr("Ini. Delay")), 0, 2);
    dspinBox = new QDoubleSpinBox();
    dspinBox->setSuffix(QStringLiteral(" ms"));
    dspinBox->setMinimum(0.0);
    dspinBox->setMaximum(500.0);
    dspinBox->setSingleStep(0.1);
    dspinBox->setDecimals(1);
    dspinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, AmpMultiWidget::ReverbIniDelay);
    dspinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 2);
    dspinBox->setProperty( ArrayDataEditWidget::convertMethodProperty, QStringLiteral("scaleAndAdd(0.1, 0)"));
    mainlyt->addWidget(dspinBox, 1, 2);

    mainlyt->addWidget(new QLabel(tr("Density")), 2, 2);
    spinBox = createStandardRawSpinBox( AmpMultiWidget::ReverbDensity, 0, 100);
    mainlyt->addWidget(spinBox, 3, 2);

    setLayout(mainlyt);
}
