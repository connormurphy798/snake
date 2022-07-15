#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Math.hpp"

class Entity {
public:
	Entity(int p_x, int p_y, SDL_Texture* p_texture);

    Entity(Vector2 p_pos, SDL_Texture* p_texture);

	int getX();

	int getY();

    Vector2& getPos();

    void setX(int p_x);

    void setY(int p_y);

    void setPos(Vector2 p_pos);

	SDL_Rect getCurrentFrame();

	SDL_Texture* getTexture();

private:
	Vector2         f_pos;
	SDL_Rect		f_current_frame;
	SDL_Texture*	f_texture;
};