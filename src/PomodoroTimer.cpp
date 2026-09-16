#include "PomodoroTimer.h"

PomodoroTimer::PomodoroTimer (int workSeconds, int breakSeconds) :
  workTime(std::move(workSeconds)), breakTime(std::move(breakSeconds)), currentPhase(Phase::Work),
  isTimerGoing(false), secondsLeft(0)
    {}




