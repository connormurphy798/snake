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
	const int win_w = 256;
	const int win_h = 240;
    const int win_scale = 1;
	RenderWindow window = RenderWindow(win_name, win_w, win_h, win_scale);
    
    const int block_scale = 4;    // 1 block = 2^4 by 2^4 pixels
    const int win_block_w = win_w >> block_scale;
    const int win_block_h = win_h >> block_scale;
    const int block_limits[4] = {0, win_block_h-1, 0, win_block_w-1};

    Vector2 spos = Vector2(3, 11); // position scaled to block size
    Vector2 pos = spos.scale2(block_scale);
	SDL_Texture* test_texture = window.loadTexture("res/img/test1.png");
    int snake_size = 4;
    Block snake[snake_size] = {
        Block(spos, test_texture, block_scale),
        Block(spos, test_texture, block_scale),
        Block(spos, test_texture, block_scale),
        Block(spos, test_texture, block_scale)
    };
    KeyMap keyboard = KeyMap();

	// game loop
    unsigned long long curr_time = 0;
    unsigned long long next_time = 0;
    float timestep = 5.0f;  // position updates every 1.0/timestep seconds 

	bool game_running = true;
    Vector2 svel = Vector2(0,0);
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
                    svel = Vector2(0,-1);
                }
                if (scancode == keyboard.f_down  && spos.f_y < win_block_h-1) {
                    svel = Vector2(0,1);
                }
                if (scancode == keyboard.f_left && spos.f_x > 0) {
                    svel = Vector2(-1,0);
                }
                if (scancode == keyboard.f_right && spos.f_x < win_block_w-1) {
                    svel = Vector2(1,0);
                }
            }     
        }

        next_time = (unsigned long long) (Utils::upTimeSeconds() * timestep);
        // limit update rate
        if (next_time > curr_time) {
            // update body blocks from back to front
            for (int i=snake_size; i>0; i--) {
                snake[i].setSPos(snake[i-1].getSPos());
            }
            // update head
            snake[0].incrementSPos(svel, block_limits);
            curr_time = next_time;
        }

 		window.clear();

        for (int i=0; i<snake_size; i++) {
            window.render(snake[i]);
        } 
        spos = snake[0].getSPos();
        pos = snake[0].getPos();
        


 		window.display();
	}

	// close game
	window.close();
	SDL_Quit();
	return 0;
}