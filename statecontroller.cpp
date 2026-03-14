#include "statecontroller.h"
#include <QDebug>

StateController::StateController():currentState(State::Idle),currentCycle(Cycle::FocusTime){}

void StateController::start(){
    if (currentState == State::Idle || currentState == State::Paused || currentState == State::Finished){
        currentState = State::Running;
        //qDebug() << "Started!";
    }
    else StateController::pause();
}
// if finished, requestToAdd1();

void StateController::pause(){
    if (currentState == State::Running)
        currentState = State::Paused;
    //qDebug() << "Paused!";
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
    //qDebug() << "Idle!";
}

StateController::State StateController::getState() const{
    return currentState;
}

StateController::Cycle StateController::getCycle() const{
    return currentCycle;
}
