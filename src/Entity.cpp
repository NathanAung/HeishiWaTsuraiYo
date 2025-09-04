#include "Entity.h"
using namespace s3d;

Entity::Entity(const Vec2& pos, const Texture& tex)
    : position(pos), texture(tex) {}

Entity::~Entity() = default;

void Entity::update() {
	position.x -= 100 * Scene::DeltaTime();
	collider.setPos(position);
}

void Entity::draw() {
    texture.scaled(0.2).drawAt(position); // default draw top-left
	//collider.draw();
}

double Entity::getY() const {
    return position.y;
}
