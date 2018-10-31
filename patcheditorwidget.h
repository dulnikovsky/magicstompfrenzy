#ifndef PATCHEDITORWIDGET_H
#define PATCHEDITORWIDGET_H

#include "arraydataeditwidget.h"

class QLineEdit;

class PatchEditorWidget : public ArrayDataEditWidget
{
    Q_OBJECT
public:
    explicit PatchEditorWidget(QWidget *parent = nullptr);

signals:

public slots:
};

#endif // PATCHCOMMONEDITOR_H
