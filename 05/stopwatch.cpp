#include "stopwatch.h"
#include <QDateTime>

Stopwatch::Stopwatch(QObject *parent) : QObject(parent), running(false), lastLapTime(0)
{
    connect(&timer, &QTimer::timeout, this, &Stopwatch::updateTimer);
}

void Stopwatch::start()
{
    if (!running)
    {
        if (lastLapTime == 0) {
            startTime = QDateTime::currentMSecsSinceEpoch();
        } else {
            startTime = QDateTime::currentMSecsSinceEpoch() - lastLapTime;
        }
        running = true;
        timer.start(100);
    }
}

void Stopwatch::stop()
{
    if (running)
    {
        running = false;
        timer.stop();
    }
}

void Stopwatch::reset()
{
    startTime = 0;
    lastLapTime = 0;
    running = false;
    timer.stop();
}

bool Stopwatch::isRunning()
{
    return running;
}

qint64 Stopwatch::elapsed()
{
    if (running)
    {
        return QDateTime::currentMSecsSinceEpoch() - startTime;
    }
    else
    {
        return lastLapTime;
    }
}

qint64 Stopwatch::lapTime()
{
    qint64 currentTime = QDateTime::currentMSecsSinceEpoch();
    return currentTime - startTime;
}

void Stopwatch::lap()
{
    if (running)
    {
        lastLapTime = QDateTime::currentMSecsSinceEpoch() - startTime;
        emit timeChanged(lastLapTime);
    }
}

void Stopwatch::updateTimer()
{
    if (running)
    {
        emit timeChanged(elapsed());
    }
}
