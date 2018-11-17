#include "phaserwidget.h"
#include "freqspinbox.h"
#include <QGridLayout>
#include <QDoubleSpinBox>
#include <QLabel>
#include <QSpinBox>
#include <QComboBox>
#include <QGroupBox>

PhaserWidget::PhaserWidget(QWidget *parent) :
    EffectEditBaseWidget(parent)
{
    QSpinBox *spinBox;
    QDoubleSpinBox *dspinBox;
    QGridLayout *mainlyt = new QGridLayout();

    mainlyt->addWidget(new QLabel(tr("Stage")), 0, 0);
    QComboBox *waveComboBox = new QComboBox();
    waveComboBox->addItem(QStringLiteral("2"));
    waveComboBox->addItem(QStringLiteral("4"));
    waveComboBox->addItem(QStringLiteral("6"));
    waveComboBox->addItem(QStringLiteral("8"));
    waveComboBox->addItem(QStringLiteral("10"));
    waveComboBox->addItem(QStringLiteral("12"));
    waveComboBox->addItem(QStringLiteral("16"));
    waveComboBox->setCurrentIndex(-1);
    waveComboBox->setProperty( ArrayDataEditWidget::valuePropertyName, QStringLiteral("currentIndex"));
    waveComboBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, Stage);
    waveComboBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    mainlyt->addWidget( waveComboBox, 1, 0);

    mainlyt->addWidget(new QLabel(tr("Mix")), 0, 1);
    spinBox = new QSpinBox();
    spinBox->setMinimum(0);
    spinBox->setMaximum(100);
    spinBox->setSuffix(" %");
    spinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, Mix);
    spinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    mainlyt->addWidget(spinBox, 1, 1);

    mainlyt->addWidget(new QLabel(tr("Freq")), 0, 2);
    dspinBox = new QDoubleSpinBox();
    dspinBox->setMinimum(0.05);
    dspinBox->setMaximum(40.0);
    dspinBox->setSingleStep(0.05);
    dspinBox->setDecimals(2);
    dspinBox->setSuffix(" Hz");
    dspinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, Freq);
    dspinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 2);
    dspinBox->setProperty( ArrayDataEditWidget::convertMethodProperty, QStringLiteral("scaleAndAdd(0.05, 0.05)"));
    mainlyt->addWidget(dspinBox, 1, 2);

    mainlyt->addWidget(new QLabel(tr("Depth")), 0, 3);
    spinBox = new QSpinBox();
    spinBox->setMinimum(0);
    spinBox->setMaximum(100);
    spinBox->setSuffix(" %");
    spinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, Depth);
    spinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 2);
    mainlyt->addWidget(spinBox, 1, 3);

    mainlyt->addWidget(new QLabel(tr("FB Gain")), 0, 4);
    spinBox = new QSpinBox();
    spinBox->setMinimum(-99);
    spinBox->setMaximum(99);
    spinBox->setSuffix(" %");
    spinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, FBGain);
    spinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 2);
    spinBox->setProperty( ArrayDataEditWidget::convertMethodProperty, QStringLiteral("scaleAndAdd(1, -99)"));
    mainlyt->addWidget(spinBox, 1, 4);

    mainlyt->addWidget(new QLabel(tr("Offset")), 0, 5);
    spinBox = new QSpinBox();
    spinBox->setMinimum(0);
    spinBox->setMaximum(100);
    spinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, Offset);
    spinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 2);
    mainlyt->addWidget(spinBox, 1, 5);

    mainlyt->addWidget(new QLabel(tr("Phase")), 2, 0);
    dspinBox = new QDoubleSpinBox();
    dspinBox->setMinimum(0.0);
    dspinBox->setMaximum(354.375);
    dspinBox->setSingleStep(5.625);
    dspinBox->setDecimals(2);
    dspinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, Phase);
    dspinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    dspinBox->setProperty( ArrayDataEditWidget::convertMethodProperty, QStringLiteral("scaleAndAdd(5.625, 0)"));
    mainlyt->addWidget(dspinBox, 3, 0);

    mainlyt->addWidget(new QLabel(tr("LSH Freq")), 2, 1);
    FreqSpinBox *lshspinBox = new FreqSpinBox();
    lshspinBox->setParameters( 21.2, 8000.0, 0, 0x67);
    lshspinBox->setSuffix(QStringLiteral(" Hz"));
    lshspinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, LSHFreq);
    lshspinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    mainlyt->addWidget(lshspinBox, 3, 1);

    mainlyt->addWidget(new QLabel(tr("LSH Gain")), 2, 2);
    dspinBox = new QDoubleSpinBox();
    dspinBox->setMinimum(-12.0);
    dspinBox->setMaximum(12.0);
    dspinBox->setSingleStep(0.5);
    dspinBox->setDecimals(1);
    dspinBox->setSuffix(QStringLiteral(" dB"));
    dspinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, LSHGain);
    dspinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    dspinBox->setProperty( ArrayDataEditWidget::convertMethodProperty, QStringLiteral("scaleAndAdd(0.5, -12.0)"));
    mainlyt->addWidget(dspinBox, 3, 2);

    mainlyt->addWidget(new QLabel(tr("HSH Freq")), 2, 3);
    FreqSpinBox *hshspinBox = new FreqSpinBox();
    hshspinBox->setParameters( 50.0, 16000.0, 0, 0x64);
    hshspinBox->setSuffix(QStringLiteral(" Hz"));
    hshspinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, HSHFreq);
    hshspinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    mainlyt->addWidget(hshspinBox, 3, 3);

    mainlyt->addWidget(new QLabel(tr("HSH Gain")), 2, 4);
    dspinBox = new QDoubleSpinBox();
    dspinBox->setMinimum(-12.0);
    dspinBox->setMaximum(12.0);
    dspinBox->setSingleStep(0.5);
    dspinBox->setDecimals(1);
    dspinBox->setSuffix(QStringLiteral(" dB"));
    dspinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, HSHGain);
    dspinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    dspinBox->setProperty( ArrayDataEditWidget::convertMethodProperty, QStringLiteral("scaleAndAdd(0.5, -12.0)"));
    mainlyt->addWidget(dspinBox, 3, 4);

    setLayout(mainlyt);
}
