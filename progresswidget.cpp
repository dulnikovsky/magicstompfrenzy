#include "progresswidget.h"

#include <QProgressBar>
#include <QPushButton>
#include <QHBoxLayout>

ProgressWidget::ProgressWidget(QWidget *parent)
    : QWidget(parent)
{
    QHBoxLayout *lyt = new QHBoxLayout();
    progressBar = new QProgressBar();
    cancelButton = new QPushButton(tr("Cancel"));
    connect(cancelButton, SIGNAL(pressed()), this, SIGNAL(cancel()));
    lyt->addWidget(progressBar);
    lyt->addWidget(cancelButton);
    setLayout(lyt);
}

void ProgressWidget::setFormat(const QString &format)
{
    progressBar->setFormat(format);
}

void ProgressWidget::setRange(int minimum, int maximum)
{
    progressBar->setRange( minimum, maximum);
}

void ProgressWidget::setValue( int val)
{
    progressBar->setValue( val);
}
