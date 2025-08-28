#pragma once
#include <Siv3D.hpp>
 
class TrapManager {
private:
	const Texture holeT{ U"🕳️"_emoji};
	const Texture holeKingT{ U"🫅"_emoji};
	const Texture holeEnemyT{ U"🥷"_emoji};

	struct Trap
	{
		Vec2 currentPos;
		Texture* texture;
		Circle collider{ 400, 300, 40 };

		int state = 0;	//0 - normal, 1 - king fell in, 2 - enemy fell in

	};

	const float spawnTimeMin = 0.5f;
	const float spawnTimeMax = 3.0f;
	float spawnTime = 2.0f;
	float spawnTimer = 0.0f;
	
	void SpawnTrap();
	void UpdateTraps(const double& deltaTime);

public:
	Array<Trap> trapArr;
	bool isSpawning = true;
	bool isMoving = true;

	float trapMoveSpeed = 2.0f;

    //TrapManager();
    void Update();
    void Draw() const;
};