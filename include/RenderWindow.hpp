#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "Entity.hpp"

class RenderWindow {
public:
	RenderWindow(const char* p_title, int p_width, int p_height);

	SDL_Texture* loadTexture(const char* p_filepath);

	void clear();

	void render(Entity& p_entity);

	void display();

	void close();

private:
	SDL_Window*		f_window;
	SDL_Renderer*	f_renderer;
};