#include "PomodoroTimer.h"

void PomodoroTimer::configure(int workSeconds, int breakSeconds) {
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

PomodoroTimer::PomodoroTimer (int workSeconds, int breakSeconds) :
  isTimerGoing(false), secondsLeft(0)
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
