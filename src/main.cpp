/**
 *
 *	Connor Murphy, 2022
 * 
 **/

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <unordered_set>

#include "RenderWindow.hpp"
#include "Entity.hpp"
#include "KeyMap.hpp"
#include "Utils.hpp"
#include "Block.hpp"


template <class T>
void printNotInSet(const std::unordered_set<T>* p_set, const T* p_elements, int p_num) {
    for (int i=0; i<p_num; i++) {
        if (!p_set->count(p_elements[i])) {
            std::cout << p_elements[i] << " not in provided set" << std::endl; 
        }
    }
    std::cout << "all elements checked\n" << std::endl;
}



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
    char win_name[] = "Snake v0.2";
    const int win_w = 256;
    const int win_h = 240;
    const int win_scale = 1;
    RenderWindow window = RenderWindow(win_name, win_w, win_h, win_scale);
    
    const int block_scale = 4;    // 1 block = 2^4 by 2^4 pixels
    const int win_block_w = win_w >> block_scale;   
    const int win_block_h = win_h >> block_scale;
    const int num_blocks = win_block_h * win_block_w;
    const int block_limits[4] = {0, win_block_h-1, 0, win_block_w-1};

    // initialize the snake
    Vector2 head_spos = Vector2(3, 11); // position scaled to block size
    SDL_Texture* snake_texture = window.loadTexture("res/img/test1.png");
    int snake_size = 1;
    Block* snake = (Block*) malloc(num_blocks * sizeof(Block));
    snake[0] = Block(head_spos, snake_texture, block_scale);

    // create set of available blocks, 0 to num_blocks-1
    std::unordered_set<unsigned short> available_blocks;
    for (unsigned short i=0; i<num_blocks; i++) {
        available_blocks.insert(i);
    }
    available_blocks.erase(Utils::vectorToBlockNum(head_spos, win_block_w));


    // generate random food position
    Vector2 food_spos = Utils::blockNumToVector(Utils::randElementInSet(&available_blocks), win_block_w);
    SDL_Texture* food_texture = window.loadTexture("res/img/test2.png");
    Block food = Block(food_spos, food_texture, block_scale);

    KeyMap keyboard = KeyMap();

	// game loop
    unsigned long long curr_time = 0;
    unsigned long long next_time = 0;
    float timestep = 10.0f;  // position updates every 1.0/timestep seconds 

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
                if (scancode == keyboard.f_up && head_spos.f_y > 0) {
                    svel = Vector2(0,-1);
                }
                if (scancode == keyboard.f_down  && head_spos.f_y < win_block_h-1) {
                    svel = Vector2(0,1);
                }
                if (scancode == keyboard.f_left && head_spos.f_x > 0) {
                    svel = Vector2(-1,0);
                }
                if (scancode == keyboard.f_right && head_spos.f_x < win_block_w-1) {
                    svel = Vector2(1,0);
                }
            }     
        }

        next_time = (unsigned long long) (Utils::upTimeSeconds() * timestep);
        // limit update rate
        if (next_time > curr_time) {
            // update body blocks from back to front
            available_blocks.insert(Utils::vectorToBlockNum(snake[snake_size-1].getSPos(), win_block_w));
            for (int i=snake_size-1; i>0; i--) {
                snake[i].setSPos(snake[i-1].getSPos());
            }

            // update head
            snake[0].incrementSPos(svel, block_limits);
            head_spos = snake[0].getSPos();
            available_blocks.erase(Utils::vectorToBlockNum(head_spos, win_block_w));

            // handle eating
            if (head_spos == food.getSPos()) {
                food.setSPos(Utils::blockNumToVector(Utils::randElementInSet(&available_blocks), win_block_w));
                snake[snake_size] = Block(snake[snake_size-1].getSPos(), snake_texture, block_scale);
                snake_size++;
                if (snake_size == num_blocks) {
                    game_running = false;
                }
            }

            curr_time = next_time;
        }

 		window.clear();

        for (int i=0; i<snake_size; i++) {
            window.render(snake[i]);
        } 

        window.render(food);

 		window.display();
	}

	// close game
    free(snake);
	window.close();
	SDL_Quit();
	return 0;
}