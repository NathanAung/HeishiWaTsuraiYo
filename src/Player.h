#pragma once
#include "Entity.h"

class Player : public Entity {
public:
	bool scrolling = true;
    Player(const s3d::Vec2& pos, const s3d::Texture& tex);
	~Player() {};

    void update() override;
    void draw() override;
	
	Rect hitbox;

private:
    const s3d::Texture knightAtkTexture{ U"Assets/knightAtk.png" };
    double speed = 280.0;

	double attackCoolDown = 0.6;

    s3d::Vec2 targetPos;        // destination
    bool facingLeft = false;
    bool isAttacking = false;
    double atkAnimInterval = 0;
	

	


};
