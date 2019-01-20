#include "importbankselectiondialog.h"

#include <QRadioButton>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QApplication>
#include <QStyle>
#include <QFileDialog>
#include <QStandardPaths>
#include <QDialogButtonBox>

ImportBankSelectionDialog::ImportBankSelectionDialog(QWidget *parent) : QDialog(parent)
{

    setWindowTitle(tr("Import Patches from Standard MIDI File"));

    QVBoxLayout *layout= new QVBoxLayout();

    QHBoxLayout *hlayout = new QHBoxLayout();
    hlayout->addWidget( new QLabel(tr("Choose file to import: ")));
    hlayout->addWidget( fileNameEdit = new QLineEdit());

    QStyle *style= qApp->style();

    QPushButton *startFileDialogButton = new QPushButton(style->standardIcon(QStyle::SP_DriveHDIcon), QString());
    connect(
        startFileDialogButton, &QPushButton::clicked,
        [=]() {

        QString fileName = QFileDialog::getOpenFileName(this, tr("Open SMF File"),
                                                        QStandardPaths::writableLocation(QStandardPaths::HomeLocation),
                                                        tr("Standard MIDI Files (*.mid)"));

        if(fileName.isEmpty())
            return;
        fileNameEdit->setText(fileName);
    }
    );


    hlayout->addWidget( startFileDialogButton);

    layout->addLayout(hlayout);

    QGroupBox *groupBox = new QGroupBox(tr("Choose Tab where imported patches will be written:"));
    QVBoxLayout *groupLayout= new QVBoxLayout();

    userRadio = new QRadioButton(tr("&User Patches Tab"));
    groupLayout->addWidget(userRadio);
    importedRadio = new QRadioButton(tr("&Imported Patches Tab"));
    groupLayout->addWidget(importedRadio);
    importedRadio->setChecked(true);

    groupBox->setLayout(groupLayout);

    layout->addWidget( groupBox);

    QDialogButtonBox *buttonBox = new QDialogButtonBox(Qt::Horizontal);
    buttonBox->addButton(new QPushButton(tr("Import")), QDialogButtonBox::AcceptRole);
    buttonBox->addButton(new QPushButton(tr("Cancel")), QDialogButtonBox::RejectRole);
    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

    layout->addWidget( buttonBox);

    setLayout( layout );
}

QString ImportBankSelectionDialog::fileName() const
{
    return fileNameEdit->text();
}

ImportBankSelectionDialog::TabSelection ImportBankSelectionDialog::SelectedTab() const
{
    return importedRadio->isChecked()?ImportTab:UserTab;
}
