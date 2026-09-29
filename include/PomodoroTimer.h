#pragma once
#include <functional>

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

    int getSecondsLeft() const;

    std::function<void(Phase)> onPhaseFinished;

private:
    Phase currentPhase;

    int secondsLeft;
    bool isTimerGoing;
    int workTime;
    int breakTime;

    void proportionCalculation();
    
};
