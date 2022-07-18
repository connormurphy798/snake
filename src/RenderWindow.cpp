#include "RenderWindow.hpp"

RenderWindow::RenderWindow(const char* title, int width, int height, int scale) : f_window(NULL), f_renderer(NULL), f_scale(scale) {

	// initialize window
	f_window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width << f_scale, height << f_scale, SDL_WINDOW_SHOWN);
	if (!f_window) {
		std::cout << "SDL failed to create window. Error: " << SDL_GetError() << std::endl;
	}

	// initialize renderer
	f_renderer = SDL_CreateRenderer(f_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!f_renderer) {
		std::cout << "SDL failed to create renderer. Error " << SDL_GetError() << std::endl;
	}

    // set background color
    SDL_SetRenderDrawColor(f_renderer, 55, 55, 55, 255);
    

}


SDL_Texture* RenderWindow::loadTexture(const char* filepath) {
	SDL_Texture* texture = NULL;
	texture = IMG_LoadTexture(f_renderer, filepath);
	if (!texture) {
		std::cout << "Failed to load texture. Error: " << SDL_GetError() << std::endl;
	}
	return texture;
}


void RenderWindow::clear() {
	SDL_RenderClear(f_renderer);
}


void RenderWindow::render(Entity& entity) {
	SDL_Rect src = entity.getCurrentFrame();
	SDL_Rect dst;
    
	dst.x = entity.getPos().f_x << f_scale;
	dst.y = entity.getPos().f_y << f_scale;
	dst.w = src.w << f_scale;
	dst.h = src.h << f_scale;

	SDL_RenderCopy(f_renderer, entity.getTexture(), &src, &dst);
}


void RenderWindow::display() {
	SDL_RenderPresent(f_renderer);
}


void RenderWindow::close() {
	SDL_DestroyWindow(f_window);
	SDL_DestroyRenderer(f_renderer);
}