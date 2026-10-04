#include "PomodoroTimer.h"

void PomodoroTimer::configure(int workSeconds, int breakSeconds) {
  if(workSeconds <= 0) return;

    workTime = workSeconds;

  if(breakSeconds == -1) {
    proportionCalculation();
  }

  else {
    breakTime = breakSeconds;
  }

  secondsLeft = workTime;
  currentPhase = Phase::Work;
}

PomodoroTimer::PomodoroTimer (int workSeconds, int breakSeconds) 
{
      configure(workSeconds, breakSeconds);
}

void PomodoroTimer::start() {
  isTimerGoing = true;
}

void PomodoroTimer::pause() {
  isTimerGoing = false;
}

void PomodoroTimer::reset() {
  configure(workTime, breakTime);
  isTimerGoing = false;
}

void PomodoroTimer::tick() {
  if(isTimerGoing) {
    if(secondsLeft > 0) {
      secondsLeft--;
    }

    if(secondsLeft == 0) {
      currentPhase = (currentPhase == Phase::Work) ? Phase::Break : Phase::Work;
      secondsLeft = (currentPhase == Phase::Work) ? workTime : breakTime;
      
      if(onPhaseFinished) {
        onPhaseFinished(currentPhase);
      }
    }
  }
}

int PomodoroTimer::getSecondsLeft() const {
  return secondsLeft;
}

void PomodoroTimer::proportionCalculation() {
    breakTime = calculateProportionalBreak(workTime);
}

int PomodoroTimer::calculateProportionalBreak(int workSeconds) {
    return std::max(1, static_cast<int>(workSeconds * 0.2));
}