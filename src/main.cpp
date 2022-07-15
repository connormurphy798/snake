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
	int win_w = 512;	//  NES resolution, 
	int win_h = 480;	//	scaled up by 2
	RenderWindow window = RenderWindow(win_name, win_w, win_h);
    KeyMap keyboard = KeyMap();

    int x = 12;
    int y = 12;
	SDL_Texture* test_texture = window.loadTexture("res/img/test1.png");
    Entity guy = Entity(x, y, test_texture);


	// game loop
	bool game_running = true;
	SDL_Event event;
    SDL_Scancode scancode;
	while (game_running) {
		// poll for quit event
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				game_running = false;
			}
            if (event.type == SDL_KEYDOWN) {
                scancode = event.key.keysym.scancode;
                if (scancode == keyboard.f_back) {
                    game_running = false;
                }
            }     
        }
 	
 		window.clear();

        window.render(guy);

        std::cout << Utils::upTimeSeconds() << std::endl;

 		window.display();
	}

	// close game
	window.close();
	SDL_Quit();
	return 0;
}