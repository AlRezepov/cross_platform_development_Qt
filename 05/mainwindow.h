#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "stopwatch.h"

namespace Ui { class MainWindow; }

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onStartStopClicked();
    void onResetClicked();
    void onLapClicked();
    void updateTimer();

private:
    Ui::MainWindow *ui;
    Stopwatch *stopwatch;
    QTimer *timer;
    int lapNumber;
};

#endif // MAINWINDOW_H
