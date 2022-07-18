#pragma once

#include <SDL2/SDL.h>
#include <stdlib.h>
#include <assert.h>
#include <unordered_set>

namespace Utils {
    inline float upTimeSeconds() {
        return SDL_GetTicks() * 0.001f; 
    }

    inline int max(int a, int b) {
        return (a > b) ? a : b;
    }

    inline int min(int a, int b) {
        return (a < b) ? a : b;
    }

    inline int mid(int a, int b, int c) { // dependent on that a < c OR b < c
        return min(max(a, b), c);
    }

    inline bool isEven(int n) {
        return ((n >> 1) << 1) == n;
    }

    inline int log2(int n) {
        assert(n > 0);
        int log=0;
        while (n > 1) {
            n >>= 1;
            log++;
        }
        return log;
    }

    inline unsigned twoToThe(int n) {
        return 1 << n;
    }

    inline unsigned ones(int n) {
        return twoToThe(n) - 1;
    }

    inline int vectorToBlockNum(Vector2 v, int w) {
        return w * v.f_y + v.f_x;
    }

    inline Vector2 blockNumToVector(int block, int w) {
        return Vector2(block % w, block / w);
    }

    template <class T>
    inline T randElementInSet(const std::unordered_set<T>* set) {
        int random = rand() % set->size();
        auto iter = set->begin();
        for (int i=0; i<random; i++) {
            iter++;
        }
        return *iter;
    }
};