#include "gatereverbwidget.h"
#include "magicstomptext.h"
#include "hpfspinbox.h"
#include "lpfspinbox.h"
#include <QGridLayout>
#include <QDoubleSpinBox>
#include <QLabel>
#include <QSpinBox>
#include <QComboBox>
#include <QGroupBox>

GateReverbWidget::GateReverbWidget(bool isEarlyRefReverb, QWidget *parent) :
    EffectEditBaseWidget(parent)
{
    QSpinBox *spinBox;
    QDoubleSpinBox *dspinBox;
    QGridLayout *mainlyt = new QGridLayout();

    mainlyt->addWidget(new QLabel(tr("Type")), 0, 0);
    QComboBox *typeComboBox = new QComboBox();
    if(isEarlyRefReverb)
        typeComboBox->addItems( EarlyRefTypeNameList);
    else
        typeComboBox->addItems( GateReverbTypeNameList);
    typeComboBox->setCurrentIndex(-1);
    typeComboBox->setProperty( ArrayDataEditWidget::valuePropertyName, QStringLiteral("currentIndex"));
    typeComboBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, Type);
    typeComboBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    mainlyt->addWidget( typeComboBox, 1, 0);

    mainlyt->addWidget(new QLabel(tr("Mix")), 0, 1);
    spinBox = new QSpinBox();
    spinBox->setMinimum(0);
    spinBox->setMaximum(100);
    spinBox->setSuffix(" %");
    spinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, Mix);
    spinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    mainlyt->addWidget(spinBox, 1, 1);

    mainlyt->addWidget(new QLabel(tr("Room Size")), 0, 2);
    dspinBox = new QDoubleSpinBox();
    dspinBox->setMinimum(0.1);
    dspinBox->setMaximum(20.0);
    dspinBox->setSingleStep(0.1);
    dspinBox->setDecimals(1);
    dspinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, RoomSize);
    dspinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 2);
    dspinBox->setProperty( ArrayDataEditWidget::convertMethodProperty, QStringLiteral("scaleAndAdd(0.1, 0.1)"));
    mainlyt->addWidget(dspinBox, 1, 2);

    mainlyt->addWidget(new QLabel(tr("Liveness")), 0, 3);
    spinBox = new QSpinBox();
    spinBox->setMinimum(0);
    spinBox->setMaximum(10);
    spinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, Liveness);
    spinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    mainlyt->addWidget(spinBox, 1, 3);


    mainlyt->addWidget(new QLabel(tr("Diffusion")), 0, 4);
    spinBox = new QSpinBox();
    spinBox->setMinimum(0);
    spinBox->setMaximum(10);
    spinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, Diffusion);
    spinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    mainlyt->addWidget(spinBox, 1, 4);

    mainlyt->addWidget(new QLabel(tr("Density")), 0, 5);
    spinBox = new QSpinBox();
    spinBox->setMinimum(0);
    spinBox->setMaximum(100);
    spinBox->setSuffix(" %");
    spinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, Density);
    spinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    mainlyt->addWidget(spinBox, 1, 5);

    mainlyt->addWidget(new QLabel(tr("Init Delay")), 2, 0);
    dspinBox = new QDoubleSpinBox();
    dspinBox->setMinimum(0.0);
    dspinBox->setMaximum(500.0);
    dspinBox->setSingleStep(0.1);
    dspinBox->setDecimals(1);
    dspinBox->setSuffix(" ms");
    dspinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, InitDelay);
    dspinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 2);
    dspinBox->setProperty( ArrayDataEditWidget::convertMethodProperty, QStringLiteral("scaleAndAdd(0.1, 0)"));
    mainlyt->addWidget(dspinBox, 3, 0);

    mainlyt->addWidget(new QLabel(tr("FB Gain")), 2, 1);
    spinBox = new QSpinBox();
    spinBox->setMinimum(-99);
    spinBox->setMaximum(99);
    spinBox->setSuffix(" %");
    spinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, FBGain);
    spinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 2);
    spinBox->setProperty( ArrayDataEditWidget::convertMethodProperty, QStringLiteral("scaleAndAdd(1, -99)"));
    mainlyt->addWidget(spinBox, 3, 1);

    mainlyt->addWidget(new QLabel(tr("ER Number")), 2, 2);
    spinBox = new QSpinBox();
    spinBox->setMinimum(1);
    spinBox->setMaximum(19);
    spinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, ERNUmber);
    spinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    spinBox->setProperty( ArrayDataEditWidget::convertMethodProperty, QStringLiteral("scaleAndAdd(1, 1)"));
    mainlyt->addWidget(spinBox, 3, 2);

    mainlyt->addWidget(new QLabel(tr("High Ratio")), 2, 3);
    dspinBox = new QDoubleSpinBox();
    dspinBox->setMinimum(0.1);
    dspinBox->setMaximum(1.0);
    dspinBox->setSingleStep(0.1);
    dspinBox->setDecimals(1);
    dspinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, HighRatio);
    dspinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    dspinBox->setProperty( ArrayDataEditWidget::convertMethodProperty, QStringLiteral("scaleAndAdd(0.1, 0.1)"));
    mainlyt->addWidget(dspinBox, 3, 3);

    mainlyt->addWidget(new QLabel(tr("High Pass Filter")), 2, 4);
    HpfSpinBox *hpfSpinBox = new HpfSpinBox();
    hpfSpinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, HPF);
    hpfSpinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    mainlyt->addWidget(hpfSpinBox, 3, 4);

    mainlyt->addWidget(new QLabel(tr("Low Pass Filter")), 2, 5);
    LpfSpinBox *lpfSpinBox = new LpfSpinBox();
    lpfSpinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, LPF);
    lpfSpinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    mainlyt->addWidget(lpfSpinBox, 3, 5);

    mainlyt->setRowStretch(4,2);

    setLayout(mainlyt);
}
