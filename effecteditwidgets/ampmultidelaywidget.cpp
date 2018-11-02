#include "ampmultidelaywidget.h"
#include "ampmultiwidget.h"
#include <QGridLayout>
#include <QDoubleSpinBox>
#include <QLabel>
#include <QSpinBox>

AmpMultiDelayWidget::AmpMultiDelayWidget(QWidget *parent) :
    EffectEditBaseWidget(parent)
{
    setTitle(tr("Delay"));

    QDoubleSpinBox *dspinBox;
    QSpinBox *spinBox;
    QGridLayout *mainlyt = new QGridLayout();

    mainlyt->addWidget(new QLabel(tr("Level")), 0, 0);
    dspinBox = createStandard10DblSpinBox( AmpMultiWidget::DelayLevel);
    mainlyt->addWidget(dspinBox, 1, 0);

    mainlyt->addWidget(new QLabel(tr("Feedback")), 2, 0);
    dspinBox = new QDoubleSpinBox();
    dspinBox->setSuffix(QStringLiteral(" ms"));
    dspinBox->setMinimum(0.0);
    dspinBox->setMaximum(1000.0);
    dspinBox->setSingleStep(0.1);
    dspinBox->setDecimals(1);
    dspinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, AmpMultiWidget::DelayFeedback);
    dspinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 2);
    dspinBox->setProperty( ArrayDataEditWidget::convertMethodProperty, QStringLiteral("scaleAndAdd(0.1, 0)"));
    mainlyt->addWidget(dspinBox, 3, 0);

    mainlyt->addWidget(new QLabel(tr("Tap L")), 0, 1);
    spinBox = createStandardRawSpinBox(AmpMultiWidget::DelayTapL, 0, 100);
    mainlyt->addWidget(spinBox, 1, 1);

    mainlyt->addWidget(new QLabel(tr("Tap R")), 0, 2);
    spinBox = createStandardRawSpinBox( AmpMultiWidget::DelayTapR, 0, 100);
    mainlyt->addWidget(spinBox, 1, 2);

    mainlyt->addWidget(new QLabel(tr("Feedback Gain")), 2, 1);
    spinBox = new QSpinBox();
    spinBox->setMinimum(-99);
    spinBox->setMaximum(99);
    spinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, AmpMultiWidget::DelayFeedbackGain);
    spinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    spinBox->setProperty( ArrayDataEditWidget::convertMethodProperty, QStringLiteral("scaleAndAdd(2, -99)")); //TODO check rounding
    mainlyt->addWidget(spinBox, 3, 1);

    mainlyt->addWidget(new QLabel(tr("High")), 2, 2);
    dspinBox = new QDoubleSpinBox();
    dspinBox->setMinimum(0.0);
    dspinBox->setMaximum(1.0);
    dspinBox->setSingleStep(0.1);
    dspinBox->setDecimals(1);
    dspinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, AmpMultiWidget::DelayHeigh);
    dspinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    dspinBox->setProperty( ArrayDataEditWidget::convertMethodProperty, QStringLiteral("scaleAndAdd(0.1, 0)"));
    mainlyt->addWidget(dspinBox, 3, 2);

    mainlyt->addWidget(new QLabel(tr("HPF(?)")), 0, 4);
    spinBox = createStandardRawSpinBox(AmpMultiWidget::DelayHPF, 0, 0x68);
    mainlyt->addWidget(spinBox, 1, 4);

    mainlyt->addWidget(new QLabel(tr("LPF(?)")), 2, 4);
    spinBox = createStandardRawSpinBox( AmpMultiWidget::DelayLPF, 0, 0x65);
    mainlyt->addWidget(spinBox, 3, 4);

    setLayout(mainlyt);
}
