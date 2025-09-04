// TrapManager.hpp
#pragma once
#include <Siv3D.hpp>
#include "KingP.h"
#include "EnemyManagerP.h"
#include "PlayerP.h"

class TrapManager {
private:
	struct Trap
	{
		Vec2 spawnPos{ 850, 300 };
		Vec2 currentPos{ 900, 0 };
		Circle collider{ 900, 0, 40 };
		float trapScale = 0.1f;

		int state = 0;	//0 - normal, 1 - king fell in, 2 - enemy fell in, 3 - disabled
		bool activated = false;

		Trap() {
			currentPos = spawnPos;
			collider.setPos(spawnPos);

		}

		void TrapUpdate(float& deltaSpeed) {
			currentPos.x -= deltaSpeed;
			collider.setPos(currentPos);
		}

		void TrapCollide(int type) {

		}

		void TrapDraw(const Array<Texture>& textures) {
			textures[state].scaled(trapScale).drawAt(currentPos);
		}
	};

	const float spawnTimeMin = 3.0f;
	const float spawnTimeMax = 8.0f;
	float spawnTime = 2.0f;
	float spawnTimer = 0.0f;

	void SpawnTrap();	// add a trap to array
	void UpdateTraps(const double& deltaTime, KingP& king, PlayerP& player, Array<EnemyManagerP::EnemyP>& enemyArr);	// update individual traps

public:
	Array<Texture> holeTexArr;
	Array<Trap> trapArr;
	bool isSpawning = true;
	bool isMoving = true;

	float trapMoveSpeed = 30.0f;

	TrapManager();	// constructor
	void Update(KingP& king, PlayerP& player, Array<EnemyManagerP::EnemyP>& enemyArr);	// update for the manager, spawn, update traps
	void Draw();
	void TrapsPause(bool pause); // true = pause spawning traps, false = resume
};
