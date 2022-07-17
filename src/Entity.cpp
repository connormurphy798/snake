#include "Entity.hpp"

Entity::Entity() : f_pos(Vector2(0,0)), f_texture(nullptr) {
    f_current_frame.x = 0;
	f_current_frame.y = 0;
	f_current_frame.w = 0;
	f_current_frame.h = 0;
}

Entity::Entity(Vector2 pos, SDL_Texture* texture) : f_pos(pos), f_texture(texture) {
	f_current_frame.x = 0;
	f_current_frame.y = 0;
	f_current_frame.w = 16;
	f_current_frame.h = 16;
}

Entity::Entity(Vector2 pos, SDL_Texture* texture, Vector2 texture_offset, Vector2 texture_size) : f_pos(pos), f_texture(texture) {
    setCurrentFrame(texture_offset, texture_size);
}

Vector2& Entity::getPos() {
    return f_pos;
}

void Entity::setPos(Vector2 pos) {
    f_pos = pos;
}

SDL_Rect Entity::getCurrentFrame() {
	return f_current_frame;
}

void Entity::setCurrentFrame(Vector2 offset, Vector2 size) {
    f_current_frame.x = offset.f_x;
	f_current_frame.y = offset.f_y;
	f_current_frame.w = size.f_x;
	f_current_frame.h = size.f_y;
}

SDL_Texture* Entity::getTexture() {
	return f_texture;
}