#pragma once
#include "Entity.h"

class Enemy : public Entity {
public:
    Enemy(const s3d::Vec2& pos, const s3d::Texture& tex);
	~Enemy() {};

    void update() override;
    void draw() override;
	void MoveTo(Vec2 pos);
	void PushTo(Vec2 pos, double time);
	bool fallen = false;
	double movingTime = 0.0;

private:
    const s3d::Texture knightAtkTexture{ U"Assets/knightAtk.png" };

	
	double maxTime = 10.0;
	Vec2 movingToPos;
};
