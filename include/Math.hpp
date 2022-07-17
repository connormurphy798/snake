#pragma once

#include <stdlib.h>
#include <iostream>

struct Vector2 {
    Vector2();

    Vector2(int x, int y);

    bool operator==(Vector2 v);

    bool operator!=(Vector2 v);

    Vector2 operator+(Vector2 v);

    Vector2 operator-(Vector2 v);

    int operator*(Vector2 v);

    inline Vector2 scale2(int n) {
        return Vector2(f_x << n, f_y << n);
    };

    void printCoords();

    int f_x;
    int f_y;
};
