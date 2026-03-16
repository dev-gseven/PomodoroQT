#ifndef POMODOROCORE_H
#define POMODOROCORE_H

#include "statecontroller.h"
#include <QString>
#include <QElapsedTimer>
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
    bool isFinished;
    QString updateUI();

    void setCycleCount(int newCycleCount);
    int getCycleCount() const;
    int getRemainingSeconds() const;

private:
    int cycleCount;
    void switchCycle();
    int longDuration;
    int focusDuration;
    int breakDuration;
    int remainingSeconds;

    //QTimer timer;
    QElapsedTimer timer;

    StateController stateController;
};

#endif // POMODOROCORE_H
