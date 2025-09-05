#include "Enemy.h"
using namespace s3d;

Enemy::Enemy(const Vec2& pos, const Texture& tex)
    : Entity(pos, tex)// start with current position
{}



void Enemy::update() {

	position.x -= 100 * Scene::DeltaTime();
	position.y += ( position.x < 300 ? (position.y > Scene::Height()/2 ? -100 : 100)  * Scene::DeltaTime() : 0);
	collider.setPos(position);
	// if (hitbox.intersects(otherHitbox) && isAttacking) {
    // 	// Collision detected
	// }
}


void Enemy::draw() {
    if(!fallen)
		texture.scaled(0.2).drawAt(position);
	
}

void Enemy::MoveTo(Vec2 pos){
	position = pos;
}
