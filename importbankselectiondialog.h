#ifndef IMPORTBANKSELECTIONDIALOG_H
#define IMPORTBANKSELECTIONDIALOG_H

#include <QDialog>

class QLineEdit;
class QRadioButton;

class ImportBankSelectionDialog : public QDialog
{
    Q_OBJECT
public:
    explicit ImportBankSelectionDialog(QWidget *parent = nullptr);

    QString fileName() const;

    enum TabSelection { UserTab, ImportTab };

    TabSelection SelectedTab() const;

private:
    QLineEdit *fileNameEdit;
    QRadioButton *userRadio;
    QRadioButton *importedRadio;
};

#endif // IMPORTBANKSELECTIONDIALOG_H
