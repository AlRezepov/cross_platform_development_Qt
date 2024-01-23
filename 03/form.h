#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include "dialog.h"

namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = nullptr);
    ~Form();

private slots:
    void on_pb_ok_clicked();

private:
    Ui::Form *ui;
    Dialog* dialog;
};

#endif // FORM_H
