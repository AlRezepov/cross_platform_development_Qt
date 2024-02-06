#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <QObject>
#include <QTime>

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

private:
    qint64 startTime;
    bool running;
};

#endif // STOPWATCH_H
