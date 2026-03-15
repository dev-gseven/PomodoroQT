#include "statecontroller.h"

StateController::StateController():currentState(State::Idle),currentCycle(Cycle::FocusTime){}

void StateController::start(){
    if (currentState == State::Idle || currentState == State::Paused || currentState == State::Finished){
        currentState = State::Running;
    }
    else StateController::pause();
}

void StateController::pause(){
    if (currentState == State::Running)
        currentState = State::Paused;
}

void StateController::setCycle(Cycle newCycle){
    currentCycle = newCycle;
}

void StateController::setState(State newState){
    currentState = newState;
}

void StateController::reset(){
    currentState = State::Idle;
    currentCycle = Cycle::FocusTime;
}

StateController::State StateController::getState() const{
    return currentState;
}

StateController::Cycle StateController::getCycle() const{
    return currentCycle;
}
