#pragma once

#include <SDL2/SDL.h>

namespace Utils {
    inline float upTimeSeconds() {
        return SDL_GetTicks() * 0.001f; 
    }
};