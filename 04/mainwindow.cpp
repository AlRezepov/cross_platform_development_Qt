#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->gb_radioButton->setTitle("Группа Радио Кнопок");

    ui->rb_first->setText("Радио_Кнопка_01");
    ui->rb_second->setText("Радио_Кнопка_02");

    for (int i = 0; i < 10; ++i) {
        ui->cb_list->addItem("Позиция: " + QString::number(i));
    }

    ui->pb_button->setText("Нажми на меня");
    ui->pb_button->setCheckable(true);

    ui->pb_progres->setMinimum(0);
    ui->pb_progres->setMaximum(10);
    ui->pb_progres->setValue(0);

    count = 0;

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pb_button_clicked()
{
    count +=1;
    ui->pb_progres->setValue(count);

    if (count > 10){
        count = 0;
        ui->pb_progres->setValue(count);
    }
}

