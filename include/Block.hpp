#pragma once

#include <SDL2/SDL.h>
#include <iostream>

#include "Entity.hpp"
#include "Math.hpp"
#include "Utils.hpp"

class Block : public Entity {
public:
    Block();

    Block(Vector2 p_spos, SDL_Texture* p_texture, int p_scale2);

    Vector2& getSPos();

    void setSPos(Vector2 p_spos);

    int incrementSX(int p_dx);

    int incrementSY(int p_dy);

    Vector2& incrementSPos(Vector2 p_d);

    Vector2& incrementSPos(Vector2 p_d, const int* p_limits); // {T, B, L, R}

    void printPos(int p_pos_type);

protected:
    Vector2 f_spos;
    int     f_scale2;

private:
    inline void updateX() {
        f_pos.f_x = f_spos.f_x << f_scale2; 
    }

    inline void updateY() {
        f_pos.f_y = f_spos.f_y << f_scale2;
    }

    inline void updatePos() {
        f_pos = f_spos.scale2(f_scale2);
    }
};