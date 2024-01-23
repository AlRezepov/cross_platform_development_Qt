#include "form.h"
#include "ui_form.h"

Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
    dialog = new Dialog(this);
}

Form::~Form()
{
    delete ui;
}

void Form::on_pb_ok_clicked()
{
    dialog->show();
}

