#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "qboxlayout.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    form = new Form(this);
    mainLayout->addWidget(form);

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}

