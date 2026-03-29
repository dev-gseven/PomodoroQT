#include "pomodorocore.h"

#define DIGITS 2
#define BASE 10



PomodoroCore::PomodoroCore(int focusMinutes, int breakMinutes, int longMinutes):
    focusDuration(focusMinutes*60),breakDuration(breakMinutes *60),
    remainingSeconds(focusMinutes * 60),cycleCount(0), longDuration(longMinutes * 60), isFinished(false), elapsedMs(0),
    currentSeconds(1)
{

}

QString PomodoroCore::updateUI(){

    qint64 remainingSecondsMs = remainingSeconds * 1000;

    if(stateController.isElapsedTimerValid()){

        elapsedMs = stateController.getState() == StateController::State::Paused ? 0 : stateController.getElapsedMs();
        qint64 totalElapsedMs = stateController.getAccumulatedMs() + elapsedMs;
        qint64 remainingTimeMs = remainingSecondsMs - totalElapsedMs;
        qint64 seconds = remainingTimeMs / 1000;

        currentSeconds = seconds;
        qint64 mins = seconds / 60;
        qint64 secs = seconds % 60;

        return QString("%1:%2").arg (mins, DIGITS, BASE, QChar('0')).arg(secs, DIGITS, BASE, QChar('0'));
    }
    else{
        int seconds = remainingSeconds;
        int mins = seconds / 60;
        int secs = seconds % 60;

        return QString("%1:%2").arg (mins, DIGITS, BASE, QChar('0')).arg(secs, DIGITS, BASE, QChar('0'));
    }

}

void  PomodoroCore::start(){
    stateController.start();
    if (cycleCount == 0){
        add1ToCycleCount();
    }
}


void PomodoroCore::pause(){
    stateController.pause();
}

void PomodoroCore::skipCycle(){
    start();
    switchCycle();
}

void PomodoroCore::reset(){
    stateController.reset();
    setRemainingSeconds(focusDuration);
    setCycleCount(0);
}

void PomodoroCore::setCycleCount(const int &newCycleCount){
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

    if (stateController.isElapsedTimerValid() && currentSeconds <=  0){
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
    default:
        return "Unknown"; // should never reach here
    }
}

void PomodoroCore::switchCycle(){

    StateController::Cycle cycle = stateController.getCycle();

    switch(cycle){
    case StateController::Cycle::FocusTime:{
        if (cycleCount % 4 == 0 && cycleCount != 0){
            stateController.setCycle(StateController::Cycle::LongBreak);
            setRemainingSeconds(longDuration);
            stateController.setAccumulatedMs(0);
            start();
            stateController.pause();
            break;
        }
        else{
            stateController.setCycle(StateController::Cycle::BreakTime);
            setRemainingSeconds(breakDuration);
            stateController.setAccumulatedMs(0);
            start();
            stateController.pause();
            break;
        }
    }
    case StateController::Cycle::BreakTime:
        stateController.setCycle(StateController::Cycle::FocusTime);
        setRemainingSeconds(focusDuration);
        add1ToCycleCount();
        stateController.setAccumulatedMs(0);
        start();
        stateController.pause();
        break;
    case StateController::Cycle::LongBreak:
        stateController.setCycle(StateController::Cycle::FocusTime);
        setRemainingSeconds(focusDuration);
        add1ToCycleCount();
        stateController.setAccumulatedMs(0);
        start();
        stateController.pause();
        break;
    }
}

int PomodoroCore::getCurrentSeconds() const{
    return currentSeconds;
}

int PomodoroCore::setRemainingSeconds(const int &newRemainingSeconds){
    return remainingSeconds = newRemainingSeconds;
}
