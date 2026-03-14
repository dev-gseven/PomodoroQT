#ifndef STATECONTROLLER_H
#define STATECONTROLLER_H


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
    StateController();

private:
    State currentState;
    Cycle currentCycle;
};

#endif // STATECONTROLLER_H
