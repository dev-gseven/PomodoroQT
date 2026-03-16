#include "pomodorocore.h"

#define DIGITS 2
#define BASE 10



PomodoroCore::PomodoroCore(int focusMinutes, int breakMinutes, int longMinutes):
    focusDuration(focusMinutes*60),breakDuration(breakMinutes *60),
    remainingSeconds(focusMinutes * 60),cycleCount(0), longDuration(longMinutes * 60), isFinished(false){}

QString PomodoroCore::updateUI(){
    int seconds = remainingSeconds;

    int mins = seconds / 60;
    int secs = seconds % 60;

    return QString("%1:%2").arg (mins, DIGITS, BASE, QChar('0')).arg(secs, DIGITS, BASE, QChar('0'));

}

void  PomodoroCore::start(){
    stateController.start(); //play/pause
    if (cycleCount == 0){
        add1ToCycleCount();
    }
}

void PomodoroCore::pause(){
    stateController.pause();
}

void PomodoroCore::skipCycle(){
    switchCycle();
    stateController.pause();
}

void PomodoroCore::reset(){
    stateController.reset();
    stateController.setCycle(StateController::Cycle::FocusTime);
    remainingSeconds = focusDuration;
    setCycleCount(0);
}

void PomodoroCore::setCycleCount(int newCycleCount){
    cycleCount = newCycleCount;
}

void PomodoroCore::add1ToCycleCount(){
    cycleCount++;
}

int PomodoroCore::getCycleCount() const{
    return cycleCount;
}

void PomodoroCore::tick(){
    if (stateController.getState() != StateController::State::Running){
        return;
    }
    if (remainingSeconds > 0){
        --remainingSeconds;
        //Atualizar UI por aqui, timerChanged()
    }
    if (remainingSeconds ==  0){
        stateController.setState(StateController::State::Finished);
        isFinished = true;
        switchCycle();
    }
}
QString PomodoroCore::cycleToString(){
    StateController::Cycle cycle = stateController.getCycle();
    switch (cycle){
    case StateController::Cycle::BreakTime:
        return "Break Time";
    case StateController::Cycle::FocusTime:
        return "Focus Time";
    case StateController::Cycle::LongBreak:
        return "Long Break";
    }

    return "Unknown";
}

void PomodoroCore::switchCycle(){

    StateController::Cycle cycle = stateController.getCycle();

    switch(cycle){
    case StateController::Cycle::FocusTime:{
        if (cycleCount % 4 == 0){
            stateController.setCycle(StateController::Cycle::LongBreak);
            remainingSeconds = longDuration;
            break;
        }
        else{
            stateController.setCycle(StateController::Cycle::BreakTime);
            remainingSeconds = breakDuration;
            break;
        }
    }
    case StateController::Cycle::BreakTime:
        stateController.setCycle(StateController::Cycle::FocusTime);
        remainingSeconds = focusDuration;
        add1ToCycleCount();
        break;
    case StateController::Cycle::LongBreak:
        stateController.setCycle(StateController::Cycle::FocusTime);
        remainingSeconds = focusDuration;
        add1ToCycleCount();
        break;
    }

}

int PomodoroCore::getRemainingSeconds() const{
    return remainingSeconds;
}
