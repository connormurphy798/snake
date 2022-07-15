#include "Block.hpp"

Block::Block() : f_spos(Vector2(0,0)), f_scale2(0) { 
    f_pos = Vector2(0,0);

    f_texture = nullptr;
	
    f_current_frame.x = 0;
	f_current_frame.y = 0;
	f_current_frame.w = 0;
	f_current_frame.h = 0;
}

Block::Block(Vector2 p_spos, SDL_Texture* p_texture, int p_scale2) : f_spos(p_spos), f_scale2(p_scale2) { 
    updatePos();

    f_texture = p_texture;
	
    f_current_frame.x = 0;
	f_current_frame.y = 0;
	f_current_frame.w = 16;
	f_current_frame.h = 16;
}

Vector2& Block::getSPos() {
    return f_spos;
}

void Block::setSPos(Vector2 p_spos) {
    f_spos = p_spos;
    f_pos = p_spos.scale2(4);
}

int Block::incrementSX(int p_dx) {
    f_spos.f_x += p_dx;
    updateX();
    return f_spos.f_x; 
}

int Block::incrementSY(int p_dy) {
    f_spos.f_y += p_dy;
    updateY();
    return f_spos.f_y; 
}

Vector2& Block::incrementSPos(Vector2 p_d) {
    f_spos = f_spos + p_d;
    updatePos();
    return f_spos;
}

Vector2& Block::incrementSPos(Vector2 p_d, const int* p_limits) {
    Vector2 spos_buffer = f_spos + p_d;
    setSPos(Vector2(
        Utils::mid(p_limits[2], spos_buffer.f_x, p_limits[3]),
        Utils::mid(p_limits[0], spos_buffer.f_y, p_limits[1])
    ));
    updatePos();
    return f_spos;
}

void Block::printPos(int p_pos_type) {
    switch (p_pos_type) {
        case 0:     // spos + pos
            std::cout << "SPos: (" << f_spos.f_x << ", " << f_spos.f_y << "),   " << "Pos: (" << f_pos.f_x << ", " << f_pos.f_y << ")  " << std::endl;
            break;
        case 1:     // spos only
            std::cout << "SPos: (" << f_spos.f_x << ", " << f_spos.f_y << ")" << std::endl;
            break;
        case 2:     // pos only
            std::cout << "Pos: (" << f_pos.f_x << ", " << f_pos.f_y << ")  " << std::endl;
            break;
    }
}