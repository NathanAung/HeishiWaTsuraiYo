# include "Title.h"

Title::Title(const InitData& init)
		: IScene{ init }
{
	Print << U"Title::Title()";
}

Title::~Title()
{
	Print << U"Title::~Title()";
}

// Update function
void Title::update()
{
	// On left click
	if (MouseL.down())
	{
		// Transition to game scene
		changeScene(U"Game", 1.5s);
	}
}

// Draw function
void Title::draw() const 
{
	Scene::SetBackground(ColorF{ 0.6, 0.8, 0.7 });
	FontAsset(U"TitleFont")(U"My Game").drawAt(60, Vec2{ Scene::Size().x/2, Scene::Size().y/8 });
	Circle{ Cursor::Pos(), 50 }.draw(Palette::Seagreen);
}

void Title::drawFadeIn(double t) const
{
	draw();
	Circle{ Scene::Size().x/2, Scene::Size().y/2, Scene::Size().x }
		.drawFrame(((1 - t) * Scene::Size().x), 0, ColorF{ 0.2, 0.3, 0.4 });

	
	
}

void Title::drawFadeOut(double t) const
{
	draw();
	Circle{ Scene::Size().x/2, Scene::Size().y/2, Scene::Size().x }
		.drawFrame((t *  Scene::Size().x), 0, ColorF{ 0.2, 0.3, 0.4 });
}