/**
 *
 *	Connor Murphy, 2022
 * 
 **/

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "RenderWindow.hpp"
#include "Entity.hpp"
#include "KeyMap.hpp"
#include "Utils.hpp"
#include "Block.hpp"


int main(int argc, char* args[]) {
	
	// initialize SDL library
	if (SDL_Init(SDL_INIT_VIDEO)) {
		std::cout << "SDL intialization failed. SDL error: " << SDL_GetError() << std::endl;
	}

	// initialize SDL image library
	if (!IMG_Init(IMG_INIT_PNG)) {
		std::cout << "Image initialization failed. SDL error: " << SDL_GetError() << std::endl;
	}

	// game setup
	char win_name[] = "Snake v0.0";
	int win_w = 256;
	int win_h = 240;
    int win_scale = 1;
	RenderWindow window = RenderWindow(win_name, win_w, win_h, win_scale);
    KeyMap keyboard = KeyMap();

    int block_scale = 4;    // 1 block = 2^4 by 2^4 pixels
    Vector2 spos = Vector2(6, 7);
    Vector2 pos = spos.scale2(block_scale);
	SDL_Texture* test_texture = window.loadTexture("res/img/test1.png");
    Block guy = Block(spos, test_texture, block_scale);

	// game loop
	bool game_running = true;
	SDL_Event event;
    SDL_Scancode scancode;
	while (game_running) {
		while (SDL_PollEvent(&event)) {
            // check for quit event
			if (event.type == SDL_QUIT) {
				game_running = false;
			}
            // check for button press
            if (event.type == SDL_KEYDOWN) {
                scancode = event.key.keysym.scancode;
                if (scancode == keyboard.f_back) {
                    game_running = false;
                }
                if (scancode == keyboard.f_up && spos.f_y > 0) {
                    guy.incrementSY(-1);
                }
                if (scancode == keyboard.f_down  && spos.f_y < 14) {
                    guy.incrementSY(1);
                }
                if (scancode == keyboard.f_left && spos.f_x > 0) {
                    guy.incrementSX(-1);
                }
                if (scancode == keyboard.f_right && spos.f_x < 15) {
                    guy.incrementSX(1);
                }
            }     
        }
 	
 		window.clear();

        window.render(guy);
        spos = guy.getSPos();
        pos = guy.getPos();
        guy.printPos(0);


 		window.display();
	}

	// close game
	window.close();
	SDL_Quit();
	return 0;
}