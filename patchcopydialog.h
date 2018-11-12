#ifndef PATCHCOPYDIALOG_H
#define PATCHCOPYDIALOG_H

#include <QDialog>

class PatchListModel;
class QComboBox;
class PatchCopyDialog : public QDialog
{
    Q_OBJECT
public:
    explicit PatchCopyDialog(PatchListModel *model, const QString& patchToCopyName, QWidget *parent = nullptr);

    int targetPatchIndex() const;
private:
    QComboBox *targetPatchCombo;
};

#endif // PATCHCOPYDIALOG_H
