#include "delaybandwidget.h"
#include "multibanddelaywidget.h"

#include <QGridLayout>
#include <QDoubleSpinBox>
#include <QLabel>
#include <QComboBox>
#include <QSpinBox>

DelayBandWidget::DelayBandWidget(int offset,bool showLabels, QWidget *parent) :
    EffectEditBaseWidget(parent)
{
    this->setProperty( ArrayDataEditWidget::dataOffsetProperty, offset);

    int col = 0;

    QDoubleSpinBox *dspinBox;
    QGridLayout *mainlyt = new QGridLayout();

    if(showLabels) mainlyt->addWidget(new QLabel(tr("Time")), 0, col);
    dspinBox = MultibandDelayWidget::createTimeSpinBox(
                ((offset - MultibandDelayWidget::LowCutFilter1)/MultibandDelayWidget::BandLenght)*2 - offset, 0.0, 696.0);
    mainlyt->addWidget(dspinBox, 1, col++);

    if(showLabels) mainlyt->addWidget(new QLabel(tr("Low Cut Filter")), 0, col);
    dspinBox = createStandard10DblSpinBox(0);
    mainlyt->addWidget(dspinBox, 1, col++);

    if(showLabels) mainlyt->addWidget(new QLabel(tr("High Cut Filter")), 0, col);
    dspinBox = createStandard10DblSpinBox(1);
    mainlyt->addWidget(dspinBox, 1, col++);

    if(showLabels) mainlyt->addWidget(new QLabel(tr("Feedback")), 0, col);
    dspinBox = createStandard10DblSpinBox(2);
    mainlyt->addWidget(dspinBox, 1, col++);

    if(showLabels) mainlyt->addWidget(new QLabel(tr("Wave")), 0, col);
    QComboBox *comboBox = new QComboBox();
    comboBox->setCurrentIndex(-1);
    comboBox->setProperty( ArrayDataEditWidget::valuePropertyName, QStringLiteral("currentIndex"));
    comboBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, 3);
    comboBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    comboBox->addItem(tr("Sine"));
    comboBox->addItem(tr("Other"));
    mainlyt->addWidget(comboBox, 1, col++);

    if(showLabels) mainlyt->addWidget(new QLabel(tr("Phase")), 0, col);
    comboBox = new QComboBox();
    comboBox->setCurrentIndex(-1);
    comboBox->setProperty( ArrayDataEditWidget::valuePropertyName, QStringLiteral("currentIndex"));
    comboBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, 4);
    comboBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    comboBox->addItem(tr("Normal"));
    comboBox->addItem(tr("Reverse"));
    mainlyt->addWidget(comboBox, 1, col++);

    if(showLabels) mainlyt->addWidget(new QLabel(tr("Tap")), 0, col);
    QSpinBox *spinBox = createStandardRawSpinBox(5, 0, 100);
    spinBox->setSuffix(QStringLiteral(" %"));
    mainlyt->addWidget(spinBox, 1, col++);

    if(showLabels) mainlyt->addWidget(new QLabel(tr("Speed")), 0, col);
    dspinBox = createStandard10DblSpinBox(6);
    mainlyt->addWidget(dspinBox, 1, col++);

    if(showLabels) mainlyt->addWidget(new QLabel(tr("Depth")), 0, col);
    dspinBox = createStandard10DblSpinBox(7);
    mainlyt->addWidget(dspinBox, 1, col++);

    if(showLabels) mainlyt->addWidget(new QLabel(tr("Pan")), 0, col);
    dspinBox = new QDoubleSpinBox();
    dspinBox->setMinimum(-10.0);
    dspinBox->setMaximum(10.0);
    dspinBox->setSingleStep(0.1);
    dspinBox->setDecimals(1);
    dspinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, 8);
    dspinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    dspinBox->setProperty( ArrayDataEditWidget::convertMethodProperty, QStringLiteral("scaleAndAdd(0.2, -10)"));
    mainlyt->addWidget(dspinBox, 1, col++);

    if(showLabels) mainlyt->addWidget(new QLabel(tr("Level")), 0, col);
    dspinBox = createStandard10DblSpinBox(9);
    mainlyt->addWidget(dspinBox, 1, col++);

    if(showLabels) mainlyt->addWidget(new QLabel(tr("Sync")), 0, col);
    spinBox = createStandardRawSpinBox(10, 0, 100);
    spinBox->setProperty( ArrayDataEditWidget::convertMethodProperty, QStringLiteral("scaleAndAdd(1, 1)"));
    mainlyt->addWidget(spinBox, 1, col++);

    setLayout(mainlyt);
}
