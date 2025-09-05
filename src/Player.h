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
	bool isAttacking = false;

private:
    const s3d::Texture knightAtkTexture{ U"Assets/knightAtk.png" };
    double speed = 280.0;

	double attackCoolDown = 0.1;

    s3d::Vec2 targetPos;        // destination
    bool facingLeft = false;
    double atkAnimInterval = 0;
	

	


};
