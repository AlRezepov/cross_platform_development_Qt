#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->bt_start_stop->setText("Старт");
    ui->bt_clear->setText("Очистить");
    ui->lb_time->setText("00:00:00.0");
    ui->bt_circle->setText("Круг");

    stopwatch = new Stopwatch(this);
    lapNumber = 0;

    connect(ui->bt_start_stop, &QPushButton::clicked, this, &MainWindow::onStartStopClicked);
    connect(ui->bt_clear, &QPushButton::clicked, this, &MainWindow::onResetClicked);
    connect(ui->bt_circle, &QPushButton::clicked, this, &MainWindow::onLapClicked);
    connect(stopwatch, &Stopwatch::timeChanged, this, &MainWindow::updateTime);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete stopwatch;
}

void MainWindow::updateTime(qint64 time)
{
    ui->lb_time->setText(QTime(0, 0).addMSecs(time).toString("hh:mm:ss.zzz"));
}

void MainWindow::onStartStopClicked()
{
    if (stopwatch->isRunning()) {
        stopwatch->stop();
        ui->bt_start_stop->setText("Старт");
        ui->bt_circle->setEnabled(false);
    } else {
        stopwatch->start();
        ui->bt_start_stop->setText("Стоп");
        ui->bt_circle->setEnabled(true);
    }
}

void MainWindow::onResetClicked()
{
    stopwatch->reset();
    ui->lb_time->setText("00:00:00.0");
    ui->br_circle->clear();
    lapNumber = 0;
    ui->bt_circle->setEnabled(false);
}

void MainWindow::onLapClicked()
{
    if (stopwatch->isRunning()) {
        qint64 currentTime = QDateTime::currentMSecsSinceEpoch();
        qint64 lapTime;
        if (lapNumber == 0) {
            lapTime = currentTime - stopwatch->getStartTime();
        } else {
            lapTime = currentTime - lastLapTime;
        }
        lastLapTime = currentTime;
        lapNumber++;
        ui->br_circle->append(QString("Круг %1, время: %2 сек").arg(lapNumber).arg(QTime(0, 0).addMSecs(lapTime).toString("hh:mm:ss.zzz")));
    }
}
