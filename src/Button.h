#pragma once

#include <Siv3D.hpp>

class Button
{
	public:

	Button(Rect r, FontAsset f,String s)
		: rect(r)
		, font(f)
		, text(s)
	{};
	~Button(){
		
	};


	void update(){
		if (rect.mouseOver())
		{
			// Change the mouse cursor to a hand
			Cursor::RequestStyle(CursorStyle::Hand);
			hover = true;
		}
		else hover = false;
	}

	void draw(){

		RoundRect roundRect = rect.rounded(6);

		roundRect
		.drawShadow(Vec2{ 2, 2 }, 12, 0)
		.draw(( hover ? ColorF{ 0.5, 0.9, 0.9 } : ColorF{ 0.9, 0.9, 0.9 }));

		// Draw border
		rect.stretched(-3).rounded(3)
		.drawFrame(2, ColorF{ 0.2, 0.2, 0.2 });

		// Draw text
		font(text).drawAt(40, rect.center(), ColorF{ 0.1, 0.1, 0.1 });
	}

	bool clicked(){
		return rect.leftClicked();
	}
	
	private:

	bool hover = false;

	Rect rect;
	FontAsset font;
	String text;
};