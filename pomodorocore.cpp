#include "pomodorocore.h"

#define DIGITS 2
#define BASE 10

PomodoroCore::PomodoroCore(int focusMinutes, int breakMinutes, int longMinutes, QObject *parent):
    QObject(parent), focusDuration(focusMinutes*60), breakDuration(breakMinutes *60),
    remainingSeconds(focusMinutes * 60), cycleCount(0), longDuration(longMinutes * 60), elapsedMs(0),
    currentSeconds(1)
{
    timer.setInterval(1000);
    connect(&timer, &QTimer::timeout, this, &PomodoroCore::tick);
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

void PomodoroCore::start() {
    stateController.start();

    if (!timer.isActive() && stateController.getState() == StateController::State::Running)
        timer.start();
    else{
        timer.stop();
    }

    if (cycleCount == 0){
        add1ToCycleCount();
    }
}

void PomodoroCore::pause(){
    stateController.pause();
    timer.stop();
}

void PomodoroCore::skipCycle(){
    switchCycle();
}

void PomodoroCore::reset(){
    stateController.reset();
    timer.stop();
    setRemainingSeconds(focusDuration);
    setCycleCount(0);
    emit updated();
}

void PomodoroCore::setCycleCount(int newCycleCount){
    cycleCount = newCycleCount;
}

void PomodoroCore::add1ToCycleCount(){
    cycleCount++;
}

int PomodoroCore::getCycleCount(){
    return cycleCount;
}

void PomodoroCore::tick(){
    if (stateController.getState() != StateController::State::Running){
        return;
    }

    emit updated();

    if (stateController.isElapsedTimerValid() && currentSeconds <=  0){
        stateController.setState(StateController::State::Finished);
        switchCycle();
        emit finished();
    }
}

QString PomodoroCore::cycleToString() const{
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

void PomodoroCore::setLongBreak(){
    stateController.setCycle(StateController::Cycle::LongBreak);
    stateController.setAccumulatedMs(0);
    stateController.pause();
    timer.stop();
    setRemainingSeconds(longDuration);
    emit updated();
}

void PomodoroCore::setBreakTime(){
    stateController.setCycle(StateController::Cycle::BreakTime);
    stateController.setAccumulatedMs(0);
    stateController.pause();
    timer.stop();
    setRemainingSeconds(breakDuration);
    emit updated();
}

void PomodoroCore::setFocusTime(){
    stateController.setCycle(StateController::Cycle::FocusTime);
    add1ToCycleCount();
    stateController.setAccumulatedMs(0);
    stateController.pause();
    timer.stop();
    setRemainingSeconds(focusDuration);
    emit updated();
}

void PomodoroCore::switchCycle(){

    StateController::Cycle cycle = stateController.getCycle();

    switch(cycle){
    case StateController::Cycle::FocusTime:{
        if (cycleCount % 4 == 0 && cycleCount != 0){
            setLongBreak();
            break;
        }
        else{
            setBreakTime();
            break;
        }
    }
    case StateController::Cycle::BreakTime:
        setFocusTime();
        break;
    case StateController::Cycle::LongBreak:
        setFocusTime();
        break;
    }
}

int PomodoroCore::getCurrentSeconds() const{
    return currentSeconds;
}

int PomodoroCore::setRemainingSeconds(int newRemainingSeconds){
    return remainingSeconds = newRemainingSeconds;
}
