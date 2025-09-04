# include "Game.h"

void Clear(){
	Console << U"Win";
}

void Lose(){
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
	king->AddWinEvent(Clear);
	king->AddLoseEvent(Lose);


	entities.push_back(std::make_unique<Player>(Vec2{400,300}, knightTexture));
	//entities.push_back(std::make_unique<King>(Vec2{200,350}, kingTexture));
	entities.push_back(std::make_unique<Entity>(Vec2{500,500}, grassTexture));
	entities.push_back(std::make_unique<Entity>(Vec2{100,200}, grassTexture));
	entities.push_back(std::make_unique<Entity>(Vec2{700,100}, grassTexture));
	entities.push_back(std::make_unique<Entity>(Vec2{1000,400}, enemyTexture));
	entities.push_back(std::make_unique<Entity>(Vec2{2000, 300}, enemyTexture));


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

	

	std::sort(entities.begin(), entities.end(),
	[](const auto& a, const auto& b){ return a->getY() < b->getY(); });

	king->Update();
}

void Game::draw() const
{
	//Scene::SetBackground(ColorF(0.0, 0.6, 0.4));

	const double t = m_stopwatch.sF();

	const Vec2 pos{ (Scene::Size().x/2 + Periodic::Sine1_1(3s, t) * Scene::Size().y/2), Scene::Size().y/2 };

	//m_emoji.drawAt(pos);




	for (auto& e : entities) { e->update(); e->draw(); }


	king->Draw();
}

void Game::drawFadeIn(double t) const
{
	draw();
	Circle{ Scene::Size().x/2, Scene::Size().y/2, Scene::Size().x }
	.drawFrame(((1 - t) * Scene::Size().x), 0, ColorF{ 0.2, 0.3, 0.4 });
}

void Game::drawFadeOut(double t) const
{
	draw();

	Circle{ Scene::Size().x/2, Scene::Size().y/2, Scene::Size().x }
	.drawFrame((t * Scene::Size().x), 0, ColorF{ 0.2, 0.3, 0.4 });
}
