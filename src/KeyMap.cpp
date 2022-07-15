#include <iostream>

#include "KeyMap.hpp"

KeyMap::KeyMap() {
    f_up     = SDL_SCANCODE_W;
    f_down   = SDL_SCANCODE_S;
    f_left   = SDL_SCANCODE_A;
    f_right  = SDL_SCANCODE_D;
    f_select = SDL_SCANCODE_E;
    f_option = SDL_SCANCODE_Q;
    f_back   = SDL_SCANCODE_LSHIFT;
}

KeyMap::KeyMap(SDL_Scancode* p_scancodes) {
    if (!p_scancodes) {
        std::cout << "error: null scancodes used in keymap" << std::endl;
    }
    f_up     = p_scancodes[0];
    f_down   = p_scancodes[1];
    f_left   = p_scancodes[2];
    f_right  = p_scancodes[3];
    f_select = p_scancodes[4];
    f_option = p_scancodes[5];
    f_back   = p_scancodes[6];
}
