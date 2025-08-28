#include "Player.h"
using namespace s3d;

Player::Player(const Vec2& pos, const Texture& tex)
    : Entity(pos, tex)
    , targetPos(pos) // start with current position
{}

void Player::update() {
    if (MouseR.down()) {
        targetPos = Cursor::PosF();
    }

    const Vec2 delta = (targetPos - position);
    const double distance = delta.length();
    const Vec2 direction = (distance > 0.0) ? (delta / distance) : Vec2::Zero();

    Circle{ targetPos, 5 }.draw(Palette::Red);

    if (distance > 1.0) {
        position += direction * speed * Scene::DeltaTime();
    } else {
        position = targetPos;
    }

    const double dx = targetPos.x - position.x;
    if (dx > 0.01 * speed || dx < -0.01 * speed) {
        facingLeft = (targetPos.x < position.x);
    }

    if (KeySpace.down()) {
        atkAnimInterval = 0.06;
        isAttacking = true;
    } else if (atkAnimInterval > 0) {
        atkAnimInterval -= Scene::DeltaTime();
		isAttacking = true;
    } else if (atkAnimInterval <= 0){
        isAttacking = false;
    }
}

void Player::draw() {
    if (isAttacking) {
        knightAtkTexture.scaled(0.2).mirrored(facingLeft).drawAt(position);
    } else {
        texture.scaled(0.2).mirrored(facingLeft).drawAt(position);
    }
}
