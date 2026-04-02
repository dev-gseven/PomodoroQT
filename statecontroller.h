#ifndef STATECONTROLLER_H
#define STATECONTROLLER_H

#include <QElapsedTimer>

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

    void setCycle(Cycle newCycle);
    void setState(State newState);

    void setAccumulatedMs(qint64 newTime);

    qint64 getElapsedMs();
    qint64 getAccumulatedMs();

    State getState() const;
    Cycle getCycle() const;

    bool isElapsedTimerValid();

    StateController();

private:
    QElapsedTimer elapsedTimer;

    State currentState;
    Cycle currentCycle;
    qint64 accumulatedMs;
};

#endif // STATECONTROLLER_H
