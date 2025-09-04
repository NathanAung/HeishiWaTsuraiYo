#include "Enemy.h"
using namespace s3d;

Enemy::Enemy(const Vec2& pos, const Texture& tex)
    : Entity(pos, tex)// start with current position
{}



void Enemy::update() {

	collider.setPos(position);
	// if (hitbox.intersects(otherHitbox) && isAttacking) {
    // 	// Collision detected
	// }
}


	





void Enemy::draw() {
    
	texture.scaled(0.2).drawAt(position);
	
}
