#ifndef POMODOROCORE_H
#define POMODOROCORE_H

#include "statecontroller.h"
#include <QString>
//#include <QElapsedTimer>
//#include <QDebug>
//#include <QTimer>


class PomodoroCore
{
public:
    PomodoroCore(int focusMinutes, int breakMinutes, int longMinutes);

    void start();
    void pause();
    void reset();
    void skipCycle();
    void tick();
    void add1ToCycleCount();
    void windowFocus();
    QString cycleToString();
    QString updateUI();
    bool isFinished;
    //bool isTimeChanged;

    void setCycleCount(const int &newCycleCount);
    int getCycleCount() const;
    int getCurrentSeconds() const;
    int setRemainingSeconds(const int &newRemainingSeconds);
    qint64 getElapsedMs();

private:
    qint64 elapsedMs;
    int cycleCount;
    void switchCycle();
    int longDuration;
    int focusDuration;
    int breakDuration;
    int remainingSeconds;
    int currentSeconds;
//    qint64 accumulatedMs;

    //QTimer timer;
    //QElapsedTimer elapsedTimer;

    StateController stateController;
};

#endif // POMODOROCORE_H
