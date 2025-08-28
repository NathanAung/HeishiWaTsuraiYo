#include <Siv3D.hpp> // Siv3D v0.6.14
#include "Entity.h"
#include "Player.h"




void Main()
{

	Window::Resize(1280, 720);
	// 背景の色を設定する | Set the background color
	Scene::SetBackground(ColorF{ 0.6, 0.8, 0.7 });

	// 画像ファイルからテクスチャを作成する | Create a texture from an image file
	const Texture kingTexture{ U"Assets/king.png" };
	const Texture knightTexture{ U"Assets/knight.png"};

	Player knight(Vec2{400, 300}, knightTexture);

	



	Vec2 kingPos = Vec2(150, 250); 		// King starting position
	while (System::Update())
	{

		kingTexture.scaled(0.2).drawAt(kingPos);
		
		knight.update();
		knight.draw();

		if (kingPos.y > knight.getY()) {
			kingTexture.scaled(0.2).drawAt(kingPos);
		}


	}



}
