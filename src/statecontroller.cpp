#include "statecontroller.h"

StateController::StateController():currentState(State::Paused),currentCycle(Cycle::FocusTime),accumulatedMs(0){}

void StateController::start(){
    if (currentState != State::Running){
        currentState = State::Running;
        elapsedTimer.start();
    }
    else {
        StateController::pause();
        accumulatedMs += elapsedTimer.elapsed();
    }
}

void StateController::pause(){
    currentState = State::Paused;
}

void StateController::reset(){
    currentState = State::Paused;
    currentCycle = Cycle::FocusTime;
    accumulatedMs = 0;
}

bool StateController::isElapsedTimerValid() const{
    return elapsedTimer.isValid();
}

void StateController::setAccumulatedMs(qint64 newTime){
    accumulatedMs = newTime;
}

qint64 StateController::getAccumulatedMs() const{
    return accumulatedMs;
}

qint64 StateController::getElapsedMs() const{
    return elapsedTimer.elapsed();
}

void StateController::setCycle(const Cycle &newCycle){
    currentCycle = newCycle;
}

void StateController::setState(const State &newState){
    currentState = newState;
}

StateController::State StateController::getState() const{
    return currentState;
}

StateController::Cycle StateController::getCycle() const{
    return currentCycle;
}
