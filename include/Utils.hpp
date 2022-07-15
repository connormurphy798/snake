#pragma once

#include <SDL2/SDL.h>

namespace Utils {
    inline float upTimeSeconds() {
        return SDL_GetTicks() * 0.001f; 
    }

    inline int max(int p_a, int p_b) {
        return (p_a > p_b) ? p_a : p_b;
    }

    inline int min(int p_a, int p_b) {
        return (p_a < p_b) ? p_a : p_b;
    }
};