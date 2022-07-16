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

KeyMap::KeyMap(SDL_Scancode* scancodes) {
    if (!scancodes) {
        std::cout << "error: null scancodes used in keymap" << std::endl;
    }
    f_up     = scancodes[0];
    f_down   = scancodes[1];
    f_left   = scancodes[2];
    f_right  = scancodes[3];
    f_select = scancodes[4];
    f_option = scancodes[5];
    f_back   = scancodes[6];
}
