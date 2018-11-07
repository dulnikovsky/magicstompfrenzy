#include "dualpitchwidget.h"

#include <QGridLayout>
#include <QDoubleSpinBox>
#include <QLabel>
#include <QSpinBox>
#include <QComboBox>

DualPitchWidget::DualPitchWidget(QWidget *parent) :
    EffectEditBaseWidget(parent)
{
    QSpinBox *spinBox = new QSpinBox();
    QDoubleSpinBox *dspinBox;
    QGridLayout *mainlyt = new QGridLayout();

    mainlyt->addWidget(new QLabel(tr("Mode")), 0, 1);
    spinBox = new QSpinBox();
    spinBox->setMinimum(1);
    spinBox->setMaximum(10);
    spinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, Mode);
    spinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    spinBox->setProperty( ArrayDataEditWidget::convertMethodProperty, QStringLiteral("scaleAndAdd(1, 1)"));
    mainlyt->addWidget(spinBox, 1, 1);

    mainlyt->addWidget(new QLabel(tr("Mix")), 0, 2);
    spinBox = new QSpinBox();
    spinBox->setMinimum(0);
    spinBox->setMaximum(100);
    spinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, Mix);
    spinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    mainlyt->addWidget(spinBox, 1, 2);

    mainlyt->addWidget(new QLabel(tr("1")), 2, 0, 2, 1);

    mainlyt->addWidget(new QLabel(tr("Pitch")), 2, 1);
    spinBox = new QSpinBox();
    spinBox->setMinimum(-12);
    spinBox->setMaximum(12);
    spinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, Pitch1);
    spinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    spinBox->setProperty( ArrayDataEditWidget::convertMethodProperty, QStringLiteral("scaleAndAdd(1, -12)"));
    mainlyt->addWidget(spinBox, 3, 1);

    mainlyt->addWidget(new QLabel(tr("Fine")), 2, 2);
    spinBox = new QSpinBox();
    spinBox->setMinimum(-50);
    spinBox->setMaximum(50);
    spinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, Fine1);
    spinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    spinBox->setProperty( ArrayDataEditWidget::convertMethodProperty, QStringLiteral("scaleAndAdd(1, -50)"));
    mainlyt->addWidget(spinBox, 3, 2);

    mainlyt->addWidget(new QLabel(tr("Delay")), 2, 3);
    dspinBox = new QDoubleSpinBox();
    dspinBox->setMinimum(0.0);
    dspinBox->setMaximum(1000.0);
    dspinBox->setSingleStep(0.1);
    dspinBox->setDecimals(1);
    dspinBox->setSuffix(QStringLiteral(" ms"));
    dspinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, Delay1);
    dspinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 2);
    dspinBox->setProperty( ArrayDataEditWidget::convertMethodProperty, QStringLiteral("scaleAndAdd(0.1, 0)"));
    mainlyt->addWidget(dspinBox, 3, 3);

    mainlyt->addWidget(new QLabel(tr("FB Gain")), 2, 4);
    spinBox = new QSpinBox();
    spinBox->setMinimum(-99);
    spinBox->setMaximum(99);
    spinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, FBGain1);
    spinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 2);
    spinBox->setProperty( ArrayDataEditWidget::convertMethodProperty, QStringLiteral("scaleAndAdd(1, -99)"));
    mainlyt->addWidget(spinBox, 3, 4);

    mainlyt->addWidget(new QLabel(tr("Pan")), 2, 5);
    spinBox = new QSpinBox();
    spinBox->setMinimum(-63);
    spinBox->setMaximum(63);
    spinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, Pan1);
    spinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    spinBox->setProperty( ArrayDataEditWidget::convertMethodProperty, QStringLiteral("scaleAndAdd(1, -63)"));
    mainlyt->addWidget(spinBox, 3, 5);

    mainlyt->addWidget(new QLabel(tr("Level")), 2, 6);
    spinBox = new QSpinBox();
    spinBox->setMinimum(-100);
    spinBox->setMaximum(100);
    spinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, Level1);
    spinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    spinBox->setProperty( ArrayDataEditWidget::convertMethodProperty, QStringLiteral("scaleAndAdd(2, -100)"));
    mainlyt->addWidget(spinBox, 3, 6);

    mainlyt->addWidget(new QLabel(tr("2")), 4, 0, 2, 1);

    mainlyt->addWidget(new QLabel(tr("Pitch")), 4, 1);
    spinBox = new QSpinBox();
    spinBox->setMinimum(-12);
    spinBox->setMaximum(12);
    spinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, Pitch2);
    spinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    spinBox->setProperty( ArrayDataEditWidget::convertMethodProperty, QStringLiteral("scaleAndAdd(1, -12)"));
    mainlyt->addWidget(spinBox, 5, 1);

    mainlyt->addWidget(new QLabel(tr("Fine")), 4, 2);
    spinBox = new QSpinBox();
    spinBox->setMinimum(-50);
    spinBox->setMaximum(50);
    spinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, Fine2);
    spinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    spinBox->setProperty( ArrayDataEditWidget::convertMethodProperty, QStringLiteral("scaleAndAdd(1, -50)"));
    mainlyt->addWidget(spinBox, 5, 2);

    mainlyt->addWidget(new QLabel(tr("Delay")), 4, 3);
    dspinBox = new QDoubleSpinBox();
    dspinBox->setMinimum(0.0);
    dspinBox->setMaximum(1000.0);
    dspinBox->setSingleStep(0.1);
    dspinBox->setDecimals(1);
    dspinBox->setSuffix(QStringLiteral(" ms"));
    dspinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, Delay2);
    dspinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 2);
    dspinBox->setProperty( ArrayDataEditWidget::convertMethodProperty, QStringLiteral("scaleAndAdd(0.1, 0)"));
    mainlyt->addWidget(dspinBox, 5, 3);

    mainlyt->addWidget(new QLabel(tr("FB Gain")), 4, 4);
    spinBox = new QSpinBox();
    spinBox->setMinimum(-99);
    spinBox->setMaximum(99);
    spinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, FBGain2);
    spinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 2);
    spinBox->setProperty( ArrayDataEditWidget::convertMethodProperty, QStringLiteral("scaleAndAdd(1, -99)"));
    mainlyt->addWidget(spinBox, 5, 4);

    mainlyt->addWidget(new QLabel(tr("Pan")), 4, 5);
    spinBox = new QSpinBox();
    spinBox->setMinimum(-63);
    spinBox->setMaximum(63);
    spinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, Pan2);
    spinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    spinBox->setProperty( ArrayDataEditWidget::convertMethodProperty, QStringLiteral("scaleAndAdd(1, -63)"));
    mainlyt->addWidget(spinBox, 5, 5);

    mainlyt->addWidget(new QLabel(tr("Level")), 4, 6);
    spinBox = new QSpinBox();
    spinBox->setMinimum(-100);
    spinBox->setMaximum(100);
    spinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, Level2);
    spinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    spinBox->setProperty( ArrayDataEditWidget::convertMethodProperty, QStringLiteral("scaleAndAdd(2, -100)"));
    mainlyt->addWidget(spinBox, 5, 6);

    mainlyt->setColumnStretch(7,8);
    setLayout(mainlyt);
}
