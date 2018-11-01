#ifndef PATCHEDITORWIDGET_H
#define PATCHEDITORWIDGET_H

#include "arraydataeditwidget.h"

class QVBoxLayout;
class QLabel;

class PatchEditorWidget : public ArrayDataEditWidget
{
    Q_OBJECT
public:
    explicit PatchEditorWidget(QWidget *parent = nullptr);

    void setDataArray(QByteArray *arr) override;

private:
    QVBoxLayout *mainLayout;
    QWidget *effectEditWidget;
    QLabel *copyrightLabel;
    constexpr static const char *copyrightStr="MagicstompFrenzy (C) 2018 Robert Vetter";
};

#endif // PATCHCOMMONEDITOR_H
