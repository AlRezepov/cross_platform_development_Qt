#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "stopwatch.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

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
    void updateTime(qint64 time);

private:
    Ui::MainWindow *ui;
    Stopwatch *stopwatch;
    int lapNumber;
    qint64 lastLapTime;
};

#endif // MAINWINDOW_H
