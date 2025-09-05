# include "Game.h"



void Lose() {
	Console << U"Lose";
}

Game::Game(const InitData& init)
	: IScene{ init }
	, m_emoji{ U"🐥"_emoji }
{
	Print << U"Game::Game()";
	Window::Resize(1280, 720);
	// 背景の色を設定する | Set the background color
	Scene::SetBackground(ColorF{ 0.7, 0.7, 0.7 });



	king = new KingMoveManager(100, 30, 120, 100, 10);

	player = new Player(Vec2{ 400,300 }, knightTexture);

	for (int i = 0; i < 8; i++) {
		enemyArray.push_back(new Enemy(Vec2{ Scene::Width() + i * 200,Random(100, Scene::Height() - 100) }, enemyTexture));
	}

	entities.push_back(std::unique_ptr<Player>(player));
	//entities.push_back(std::make_unique<King>(Vec2{200,350}, kingTexture));
	entities.push_back(std::make_unique<Entity>(Vec2{ 500,500 }, grassTexture));
	entities.push_back(std::make_unique<Entity>(Vec2{ 100,200 }, grassTexture));
	entities.push_back(std::make_unique<Entity>(Vec2{ 700,100 }, grassTexture));
	for (int i = 0; i < enemyArray.size(); i++) {
		entities.push_back(std::unique_ptr<Enemy>(enemyArray[i]));
	}


	Vec2 kingPos = Vec2(150, 250); 		// King starting position

}

Game::~Game()
{
	Print << U"Game::~Game()";
}

void Game::update()
{
	if (not m_stopwatch.isStarted())
	{
		m_stopwatch.start();
	}

	for (int i = 0; i < enemyArray.size(); i++) {
		if (!enemyArray[i]->fallen) {
			if (enemyArray[i]->collider.intersects(king->collider)) {
				king->OnKingDamaged();
				enemyArray[i]->MoveTo(Vec2{ Scene::Width() + 100,Random(100, Scene::Height() - 100) });
			}

			if (enemyArray[i]->collider.intersects(player->hitbox) && player->isAttacking) {
				int nearestTrap = -1;
				for (int j = 0; j < trapManager.trapArr.size(); j++) {

					if (!trapManager.trapArr[j].activated && nearestTrap == -1)
						nearestTrap = j;

				}

				if (nearestTrap != -1) {
					enemyArray[i]->PushTo(trapManager.trapArr[nearestTrap].collider.center, 10.0);

				}


			}
		}

		for (int j = 0; j < trapManager.trapArr.size(); j++) {

			if (trapManager.trapArr[j].collider.intersects(enemyArray[i]->collider) && enemyArray[i]->movingTime > 0.0) {
				enemyArray[i]->fallen = true;
				continue;
			}

		}

		if (enemyArray[i]->collider.x < -100) {
			enemyArray[i]->MoveTo(Vec2{ Scene::Width() + 100,Random(100, Scene::Height() - 100) });
			enemyArray[i]->fallen = false;
		}

	}



	player->scrolling = !king->fallen;

	trapManager.Update(*king, *player, enemyArray);

	std::sort(entities.begin(), entities.end(),
	[](const auto& a, const auto& b) { return a->getY() < b->getY(); });

	king->Update();

	if (king->ReturnGameStatus() & 0x0100)
		changeScene(U"Title", 1.5s); //WON

	if (king->ReturnGameStatus() & 0x0010)
		changeScene(U"Title", 1.5s); //LOST
}

void Game::draw() const
{
	//Scene::SetBackground(ColorF(0.0, 0.6, 0.4));

	const double t = m_stopwatch.sF();

	const Vec2 pos{ (Scene::Size().x / 2 + Periodic::Sine1_1(3s, t) * Scene::Size().y / 2), Scene::Size().y / 2 };

	//m_emoji.drawAt(pos);




	for (auto& e : entities) { e->update(); e->draw(); }


	king->Draw();
}

void Game::drawFadeIn(double t) const
{
	draw();
	Circle{ Scene::Size().x / 2, Scene::Size().y / 2, Scene::Size().x }
	.drawFrame(((1 - t) * Scene::Size().x), 0, ColorF{ 0.2, 0.3, 0.4 });
}

void Game::drawFadeOut(double t) const
{
	draw();

	Circle{ Scene::Size().x / 2, Scene::Size().y / 2, Scene::Size().x }
	.drawFrame((t * Scene::Size().x), 0, ColorF{ 0.2, 0.3, 0.4 });
}

