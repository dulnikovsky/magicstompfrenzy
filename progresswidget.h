#ifndef PROGRESSWIDGET_H
#define PROGRESSWIDGET_H

#include <QWidget>

class QPushButton;
class QProgressBar;

class ProgressWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ProgressWidget(QWidget *parent = nullptr);
    void setFormat(const QString &format);
signals:
    void cancel();
public slots:
    void setRange(int minimum, int maximum);
    void setValue(int val);
private:
    QProgressBar *progressBar;
    QPushButton *cancelButton;
};

#endif // PROGRESSWIDGET_H
