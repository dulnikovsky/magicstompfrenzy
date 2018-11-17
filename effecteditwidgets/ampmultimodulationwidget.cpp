#include "ampmultimodulationwidget.h"
#include "ampmultiwidget.h"
#include <QGridLayout>
#include <QDoubleSpinBox>
#include <QLabel>
#include <QComboBox>
#include <QSpinBox>

AmpMultiModulationWidget::AmpMultiModulationWidget(EffectType type, QWidget *parent) :
    EffectEditBaseWidget(parent)
{
    if(type == Chorus)
        setTitle(tr("Chorus"));
    else if(type == Flange)
        setTitle(tr("Flange"));
    else if(type == Tremolo)
        setTitle(tr("Tremolo"));
    else if(type == Phaser)
        setTitle(tr("Phaser"));

    QDoubleSpinBox *dspinBox;
    QGridLayout *mainlyt = new QGridLayout();

    mainlyt->addWidget(new QLabel(tr("Wave")), 0, 0);
    QComboBox *waveComboBox = new QComboBox();
    waveComboBox->setCurrentIndex(-1);
    waveComboBox->setProperty( ArrayDataEditWidget::valuePropertyName, QStringLiteral("currentIndex"));
    waveComboBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, AmpMultiWidget::ModWave);
    waveComboBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    waveComboBox->addItem(QStringLiteral("Sine"));
    waveComboBox->addItem(QStringLiteral("Triangle"));
    if(type == Tremolo)
        waveComboBox->addItem(tr("Square"));
    mainlyt->addWidget(waveComboBox, 1, 0);

    if(type != Tremolo)
    {
        mainlyt->addWidget(new QLabel(tr("Level")), 2, 0);
        if(type == Chorus)
            dspinBox = createStandard10DblSpinBox( AmpMultiWidget::ChorusLevel);
        else
            dspinBox = createStandard10DblSpinBox( AmpMultiWidget::FlangePhaserLevel);
        mainlyt->addWidget(dspinBox, 3, 0);
    }

    mainlyt->addWidget(new QLabel(tr("Speed")), 0, 1);
    dspinBox = createStandard10DblSpinBox( AmpMultiWidget::ModSpeed);
    mainlyt->addWidget(dspinBox, 1, 1);

    mainlyt->addWidget(new QLabel(tr("Depth")), 2, 1);
    dspinBox = createStandard10DblSpinBox( AmpMultiWidget::ModDepth);
    mainlyt->addWidget(dspinBox, 3, 1);

    if(type == Chorus || type == Flange)
    {
        mainlyt->addWidget(new QLabel(tr("Delay")), 0, 3);
        dspinBox = new QDoubleSpinBox();
        dspinBox->setMinimum(0.0);
        if(type == Chorus)
            dspinBox->setMaximum(30.0);
        else
            dspinBox->setMaximum(10.0);
        dspinBox->setSingleStep(0.1);
        dspinBox->setDecimals(1);
        dspinBox->setSuffix(QStringLiteral(" ms"));
        dspinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, AmpMultiWidget::ChorusFlangerDelay);
        dspinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 2);
        dspinBox->setProperty( ArrayDataEditWidget::convertMethodProperty, QStringLiteral("scaleAndAdd(0.1, 0)"));
        mainlyt->addWidget(dspinBox, 1, 3);
    }

    if(type == Flange || type == Phaser)
    {
        mainlyt->addWidget(new QLabel(tr("Feedback")), 2, 3);
        QSpinBox *spinBox = new QSpinBox();
        spinBox->setMinimum(-99);
        spinBox->setMaximum(99);
        spinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, AmpMultiWidget::ModFeedback);
        spinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
        spinBox->setProperty( ArrayDataEditWidget::convertMethodProperty, QStringLiteral("scaleAndAdd(2, -99)")); //TODO check rounding
        mainlyt->addWidget(spinBox, 3, 3);
    }

    setLayout(mainlyt);
}
