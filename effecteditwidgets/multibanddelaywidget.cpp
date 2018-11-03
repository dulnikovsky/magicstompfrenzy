#include "multibanddelaywidget.h"
#include "delaybandwidget.h"
#include <QGridLayout>
#include <QDoubleSpinBox>
#include <QComboBox>
#include <QLabel>
#include <QSpinBox>

MultibandDelayWidget::MultibandDelayWidget(EffectTypeId id, QWidget *parent) :
    EffectEditBaseWidget(parent)
{
    QDoubleSpinBox *dspinBox;

    QGridLayout *headerRowLayout = new QGridLayout();

    headerRowLayout->addWidget(new QLabel(tr("Effect Level")), 0, 0);
    dspinBox = createStandard10DblSpinBox( EffectLevel);
    dspinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 2);
    headerRowLayout->addWidget(dspinBox, 1, 0);

    headerRowLayout->addWidget(new QLabel(tr("Direct Level")), 0, 1);
    dspinBox = createStandard10DblSpinBox( DirectLevel);
    dspinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 2);
    headerRowLayout->addWidget(dspinBox, 1, 1);

    headerRowLayout->addWidget(new QLabel(tr("Direct Pan")), 0, 2);
    dspinBox = new QDoubleSpinBox();
    dspinBox->setMinimum(-10.0);
    dspinBox->setMaximum(10.0);
    dspinBox->setSingleStep(0.1);
    dspinBox->setDecimals(1);
    dspinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, DirectPan);
    dspinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 2);
    dspinBox->setProperty( ArrayDataEditWidget::convertMethodProperty, QStringLiteral("scaleAndAdd(0.2, -10)"));
    headerRowLayout->addWidget(dspinBox, 1, 2);

    headerRowLayout->addWidget(new QLabel(tr("Waveform")), 0, 3);
    QComboBox *waveComboBox = new QComboBox();
    waveComboBox->setCurrentIndex(-1);
    waveComboBox->setProperty( ArrayDataEditWidget::valuePropertyName, QStringLiteral("currentIndex"));
    waveComboBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, WaveForm);
    waveComboBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 1);
    waveComboBox->addItem(tr("Triangle"));
    waveComboBox->addItem(tr("Saw Up"));
    waveComboBox->addItem(tr("Saw Down"));

    headerRowLayout->addWidget(waveComboBox, 1, 3);

    headerRowLayout->setColumnStretch(4,8);

    QGridLayout *gridlyt = new QGridLayout();
    gridlyt->addLayout(headerRowLayout, 0, 1, 1, 6);

    for(int i=0; i<8; i++)
    {
        gridlyt->addWidget( new QLabel(tr("Band ")+ QString::number(i+1)), i+1, 0);
        gridlyt->addWidget( new DelayBandWidget( LowCutFilter1 + BandLenght*i), i+1, 1);
    }

    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addLayout( headerRowLayout);
    mainLayout->addLayout( gridlyt);
    setLayout(mainLayout);
}

QDoubleSpinBox * MultibandDelayWidget::createTimeSpinBox(int offset, double minTime, double maxTime)
{
    QDoubleSpinBox *dspinBox = new QDoubleSpinBox();
    dspinBox->setSuffix(QStringLiteral(" ms"));
    dspinBox->setMinimum(minTime);
    dspinBox->setMaximum(maxTime);
    dspinBox->setSingleStep(0.1);
    dspinBox->setDecimals(1);
    dspinBox->setProperty( ArrayDataEditWidget::dataOffsetProperty, offset);
    dspinBox->setProperty( ArrayDataEditWidget::dataLenghtProperty, 2);
    dspinBox->setProperty( ArrayDataEditWidget::convertMethodProperty, QStringLiteral("scaleAndAdd(0.1, 0.1)"));
    return dspinBox;
}
