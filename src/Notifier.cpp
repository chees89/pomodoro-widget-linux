#include "Notifier.h"
#include <cstdlib>

Notifier::Notifier(std::string breakEndSound, std::string breakStartSound) : 
    _breakEndSound(std::move(breakEndSound)),
    _breakStartSound(std::move(breakStartSound))
    {}

void Notifier::play(SoundType type) const {
    if(type == SoundType::BreakStart) {
        std::string cmd = "paplay \"" + _breakStartSound + "\" &";
        std::system(cmd.c_str());
    }

    else if(type == SoundType::BreakEnd) {
        std::string cmd = "paplay \"" + _breakEndSound + "\" &";
        std::system(cmd.c_str());
    }
}
