#include "stopwatch.h"
#include <QDateTime>

Stopwatch::Stopwatch(QObject *parent) : QObject(parent), running(false), lastStopTime(0)
{
    connect(&timer, &QTimer::timeout, this, &Stopwatch::updateTimer);
}

void Stopwatch::start()
{
    if (!running)
    {
        if (lastStopTime == 0) {
            startTime = QDateTime::currentMSecsSinceEpoch();
        } else {
            qint64 elapsedSinceLastStop = QDateTime::currentMSecsSinceEpoch() - lastStopTime;
            startTime += elapsedSinceLastStop;
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
        lastStopTime = QDateTime::currentMSecsSinceEpoch();
    }
}

void Stopwatch::reset()
{
    startTime = 0;
    lastStopTime = 0;
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
        return lastStopTime - startTime;
    }
}

void Stopwatch::updateTimer()
{
    if (running)
    {
        emit timeChanged(elapsed());
    }
}

qint64 Stopwatch::getStartTime()
{
    return startTime;
}

