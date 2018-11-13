#include "distortionwidget.h"
#include "magicstomptext.h"
#include "freqspinbox.h"
#include <QGridLayout>
#include <QDoubleSpinBox>
#include <QLabel>
#include <QComboBox>

DistortionWidget::DistortionWidget(QWidget *parent) :
    EffectEditBaseWidget(parent)
{
    setTitle(tr("Distortion"));

    QDoubleSpinBox *dspinBox;
    FreqSpinBox *fspinBox = new FreqSpinBox();
    QGridLayout *mainlyt = new QGridLayout();

    mainlyt->addWidget(new QLabel(tr("Type")), 0, 0);
    QComboBox *typeComboBox = new QComboBox();
    typeComboBox->addItems( DistortionTypeNameList);
    typeComboBox->setCurrentIndex(-1);
    typeComboBox->setProperty( ArrayDataEditWidget::valuePropertyName, QStringLiteral("currentIndex"));
    typeComboBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, DistortionType);
    typeComboBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    mainlyt->addWidget( typeComboBox, 1, 0);

    mainlyt->addWidget(new QLabel(tr("Gain")), 0, 1);
    dspinBox = createStandard10DblSpinBox( Gain);
    dspinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 2);
    mainlyt->addWidget(dspinBox, 1, 1);

    mainlyt->addWidget(new QLabel(tr("Master")), 0, 2);
    dspinBox = createStandard10DblSpinBox( Master);
    dspinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 2);
    mainlyt->addWidget(dspinBox, 1, 2);

    mainlyt->addWidget(new QLabel(tr("Tone")), 0, 3);
    dspinBox = createStandard10DblSpinBox( Tone);
    dspinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 2);
    mainlyt->addWidget(dspinBox, 1, 3);

    mainlyt->addWidget(new QLabel(tr("EQ 1 Freq")), 2, 0);
    fspinBox = new FreqSpinBox();
    fspinBox->setParameters(50.0, 400.0);
    fspinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, EQ1Freq);
    fspinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 2);
    mainlyt->addWidget(fspinBox, 3, 0);

    mainlyt->addWidget(new QLabel(tr("EQ 1 Gain")), 2, 1);
    dspinBox = createStd12GainSpinBox( EQ1Gain);
    mainlyt->addWidget(dspinBox, 3, 1);

    mainlyt->addWidget(new QLabel(tr("EQ 1 Q")), 2, 2);
    ExpSpinBox *extSpinBox = new ExpSpinBox();
    extSpinBox->setParameters(0.1, 20.0);
    extSpinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, EQ1Q);
    extSpinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    mainlyt->addWidget(extSpinBox, 3, 2);

    mainlyt->addWidget(new QLabel(tr("EQ 2 Freq")), 2, 3);
    fspinBox = new FreqSpinBox();
    fspinBox->setParameters(200.0, 1600.0);
    fspinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, EQ2Freq);
    fspinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    mainlyt->addWidget(fspinBox, 3, 3);

    mainlyt->addWidget(new QLabel(tr("EQ 2 Gain")), 2, 4);
    dspinBox = createStd12GainSpinBox( EQ2Gain);
    mainlyt->addWidget(dspinBox, 3, 4);

    mainlyt->addWidget(new QLabel(tr("EQ 2 Q")), 2, 5);
    extSpinBox = new ExpSpinBox();
    extSpinBox->setParameters(0.1, 20.0);
    extSpinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, EQ2Q);
    extSpinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    mainlyt->addWidget(extSpinBox, 3, 5);

    mainlyt->addWidget(new QLabel(tr("EQ 3 Freq")), 4, 0);
    fspinBox = new FreqSpinBox();
    fspinBox->setParameters(600.0, 4800.0);
    fspinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, EQ3Freq);
    fspinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    mainlyt->addWidget(fspinBox, 5, 0);

    mainlyt->addWidget(new QLabel(tr("EQ 3 Gain")), 4, 1);
    dspinBox = createStd12GainSpinBox( EQ3Gain);
    mainlyt->addWidget(dspinBox, 5, 1);

    mainlyt->addWidget(new QLabel(tr("EQ 3 Q")), 4, 2);
    extSpinBox = new ExpSpinBox();
    extSpinBox->setParameters(0.1, 20.0);
    extSpinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, EQ3Q);
    extSpinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    mainlyt->addWidget(extSpinBox, 5, 2);

    mainlyt->addWidget(new QLabel(tr("EQ 4 Freq")), 4, 3);
    fspinBox = new FreqSpinBox();
    fspinBox->setParameters(2000.0, 16000.0);
    fspinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, EQ4Freq);
    fspinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    mainlyt->addWidget(fspinBox, 5, 3);

    mainlyt->addWidget(new QLabel(tr("EQ 3 Gain")), 4, 4);
    dspinBox = createStd12GainSpinBox( EQ4Gain);
    mainlyt->addWidget(dspinBox, 5, 4);

    mainlyt->addWidget(new QLabel(tr("EQ 4 Q")), 4, 5);
    extSpinBox = new ExpSpinBox();
    extSpinBox->setParameters(0.1, 20.0);
    extSpinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, EQ4Q);
    extSpinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    mainlyt->addWidget(extSpinBox, 5, 5);

    mainlyt->addWidget(new QLabel(tr("Pre EQ Level")), 6, 0);
    dspinBox = createStandard10DblSpinBox( PreEQLevel);
    dspinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 2);
    mainlyt->addWidget(dspinBox, 7, 0);

    mainlyt->addWidget(new QLabel(tr("Pre EQ 1 Freq")), 6, 3);
    fspinBox = new FreqSpinBox();
    fspinBox->setParameters(50.0, 500.0);
    fspinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, PreEQ1Freq);
    fspinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    mainlyt->addWidget(fspinBox, 7, 3);

    mainlyt->addWidget(new QLabel(tr("Pre EQ 1 Gain")), 6, 4);
    dspinBox = createStd12GainSpinBox( PreEQ1Gain);
    mainlyt->addWidget(dspinBox, 7, 4);

    mainlyt->addWidget(new QLabel(tr("Pre EQ 1 Q")), 6, 5);
    extSpinBox = new ExpSpinBox();
    extSpinBox->setParameters(0.1, 20.0);
    extSpinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, PreEQ1Q);
    extSpinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    mainlyt->addWidget(extSpinBox, 7, 5);

    mainlyt->addWidget(new QLabel(tr("Pre EQ 2 Freq")), 8, 0);
    fspinBox = new FreqSpinBox();
    fspinBox->setParameters(200.0, 2000.0);
    fspinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, PreEQ2Freq);
    fspinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    mainlyt->addWidget(fspinBox, 9, 0);

    mainlyt->addWidget(new QLabel(tr("Pre EQ 2 Gain")), 8, 1);
    dspinBox = createStd12GainSpinBox( PreEQ2Gain);
    mainlyt->addWidget(dspinBox, 9, 1);

    mainlyt->addWidget(new QLabel(tr("Pre EQ 2 Q")), 8, 2);
    extSpinBox = new ExpSpinBox();
    extSpinBox->setParameters(0.1, 20.0);
    extSpinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, PreEQ2Q);
    extSpinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    mainlyt->addWidget(extSpinBox, 9, 2);

    mainlyt->addWidget(new QLabel(tr("Pre EQ 3 Freq")), 8, 3);
    fspinBox = new FreqSpinBox();
    fspinBox->setParameters(1000.0, 10000.0);
    fspinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, PreEQ3Freq);
    fspinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    mainlyt->addWidget(fspinBox, 9, 3);

    mainlyt->addWidget(new QLabel(tr("Pre EQ 3 Gain")), 8, 4);
    dspinBox = createStd12GainSpinBox( PreEQ3Gain);
    mainlyt->addWidget(dspinBox, 9, 4);

    mainlyt->addWidget(new QLabel(tr("Pre EQ 3 Q")), 8, 5);
    extSpinBox = new ExpSpinBox();
    extSpinBox->setParameters(0.1, 20.0);
    extSpinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, PreEQ3Q);
    extSpinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    mainlyt->addWidget(extSpinBox, 9, 5);

    setLayout(mainlyt);
}
