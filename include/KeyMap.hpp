#pragma once

#include <SDL2/SDL.h>

struct KeyMap {
    KeyMap();

    KeyMap(SDL_Scancode* p_scancodes);

    SDL_Scancode f_up;
    SDL_Scancode f_down;
    SDL_Scancode f_left;
    SDL_Scancode f_right;
    SDL_Scancode f_select;
    SDL_Scancode f_option;
    SDL_Scancode f_back;
};