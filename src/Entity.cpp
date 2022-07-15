#include "Entity.hpp"

Entity::Entity() : f_pos(Vector2(0,0)), f_texture(nullptr) {
    f_current_frame.x = 0;
	f_current_frame.y = 0;
	f_current_frame.w = 0;
	f_current_frame.h = 0;
}

Entity::Entity(Vector2 p_pos, SDL_Texture* p_texture) : f_pos(p_pos), f_texture(p_texture) {
	f_current_frame.x = 0;
	f_current_frame.y = 0;
	f_current_frame.w = 16;
	f_current_frame.h = 16;
}

Vector2& Entity::getPos() {
    return f_pos;
}

void Entity::setPos(Vector2 p_pos) {
    f_pos = p_pos;
}

SDL_Rect Entity::getCurrentFrame() {
	return f_current_frame;
}

SDL_Texture* Entity::getTexture() {
	return f_texture;
}