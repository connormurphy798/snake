#pragma once

#include <SDL2/SDL.h>
#include <stdlib.h>
#include <assert.h>

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

    inline int mid(int p_a, int p_b, int p_c) { // dependent on that p_a < p_c OR p_b < p_c
        return min(max(p_a, p_b), p_c);
    }

    inline int log2(int p_n) {
        assert(p_n > 0);
        int log=0;
        while (p_n > 1) {
            p_n >>= 1;
            log++;
        }
        return log;
    }

    inline unsigned twoToThe(int p_n) {
        return 1 << p_n;
    }

    inline unsigned ones(int p_n) {
        return twoToThe(p_n) - 1;
    }

    inline Vector2 randVectorInSpace(int p_space_size, int p_log2w) {
        int rand_blocknum = rand() % p_space_size;
        return Vector2(rand_blocknum & Utils::ones(p_log2w), rand_blocknum >> p_log2w); // (blocknum % w, blocknum / w)
    }
};