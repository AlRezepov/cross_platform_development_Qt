#include "stopwatch.h"

Stopwatch::Stopwatch(QObject *parent) : QObject(parent), running(false) {}

void Stopwatch::start() {
    if (!running) {
        startTime = QDateTime::currentMSecsSinceEpoch();
        running = true;
    }
}

void Stopwatch::stop() {
    if (running) {
        running = false;
    }
}

void Stopwatch::reset() {
    startTime = 0;
    running = false;
}

bool Stopwatch::isRunning() {
    return running;
}

qint64 Stopwatch::elapsed() {
    if (running) {
        return QDateTime::currentMSecsSinceEpoch() - startTime;
    } else {
        return 0;
    }
}
