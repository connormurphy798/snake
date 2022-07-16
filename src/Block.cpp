#include "Block.hpp"

Block::Block() : f_spos(Vector2(0,0)), f_scale2(0) { 
    f_pos = Vector2(0,0);

    f_texture = nullptr;
	
    f_current_frame.x = 0;
	f_current_frame.y = 0;
	f_current_frame.w = 0;
	f_current_frame.h = 0;
}

Block::Block(Vector2 spos, SDL_Texture* texture, int scale2) : f_spos(spos), f_scale2(scale2) { 
    updatePos();

    f_texture = texture;
	
    f_current_frame.x = 0;
	f_current_frame.y = 0;
	f_current_frame.w = 16;
	f_current_frame.h = 16;
}

Vector2& Block::getSPos() {
    return f_spos;
}

void Block::setSPos(Vector2 spos) {
    f_spos = spos;
    f_pos = spos.scale2(4);
}

int Block::incrementSX(int dx) {
    f_spos.f_x += dx;
    updateX();
    return f_spos.f_x; 
}

int Block::incrementSY(int dy) {
    f_spos.f_y += dy;
    updateY();
    return f_spos.f_y; 
}

Vector2& Block::incrementSPos(Vector2 v) {
    f_spos = f_spos + v;
    updatePos();
    return f_spos;
}

bool Block::incrementSPos(Vector2 v, const int* limits) {
    Vector2 spos_buffer = f_spos + v;
    int x = Utils::mid(limits[2], spos_buffer.f_x, limits[3]);
    int y = Utils::mid(limits[0], spos_buffer.f_y, limits[1]);
    setSPos(Vector2(x,y));
    updatePos();
    return (x != spos_buffer.f_x) || (y != spos_buffer.f_y);  // returns true if increment was blocked by limits
}

void Block::printPos(int pos_type) {
    switch (pos_type) {
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