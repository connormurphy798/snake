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


enum State {e_initial, e_playing, e_won, e_lost};


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
    char win_name[] = "Snake v1.0";
    const int win_w = 256;
    const int win_h = 240;
    const int win_scale = 1;
    RenderWindow window = RenderWindow(win_name, win_w, win_h, win_scale);
    Entity frame = Entity(Vector2(0,0), window.loadTexture("res/img/frame.png"));
    frame.setCurrentFrame(Vector2(0,0), Vector2(win_w, win_h));
    Entity top_text = Entity(Vector2(16, 16), window.loadTexture("res/img/controls.png"));
    top_text.setCurrentFrame(Vector2(0,0), Vector2(win_w * 7 / 8, win_h * 2 / 15));
    
    const int block_size = 16;
    const int block_scale = Utils::log2(block_size);
    const int win_block_w = win_w >> block_scale;   
    const int win_block_h = win_h >> block_scale;
    const int num_blocks = win_block_h * win_block_w;
    const int frame_limits[4] = {4, 14, 0, 15};

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
    for (unsigned short i=frame_limits[2]+1; i<frame_limits[3]; i++) {
        for (unsigned short j=frame_limits[0]+1; j<frame_limits[1]; j++) {
            available_blocks.insert(Utils::vectorToBlockNum(Vector2(i,j), win_block_w));
        }
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

    const Vector2 zero_vec  = Vector2( 0,  0);
    const Vector2 dir_up    = Vector2( 0, -1);
    const Vector2 dir_down  = Vector2( 0,  1);
    const Vector2 dir_left  = Vector2(-1,  0);
    const Vector2 dir_right = Vector2( 1,  0);

    bool game_running = true;
    bool wall_collision = false;
    bool self_collision = false;
    bool ate = false;
    State game_state = e_initial;
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
                if (game_state == e_initial || game_state == e_playing) {
                    if (scancode == keyboard.f_up && snake[0].getSPos() != snake[1].getSPos()+dir_down) {
                        svel = dir_up;
                        game_state = e_playing;
                    }
                    else if (scancode == keyboard.f_down && snake[0].getSPos() != snake[1].getSPos()+dir_up) {
                        svel = dir_down;
                        game_state = e_playing;
                    }
                    else if (scancode == keyboard.f_left && snake[0].getSPos() != snake[1].getSPos()+dir_right) { 
                        svel = dir_left;
                        game_state = e_playing;
                    }
                    else if (scancode == keyboard.f_right && snake[0].getSPos() != snake[1].getSPos()+dir_left) {
                        svel = dir_right;
                        game_state = e_playing;
                    }
                }
                
            }     
        }

        next_time = (unsigned long long) (Utils::upTimeSeconds() * timestep);
        // limit update rate
        if (next_time > curr_time) {
            if (game_state == e_playing) {
                // calculate proposed new head + check collisions
                head_spos_buffer = head_spos + svel;
                wall_collision =    (head_spos_buffer.f_x <= frame_limits[2]) ||
                                    (head_spos_buffer.f_x >= frame_limits[3]) ||
                                    (head_spos_buffer.f_y <= frame_limits[0]) ||
                                    (head_spos_buffer.f_y >= frame_limits[1]);
                if (wall_collision) {
                    game_state = e_lost;
                    timestep = 10.0f;
                    std::cout << "WALL COLLISION" << std::endl;
                    continue;
                }
                self_collision = (available_blocks.find(Utils::vectorToBlockNum(head_spos_buffer, win_block_w)) == available_blocks.end() && head_spos_buffer != snake[snake_size-1].getSPos()) && svel != zero_vec;
                if (self_collision) {
                    game_state = e_lost;
                    timestep = 10.0f;
                    std::cout << "SELF COLLISION" << std::endl;
                    continue;
                }

                // grow if ate on previous frame
                if (ate) {
                    snake[snake_size] = Block(snake[snake_size-1].getSPos(), snake_sprites, zero_vec, zero_vec, block_scale);
                    snake_size++;
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
                    if (available_blocks.size() == 0) {
                        game_state = e_won;
                    } else {
                        food.setSPos(Utils::blockNumToVector(Utils::randElementInSet(&available_blocks), win_block_w));
                    } 
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
            
            if (game_state == e_lost && snake_size > 0) {
                snake_size--;  
            }

            

            curr_time = next_time;
        }

 		window.clear();

        window.render(frame);

        if (game_state == e_initial || game_state == e_playing)
            top_text.setCurrentFrame(Vector2(0,0), Vector2(win_w * 7 / 8, win_h * 2 / 15));
        else if (game_state == e_lost) {
            if (snake_size) top_text.setCurrentFrame(Vector2(0,0), Vector2(0,0));
            else            top_text.setCurrentFrame(Vector2(0,32), Vector2(win_w * 7 / 8, win_h * 2 / 15));
        } else if (game_state == e_won)
            top_text.setCurrentFrame(Vector2(0,64), Vector2(win_w * 7 / 8, win_h * 2 / 15));
        
        window.render(top_text);
        

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