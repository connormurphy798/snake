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
void printNotInSet(const std::unordered_set<T>* set, const T* elements, int num) {
    for (int i=0; i<num; i++) {
        if (!set->count(elements[i])) {
            std::cout << elements[i] << " not in provided set" << std::endl; 
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
    char win_name[] = "Snake v0.4";
    const int win_w = 256;
    const int win_h = 240;
    const int win_scale = 1;
    RenderWindow window = RenderWindow(win_name, win_w, win_h, win_scale);
    
    const int block_size = 16;
    const int block_scale = Utils::log2(block_size);
    const int win_block_w = win_w >> block_scale;   
    const int win_block_h = win_h >> block_scale;
    const int num_blocks = win_block_h * win_block_w;

    // constants denoting texture positions on sprite sheet
    const Vector2 sprite_h_u  = Vector2( 0,  0);    const Vector2 sprite_h_d  = Vector2( 16,  0);
    const Vector2 sprite_h_l  = Vector2( 0,  16);   const Vector2 sprite_h_r  = Vector2( 16,  16);
    const Vector2 sprite_b_v  = Vector2( 0,  32);   const Vector2 sprite_b_h  = Vector2( 16,  32);
    const Vector2 sprite_b_r0 = Vector2( 0,  48);   const Vector2 sprite_b_r1 = Vector2( 16,  48);
    const Vector2 sprite_b_r2 = Vector2( 0,  64);   const Vector2 sprite_b_r3 = Vector2( 16,  64);
    const Vector2 block_dim = Vector2(block_size, block_size);

    // initialize the snake
    Vector2 head_spos = Vector2(5, 5); // position scaled to block size
    Vector2 head_spos_buffer;
    SDL_Texture* snake_sprites = window.loadTexture("res/img/snake_body.png");
    int snake_size = 3;
    Block* snake = (Block*) malloc(num_blocks * sizeof(Block));
    snake[0] = Block(head_spos,                  snake_sprites, sprite_h_r, block_dim, block_scale);
    snake[1] = Block(head_spos + Vector2(-1, 0), snake_sprites, sprite_b_h, block_dim, block_scale);
    snake[2] = Block(head_spos + Vector2(-2, 0), snake_sprites, sprite_h_l, block_dim, block_scale);


    // create set of available blocks, 0 to num_blocks-1
    std::unordered_set<unsigned short> available_blocks;
    for (unsigned short i=0; i<num_blocks; i++) {
        available_blocks.insert(i);
    }
    available_blocks.erase(Utils::vectorToBlockNum(head_spos,                  win_block_w));
    available_blocks.erase(Utils::vectorToBlockNum(head_spos + Vector2(-1, 0), win_block_w));
    available_blocks.erase(Utils::vectorToBlockNum(head_spos + Vector2(-2, 0), win_block_w));


    // generate random food position
    Vector2 food_spos = Utils::blockNumToVector(Utils::randElementInSet(&available_blocks), win_block_w);
    SDL_Texture* food_texture = window.loadTexture("res/img/test2.png");
    Block food = Block(food_spos, food_texture, block_scale);

    KeyMap keyboard = KeyMap();

	// game loop
    unsigned long long curr_time = 0;
    unsigned long long next_time = 0;
    float timestep = 10.0f;  // position updates every 1.0/timestep seconds 

    int dir = 0;
    const Vector2 zero_vec  = Vector2( 0,  0);
    const Vector2 dir_up    = Vector2( 0, -1);
    const Vector2 dir_down  = Vector2( 0,  1);
    const Vector2 dir_left  = Vector2(-1,  0);
    const Vector2 dir_right = Vector2( 1,  0);

    bool game_running = true;
    bool wall_collision = false;
    bool self_collision = false;
    bool ate = false;
    Vector2 svel = zero_vec;
    SDL_Event event;
    SDL_Scancode scancode;
	while (game_running) {
        if (SDL_PollEvent(&event)) {
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
                if (scancode == keyboard.f_up) {
                    dir = 1;
                }
                else if (scancode == keyboard.f_down) {
                    dir = 2;
                }
                else if (scancode == keyboard.f_left) {
                    dir = 3;
                }
                else if (scancode == keyboard.f_right) {
                    dir = 4;
                }
            }     
        }

        next_time = (unsigned long long) (Utils::upTimeSeconds() * timestep);
        // limit update rate
        if (next_time > curr_time) {
            // convert keyboard input into velocity
            if (dir == 1 && svel != dir_down) {
                svel = dir_up;
            }
            else if (dir == 2  && svel != dir_up) {
                svel = dir_down;
            }
            else if (dir == 3 && svel != dir_right) {
                svel = dir_left;
            }
            else if (dir == 4 && svel != dir_left) {
                svel = dir_right;
            }

            if (svel != zero_vec) {
                // calculate proposed new head + check collisions
                head_spos_buffer = head_spos + svel;
                wall_collision = (head_spos_buffer.f_x < 0) || (head_spos_buffer.f_x >= win_block_w) || (head_spos_buffer.f_y < 0) || (head_spos_buffer.f_y >= win_block_h);
                if (wall_collision) {
                    std::cout << "WALL COLLISION" << std::endl;
                    continue;
                }
                self_collision = available_blocks.find(Utils::vectorToBlockNum(head_spos_buffer, win_block_w)) == available_blocks.end() && svel != zero_vec;
                if (self_collision) {
                    std::cout << "SELF COLLISION" << std::endl;
                    continue;
                }

                // grow if ate on previous frame
                if (ate) {
                    snake[snake_size] = Block(snake[snake_size-1].getSPos(), snake_sprites, zero_vec, zero_vec, block_scale);
                    snake_size++;
                    if (snake_size == num_blocks) {
                        game_running = false;
                    }
                    ate = false;
                }

                // update body blocks from back to front
                available_blocks.insert(Utils::vectorToBlockNum(snake[snake_size-1].getSPos(), win_block_w));
                for (int i=snake_size-1; i>0; i--) {
                    snake[i].setSPos(snake[i-1].getSPos());
                }

                // update head position
                snake[0].setSPos(head_spos_buffer);
                head_spos = head_spos_buffer;
                available_blocks.erase(Utils::vectorToBlockNum(head_spos, win_block_w));

                // detect new eating
                if (head_spos == food.getSPos()) {
                    food.setSPos(Utils::blockNumToVector(Utils::randElementInSet(&available_blocks), win_block_w));
                    ate = true;  
                }

                // update sprite data in 4 steps
                // step 1: head (snake[0])
                if      (svel == dir_up)    snake[0].setCurrentFrame(sprite_h_u, block_dim);
                else if (svel == dir_down)  snake[0].setCurrentFrame(sprite_h_d, block_dim);
                else if (svel == dir_left)  snake[0].setCurrentFrame(sprite_h_l, block_dim);
                else if (svel == dir_right) snake[0].setCurrentFrame(sprite_h_r, block_dim);

                // step 2: body (snake[2:snake_size-1])
                for (int i=snake_size-2; i>1; i--) {
                    snake[i].setCurrentFrame(snake[i-1].getCurrentFrame());
                }

                // step 3: tail (snake[snake_size-1])
                Vector2 delta = snake[snake_size-2].getSPos() - snake[snake_size-1].getSPos();
                if      (delta == dir_up)    snake[snake_size-1].setCurrentFrame(sprite_h_d, block_dim);
                else if (delta == dir_down)  snake[snake_size-1].setCurrentFrame(sprite_h_u, block_dim);
                else if (delta == dir_left)  snake[snake_size-1].setCurrentFrame(sprite_h_r, block_dim);
                else if (delta == dir_right) snake[snake_size-1].setCurrentFrame(sprite_h_l, block_dim);

                // step 4: neck (snake[1])
                Vector2 a = snake[0].getSPos();
                Vector2 b = snake[2].getSPos();
                Vector2 ba = a-b;
                if (ba.f_x == 0 || ba.f_y == 0) {   // straight
                    if (ba.f_x == 0)
                        snake[1].setCurrentFrame(sprite_b_v, block_dim);
                    else
                        snake[1].setCurrentFrame(sprite_b_h, block_dim);
                } else {               // curved
                    int neck_y = snake[1].getSPos().f_y;
                    int min_y = Utils::min(a.f_y, b.f_y);
                    if (ba.f_x != ba.f_y) { // positive slope
                        if (neck_y == min_y)
                            snake[1].setCurrentFrame(sprite_b_r0, block_dim);
                        else
                            snake[1].setCurrentFrame(sprite_b_r3, block_dim);
                    } else {                // negative slope
                        if (neck_y == min_y)
                            snake[1].setCurrentFrame(sprite_b_r1, block_dim);
                        else
                            snake[1].setCurrentFrame(sprite_b_r2, block_dim);
                    }

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