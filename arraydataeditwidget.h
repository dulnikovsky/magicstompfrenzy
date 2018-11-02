#ifndef ARRAYDATAEDITWIDGET_H
#define ARRAYDATAEDITWIDGET_H

#include <QWidget>

class ArrayDataEditWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ArrayDataEditWidget( QWidget *parent = nullptr);

    QByteArray *DataArray() const { return dataArray; }
    virtual void setDataArray(QByteArray *arr);

    void refreshData(int offset, int length);

    static quint64 sevenToEight( const QByteArray &array, int offset, int length);
    static void eightToSeven( quint64 val, QByteArray &array, int offset, int length);

    constexpr static const char *dataOffsetProperty="offset";
    constexpr static const char *dataLenghtProperty="length";
    constexpr static const char *valuePropertyName="valuePropertyName";
    constexpr static const char *convertMethodProperty="convertMethod";

protected:
    bool event(QEvent *event) override;
    virtual bool writeEditedParameter(QObject *editor);

signals:
    void parameterChanged(int offset, int length);

private slots:
    void valueChanged();

private:
    QByteArray *dataArray;

    void connectObjectToValueChangedSlot( QObject *widget);

    bool parseConvertMethodString(const QString &sourceStr, QString &methodName, QStringList &srguments);

    QVariant invokeConvertMethod(const QString &method, const QByteArray *data, int offset, int length);

    bool invokeConvertMethodBackwards(const QString &method, const QVariant &value, QByteArray *data, int offset, int length);

    static double scaleAndAdd( double scalingFactor, double augend, double srcValue);
    static double addAndScale( double augend, double scalingFactor, double srcValue);
};

#endif // ARRAYDATAEDITWIDGET_H
