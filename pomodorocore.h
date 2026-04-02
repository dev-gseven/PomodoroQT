#ifndef POMODOROCORE_H
#define POMODOROCORE_H

#include "statecontroller.h"

#include <QString>
#include <QObject>
#include <QTimer>

class PomodoroCore : public QObject
{
    Q_OBJECT

public:
    PomodoroCore(int focusMinutes, int breakMinutes, int longMinutes, QObject *parent = nullptr);

    void start();
    void pause();
    void reset();
    void skipCycle();

    QString cycleToString();
    QString updateUI();

    int getCycleCount() const;

signals:
    void finished();
    void updated();

private:

    QTimer timer;
    qint64 elapsedMs;
    int cycleCount;
    int longDuration;
    int focusDuration;
    int breakDuration;
    int remainingSeconds;
    int currentSeconds;

    void add1ToCycleCount();
    void switchCycle();
    void setFocusTime();
    void setBreakTime();
    void setLongBreak();
    void tick();
    void setCycleCount(const int &newCycleCount);
    int setRemainingSeconds(const int &newRemainingSeconds);
    int getCurrentSeconds() const;
    qint64 getElapsedMs();

    StateController stateController;
};

#endif // POMODOROCORE_H
