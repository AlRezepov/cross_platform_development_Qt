// mainwindow.cpp
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->bt_start_stop->setText("Старт");
    ui->bt_clear->setText("Cброс");
    ui->lb_time->setText("00:00:00.0");
    ui->bt_circle->setText("Круг");

    stopwatch = new Stopwatch(this);
    timer = new QTimer(this);
    lapNumber = 0;

    connect(ui->bt_start_stop, &QPushButton::clicked, this, &MainWindow::onStartStopClicked);
    connect(ui->bt_clear, &QPushButton::clicked, this, &MainWindow::onResetClicked);
    connect(ui->bt_circle, &QPushButton::clicked, this, &MainWindow::onLapClicked);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateTimer);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onStartStopClicked()
{
    if (stopwatch->isRunning()) {
        stopwatch->stop();
        ui->bt_start_stop->setText("Старт");
        timer->stop();
    } else {
        stopwatch->start();
        ui->bt_start_stop->setText("Стоп");
        timer->start(100);
    }
}

void MainWindow::onResetClicked()
{
    stopwatch->reset();
    ui->lb_time->setText("00:00:00.0");
    ui->br_circle->clear();
    lapNumber = 0;
}

void MainWindow::onLapClicked()
{
    if (stopwatch->isRunning()) {
        qint64 lapTime = stopwatch->elapsed();
        lapNumber++;
        ui->br_circle->append(QString("Круг %1, время: %2 сек").arg(lapNumber).arg(QTime::fromMSecsSinceStartOfDay(lapTime).toString("hh:mm:ss.zzz")));
    }
}

void MainWindow::updateTimer()
{
    qint64 time = stopwatch->elapsed();
    ui->lb_time->setText(QTime::fromMSecsSinceStartOfDay(time).toString("hh:mm:ss.zzz"));
}
