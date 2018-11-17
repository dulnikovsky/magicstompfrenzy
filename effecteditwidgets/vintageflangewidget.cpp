#include "vintageflangewidget.h"

#include <QGridLayout>
#include <QDoubleSpinBox>
#include <QLabel>
#include <QSpinBox>
#include <QComboBox>

VintageFlangeWidget::VintageFlangeWidget(QWidget *parent) :
    EffectEditBaseWidget(parent)
{
    QSpinBox *spinBox;
    QDoubleSpinBox *dspinBox;
    QGridLayout *mainlyt = new QGridLayout();

    mainlyt->addWidget(new QLabel(tr("Type")), 0, 0);
    spinBox = new QSpinBox();
    spinBox->setMinimum(1);
    spinBox->setMaximum(3);
    spinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, Type);
    spinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    spinBox->setProperty( ArrayDataEditWidget::convertMethodProperty, QStringLiteral("scaleAndAdd(1, 1)"));
    mainlyt->addWidget(spinBox, 1, 0);

    mainlyt->addWidget(new QLabel(tr("Speed")), 0, 1);
    dspinBox = new QDoubleSpinBox();
    dspinBox->setMinimum(0.0);
    dspinBox->setMaximum(10.0);
    dspinBox->setSingleStep(0.1);
    dspinBox->setDecimals(1);
    dspinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, Speed);
    dspinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 2);
    dspinBox->setProperty( ArrayDataEditWidget::convertMethodProperty, QStringLiteral("scaleAndAdd(0.1, 0)"));
    mainlyt->addWidget(dspinBox, 1, 1);

    mainlyt->addWidget(new QLabel(tr("Depth")), 0, 2);
    dspinBox = createStandard10DblSpinBox(Depth);
    mainlyt->addWidget(dspinBox, 1, 2);

    mainlyt->addWidget(new QLabel(tr("Manual")), 0, 3);
    dspinBox = createStandard10DblSpinBox(Manual);
    mainlyt->addWidget(dspinBox, 1, 3);

    mainlyt->addWidget(new QLabel(tr("Feedback")), 2, 0);
    dspinBox = createStandard10DblSpinBox(Feedback);
    mainlyt->addWidget(dspinBox, 3, 0);

    mainlyt->addWidget(new QLabel(tr("Speed (LR Diffusion)")), 2, 1, 1, 2);
    dspinBox = createStandard10DblSpinBox(SpeedLRDiff);
    mainlyt->addWidget(dspinBox, 3, 1);

    mainlyt->addWidget(new QLabel(tr("Mix")), 2, 3);
    dspinBox = createStandard10DblSpinBox(Mix);
    mainlyt->addWidget(dspinBox, 3, 3);

    mainlyt->setRowStretch(4,2);
    mainlyt->setColumnStretch(4,2);
    setLayout(mainlyt);
}
