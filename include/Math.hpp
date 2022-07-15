#pragma once

#include <iostream>

struct Vector2 {
    Vector2();

    Vector2(int p_x, int p_y);

    inline Vector2 scale2(int p_n) {
        return Vector2(f_x << p_n, f_y << p_n);
    };

    void printCoords();

    int f_x;
    int f_y;
};