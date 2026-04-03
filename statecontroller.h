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

    void setCycle(const Cycle &newCycle);
    void setState(const State &newState);

    qint64 getElapsedMs() const;
    qint64 getAccumulatedMs() const;

    void setAccumulatedMs(qint64 newTime);

    State getState() const;
    Cycle getCycle() const;

    bool isElapsedTimerValid() const;

    StateController();

private:
    QElapsedTimer elapsedTimer;

    State currentState;
    Cycle currentCycle;
    qint64 accumulatedMs;
};

#endif // STATECONTROLLER_H
