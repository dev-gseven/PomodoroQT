#ifndef POMODOROCORE_H
#define POMODOROCORE_H

#include "statecontroller.h"
#include <QString>


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

    void setCycleCount(int newCycleCount);
    int getCycleCount() const;
    int getRemainingSeconds() const;

//    StateController::State getState() const;
//    StateController::Cycle getCycle() const;

private:
    int cycleCount;
    void switchCycle();
    int longDuration;
    int focusDuration;
    int breakDuration;
    int remainingSeconds;

    StateController stateController;
};

#endif // POMODOROCORE_H
