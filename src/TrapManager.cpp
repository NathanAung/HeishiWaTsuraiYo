// TrapManager.cpp
#include "TrapManager.hpp"


TrapManager::TrapManager() {
    // Initialize textures inside the constructor
    
	Console << U"Called";
}


void TrapManager::SpawnTrap(){
	trapArr.emplace_back();
	Console << U"trap spawned";
}


// need arguments for player, king and soldiers
void TrapManager::Update(){
	const double deltaTime = Scene::DeltaTime();

	UpdateTraps(deltaTime);

	if(isSpawning){
		if(spawnTimer < spawnTime){
			spawnTimer += deltaTime;
		}
		else{
			SpawnTrap();
			spawnTimer = 0;
			spawnTime = Random(spawnTimeMin, spawnTimeMax);
		}
	}

	Draw();
}

void TrapManager::UpdateTraps(const double& deltaTime){
	if(isMoving){
		for(int i = trapArr.size() - 1; i >= 0; --i){
			Trap& trap = trapArr[i];

			float speed = trapMoveSpeed * deltaTime;
			trap.TrapUpdate(speed);
			//Console << trap.currentPos.x;

			if(trap.currentPos.x < -50.0){
				trapArr.remove_at(i);
				continue;	// skip to next iteration
			}
		}
	}
}


void TrapManager::Draw(){
	for (Trap& trap : trapArr) {
		
		trap.TrapDraw(holeTexArr); // Pass the textures here
	}
}

