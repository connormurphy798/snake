#pragma once

#include <iostream>

struct Vector2 {
    Vector2();

    Vector2(int p_x, int p_y);

    void printCoords();

    int f_x;
    int f_y;
};