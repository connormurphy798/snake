#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "Entity.hpp"

class RenderWindow {
public:
	RenderWindow(const char* title, int width, int height, int scale);

	SDL_Texture* loadTexture(const char* filepath);

	void clear();

	void render(Entity& entity);

	void display();

	void close();

private:
	SDL_Window*		f_window;
	SDL_Renderer*	f_renderer;
    int             f_scale;        // display scaled by 2**f_scale
};