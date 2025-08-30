#include <Siv3D.hpp> // Siv3D v0.6.14
#include "Entity.h"
#include "Player.h"
#include "King.h"




void Main()
{

	Window::Resize(1280, 720);
	// 背景の色を設定する | Set the background color
	Scene::SetBackground(ColorF{ 0.7, 0.7, 0.7 });

	// 画像ファイルからテクスチャを作成する | Create a texture from an image file
	const Texture kingTexture{ U"Assets/king.png" };
	const Texture knightTexture{ U"Assets/knight.png"};
	const Texture grassTexture{U"Assets/grass.png"};
	const Texture enemyTexture{U"Assets/enemy.png"};


	std::vector<std::unique_ptr<Entity>> entities;
	entities.push_back(std::make_unique<Player>(Vec2{400,300}, knightTexture));
	entities.push_back(std::make_unique<King>(Vec2{200,350}, kingTexture));
	entities.push_back(std::make_unique<Entity>(Vec2{500,500}, grassTexture));
	entities.push_back(std::make_unique<Entity>(Vec2{100,200}, grassTexture));
	entities.push_back(std::make_unique<Entity>(Vec2{700,100}, grassTexture));
	entities.push_back(std::make_unique<Entity>(Vec2{1000,400}, enemyTexture));


	Vec2 kingPos = Vec2(150, 250); 		// King starting position
	

	while (System::Update())
	{
		std::sort(entities.begin(), entities.end(),
    	[](const auto& a, const auto& b){ return a->getY() < b->getY(); });

		for (auto& e : entities) { e->update(); e->draw(); }
	}

}
