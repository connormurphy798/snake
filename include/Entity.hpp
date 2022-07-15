#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Math.hpp"

class Entity {
public:
    Entity();

    Entity(Vector2 p_pos, SDL_Texture* p_texture);

    Vector2& getPos();

    void setPos(Vector2 p_pos);

	SDL_Rect getCurrentFrame();

	SDL_Texture* getTexture();

protected:
	Vector2         f_pos;
	SDL_Rect		f_current_frame;
	SDL_Texture*	f_texture;
};