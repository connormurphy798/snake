#pragma once

#include <SDL2/SDL.h>
#include <stdlib.h>
#include <assert.h>
#include <unordered_set>

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

    inline int vectorToBlockNum(Vector2 p_v, int p_w) {
        return p_w * p_v.f_y + p_v.f_x;
    }

    inline Vector2 blockNumToVector(int p_block, int p_w) {
        return Vector2(p_block % p_w, p_block / p_w);
    }

    template <class T>
    inline T randElementInSet(const std::unordered_set<T>* p_set) {
        int random = rand() % p_set->size();
        auto iter = p_set->begin();
        for (int i=0; i<random; i++) {
            iter++;
        }
        return *iter;
    }
};