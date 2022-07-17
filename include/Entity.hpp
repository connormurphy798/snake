#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Math.hpp"

class Entity {
public:
    Entity();

    Entity(Vector2 pos, SDL_Texture* texture);

    Entity(Vector2 pos, SDL_Texture* texture, Vector2 texture_offset, Vector2 texture_size);

    Vector2& getPos();

    void setPos(Vector2 pos);

	SDL_Rect getCurrentFrame();

    void setCurrentFrame(Vector2 offset, Vector2 size);

	SDL_Texture* getTexture();

protected:
	Vector2         f_pos;
	SDL_Rect		f_current_frame;
	SDL_Texture*	f_texture;
};