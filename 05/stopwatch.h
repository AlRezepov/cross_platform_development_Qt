#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <QObject>
#include <QTimer>

class Stopwatch : public QObject
{
    Q_OBJECT
public:
    explicit Stopwatch(QObject *parent = nullptr);

    void start();
    void stop();
    void reset();
    bool isRunning();
    qint64 elapsed();
    qint64 lapTime();

signals:
    void timeChanged(qint64 time);

public slots:
    void lap();

private slots:
    void updateTimer();

private:
    qint64 startTime;
    qint64 lastLapTime;
    bool running;
    QTimer timer;
};

#endif // STOPWATCH_H
