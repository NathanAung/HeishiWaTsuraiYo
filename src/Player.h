#pragma once
#include "Entity.h"

class Player : public Entity {
public:
    Player(const s3d::Vec2& pos, const s3d::Texture& tex);

    void update() override;
    void draw() override;
	


private:
    const s3d::Texture knightAtkTexture{ U"Assets/knightAtk.png" };
    double speed = 280.0;

    s3d::Vec2 targetPos;        // destination
    bool facingLeft = false;
    bool isAttacking = false;
    double atkAnimInterval = 0;
	Rect hitbox;

	


};
