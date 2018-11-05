#include "basspreamp.h"
#include "magicstomptext.h"
#include <QLabel>
#include <QGridLayout>
#include <QDoubleSpinBox>
#include <QSpinBox>
#include <QComboBox>

BassPreampWidget::BassPreampWidget( QWidget *parent) :
    EffectEditBaseWidget(parent)
{
    QDoubleSpinBox *dspinBox;
    QSpinBox *spinBox;
    QGridLayout *mainlyt = new QGridLayout();

    mainlyt->addWidget(new QLabel(tr("Type")), 0, 0, 1, 2);
    QComboBox *speakerComboBox = new QComboBox();
    speakerComboBox->addItems( BassPreampTypeNameList);
    speakerComboBox->setCurrentIndex(-1);
    speakerComboBox->setProperty( ArrayDataEditWidget::valuePropertyName, QStringLiteral("currentIndex"));
    speakerComboBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, Type);
    speakerComboBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    mainlyt->addWidget( speakerComboBox, 1, 0);

    mainlyt->addWidget(new QLabel(tr("Gain")), 2, 0);
    dspinBox = new QDoubleSpinBox();
    dspinBox->setMinimum(0.0);
    dspinBox->setMaximum(10.0);
    dspinBox->setSingleStep(0.1);
    dspinBox->setDecimals(1);
    dspinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, Gain);
    dspinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 2);
    dspinBox->setProperty( ArrayDataEditWidget::convertMethodProperty, QStringLiteral("scaleAndAdd(0.1, 0)"));
    mainlyt->addWidget(dspinBox, 3, 0);

    mainlyt->addWidget(new QLabel(tr("Master")), 4, 0);
    dspinBox = new QDoubleSpinBox();
    dspinBox->setMinimum(0.0);
    dspinBox->setMaximum(10.0);
    dspinBox->setSingleStep(0.1);
    dspinBox->setDecimals(1);
    dspinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, Master);
    dspinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 2);
    dspinBox->setProperty( ArrayDataEditWidget::convertMethodProperty, QStringLiteral("scaleAndAdd(0.1, 0)"));
    mainlyt->addWidget(dspinBox, 5, 0);

    mainlyt->addWidget(new QLabel(tr("Bass")), 2, 1);
    dspinBox = createStdGainSpinBox(Bass);
    mainlyt->addWidget(dspinBox, 3, 1);

    mainlyt->addWidget(new QLabel(tr("Low Middle")), 2, 2);
    dspinBox = createStdGainSpinBox(LowMiddle);
    mainlyt->addWidget(dspinBox, 3, 2);

    mainlyt->addWidget(new QLabel(tr("Middle")), 2, 3);
    dspinBox = createStdGainSpinBox(Middle);
    mainlyt->addWidget(dspinBox, 3, 3);

    mainlyt->addWidget(new QLabel(tr("High Middle")), 2, 4);
    dspinBox = createStdGainSpinBox(HighMiddle);
    mainlyt->addWidget(dspinBox, 3, 4);

    mainlyt->addWidget(new QLabel(tr("Treble")), 2, 5);
    dspinBox = createStdGainSpinBox(Treble);
    mainlyt->addWidget(dspinBox, 3, 5);

    setLayout(mainlyt);
}

QDoubleSpinBox* BassPreampWidget::createStdGainSpinBox(int offset)
{
    QDoubleSpinBox *dspinBox = new QDoubleSpinBox();
    dspinBox->setMinimum(-15.0);
    dspinBox->setMaximum(15.0);
    dspinBox->setSingleStep(0.25);
    dspinBox->setDecimals(2);
    dspinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, offset);
    dspinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    dspinBox->setProperty( ArrayDataEditWidget::convertMethodProperty, QStringLiteral("scaleAndAdd(0.25, -15.0)"));
    return dspinBox;
}
