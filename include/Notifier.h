#pragma once
#include <string>
#include <utility> 

enum class SoundType { 
    BreakStart,
    BreakEnd 
};

class Notifier {
public:
    Notifier(std::string breakEndSound, std::string breakStartSound);
    void play(SoundType type) const;

private:
    std::string _breakEndSound;
    std::string _breakStartSound;
};

