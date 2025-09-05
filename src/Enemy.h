#pragma once
#include "Entity.h"

class Enemy : public Entity {
public:
    Enemy(const s3d::Vec2& pos, const s3d::Texture& tex);
	~Enemy() {};

    void update() override;
    void draw() override;
	void MoveTo(Vec2 pos);

private:
    const s3d::Texture knightAtkTexture{ U"Assets/knightAtk.png" };
};
