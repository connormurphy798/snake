#include "Math.hpp"

Vector2::Vector2() : f_x(0), f_y(0) {};

Vector2::Vector2(int p_x, int p_y) : f_x(p_x), f_y(p_y) {};

Vector2 Vector2::operator+(Vector2 p_a) {
    int x = f_x + p_a.f_x;
    int y = f_y + p_a.f_y;
    return Vector2(x, y);
}

void Vector2::printCoords() {
    std::cout << f_x << ", " << f_y << std::endl;
}