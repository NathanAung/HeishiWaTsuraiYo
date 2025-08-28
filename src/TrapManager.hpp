// TrapManager.hpp
#pragma once
#include <Siv3D.hpp>

class TrapManager {
private:
	struct Trap
	{
		Vec2 spawnPos{ 850, 300 };
		Vec2 currentPos{ 900, 0 };
		Circle collider{ 900, 0, 40 };
		float trapScale = 0.5f;

		int state = 0;	//0 - normal, 1 - king fell in, 2 - enemy fell in
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

	void SpawnTrap();
	void UpdateTraps(const double& deltaTime);

public:
	Array<Texture> holeTexArr;
	Array<Trap> trapArr;
	bool isSpawning = true;
	bool isMoving = true;

	float trapMoveSpeed = 30.0f;

	TrapManager();
	void Update();
	void Draw();
};
