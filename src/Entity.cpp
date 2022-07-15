#include "Entity.hpp"

Entity::Entity(int p_x, int p_y, SDL_Texture* p_texture) : f_texture(p_texture) {
    f_pos.f_x = p_x;
    f_pos.f_y = p_y;
	f_current_frame.x = 0;
	f_current_frame.y = 0;
	f_current_frame.w = 16;
	f_current_frame.h = 16;
}

Entity::Entity(Vector2 p_pos, SDL_Texture* p_texture) : f_pos(p_pos), f_texture(p_texture) {
	f_current_frame.x = 0;
	f_current_frame.y = 0;
	f_current_frame.w = 16;
	f_current_frame.h = 16;
}

int Entity::getX() {
	return f_pos.f_x;
}

int Entity::getY() {
	return f_pos.f_y;
}

Vector2& Entity::getPos() {
    return f_pos;
}

void Entity::setX(int p_x) {
    f_pos.f_x = p_x;
}

void Entity::setY(int p_y) {
    f_pos.f_y = p_y;
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