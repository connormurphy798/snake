#include "RenderWindow.hpp"

RenderWindow::RenderWindow(const char* p_title, int p_width, int p_height, int p_scale) : f_window(NULL), f_renderer(NULL), f_scale(p_scale) {

	// initialize window
	f_window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, p_width << f_scale, p_height << f_scale, SDL_WINDOW_SHOWN);
	if (!f_window) {
		std::cout << "SDL failed to create window. Error: " << SDL_GetError() << std::endl;
	}

	// initialize renderer
	f_renderer = SDL_CreateRenderer(f_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!f_renderer) {
		std::cout << "SDL failed to create renderer. Error " << SDL_GetError() << std::endl;
	}

}


SDL_Texture* RenderWindow::loadTexture(const char* p_filepath) {
	SDL_Texture* texture = NULL;
	texture = IMG_LoadTexture(f_renderer, p_filepath);
	if (!texture) {
		std::cout << "Failed to load texture. Error: " << SDL_GetError() << std::endl;
	}
	return texture;
}


void RenderWindow::clear() {
	SDL_RenderClear(f_renderer);
}


void RenderWindow::render(Entity& p_entity) {
	SDL_Rect src = p_entity.getCurrentFrame();
	SDL_Rect dst;
    
	dst.x = p_entity.getPos().f_x << f_scale;
	dst.y = p_entity.getPos().f_y << f_scale;
	dst.w = src.w << f_scale;
	dst.h = src.h << f_scale;

	SDL_RenderCopy(f_renderer, p_entity.getTexture(), &src, &dst);
}


void RenderWindow::display() {
	SDL_RenderPresent(f_renderer);
}


void RenderWindow::close() {
	SDL_DestroyWindow(f_window);
	SDL_DestroyRenderer(f_renderer);
}