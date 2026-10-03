#pragma once
#include <functional>
#include <algorithm>

enum class Phase {
  Work,
  Break
};

class PomodoroTimer {
public:
    PomodoroTimer(int workSeconds, int breakSeconds);
      
    void configure(int workSeconds, int breakSeconds);
    void start();
    void pause();
    void reset();
    void tick();

    static int calculateProportionalBreak(int workSeconds);
    int getSecondsLeft() const;

    std::function<void(Phase)> onPhaseFinished;

private:
    Phase currentPhase = Phase::Work;
    int secondsLeft = 0;
    bool isTimerGoing = false;
    int workTime = 0;
    int breakTime = 1;

    void proportionCalculation();
    
};
