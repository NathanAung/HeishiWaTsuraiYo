#include "TrapManager.hpp"


void TrapManager::SpawnTrap(){
	if(!isSpawning) return;


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
}

void TrapManager::UpdateTraps(const double& deltaTime){
	if(isMoving){
		for(int i = trapArr.size() - 1; i >= 0; --i){
			Trap& trap = trapArr[i];

			trap.currentPos.x -= trapMoveSpeed * deltaTime;
		}
	}
}


void TrapManager::Draw() const{

}

