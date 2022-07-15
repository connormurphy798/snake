#include "Block.hpp"

Block::Block() : f_spos(Vector2(0,0)) { 
    f_pos = Vector2(0,0);

    f_texture = nullptr;
	
    f_current_frame.x = 0;
	f_current_frame.y = 0;
	f_current_frame.w = 0;
	f_current_frame.h = 0;
}

Block::Block(Vector2 p_spos, SDL_Texture* p_texture) : f_spos(p_spos) { 
    f_pos = f_spos.scale2(4);

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