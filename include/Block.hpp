#pragma once

#include <SDL2/SDL.h>

#include "Entity.hpp"
#include "Math.hpp"

class Block : public Entity {
public:
    Block();

    Block(Vector2 p_spos, SDL_Texture* p_texture);

    Vector2& getSPos();

    void setSPos(Vector2 p_spos);

protected:
    Vector2 f_spos;
};