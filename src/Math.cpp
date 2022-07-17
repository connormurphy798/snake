#include "Math.hpp"

Vector2::Vector2() : f_x(0), f_y(0) {};

Vector2::Vector2(int x, int y) : f_x(x), f_y(y) {};

bool Vector2::operator==(Vector2 v) {
    return (f_x == v.f_x) && (f_y == v.f_y); 
}

bool Vector2::operator!=(Vector2 v) {
    return !((f_x == v.f_x) && (f_y == v.f_y)); 
}

Vector2 Vector2::operator+(Vector2 v) {
    int x = f_x + v.f_x;
    int y = f_y + v.f_y;
    return Vector2(x, y);
}

int Vector2::operator*(Vector2 v) {
    return f_x*v.f_x + f_y*v.f_y;
}

Vector2 Vector2::operator-(Vector2 v) {
    int x = f_x - v.f_x;
    int y = f_y - v.f_y;
    return Vector2(x, y);
}

void Vector2::printCoords() {
    std::cout << f_x << ", " << f_y << std::endl;
}


