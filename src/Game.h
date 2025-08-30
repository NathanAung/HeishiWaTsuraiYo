#pragma once

# include <Siv3D.hpp>

class Game : public SceneManager<String>::Scene
{
public:

	Game(const InitData& init);
	~Game();

	void update() override;

	void draw() const override;

	void drawFadeIn(double t) const override;

	void drawFadeOut(double t) const override;

	void InitTexture();

private:

	Texture m_emoji;

	Stopwatch m_stopwatch;
};