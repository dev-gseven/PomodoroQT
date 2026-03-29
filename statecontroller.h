#ifndef STATECONTROLLER_H
#define STATECONTROLLER_H

#include <QElapsedTimer>
//#include <QDebug>

class StateController
{
public:
    enum class State{
        Idle, Running, Paused, Finished,
    };
    enum class Cycle{
        FocusTime, BreakTime, LongBreak
    };

    void start();
    void pause();
    void reset();

    State getState() const;
    Cycle getCycle() const;

    void setCycle(Cycle newCycle);
    void setState(State newState);

    qint64 getElapsedMs();
    qint64 getAccumulatedMs();

    void setAccumulatedMs(qint64 newTime);

    bool isElapsedTimerValid();

    StateController();

private:
    QElapsedTimer elapsedTimer;
    State currentState;
    Cycle currentCycle;
    qint64 accumulatedMs;
};

#endif // STATECONTROLLER_H
