# include <Siv3D.hpp>
# include "Title.h"
# include "Game.h"

using App = SceneManager<String>;


class KingMoveManager
{
	private:
		// 王の移動速度
		double _scrollSpeedPerSec;

		// 王の総移動時間
		double _kingMoveTimeSec;

		// 現在の残り移動時間
		double _timeFramePerSec;

		// 王のX座標
		double _kingXPosition;

		// 王の最大HP
		int32 _kingMaxHP;

		// 王のHP
		int32 _kingHP;

		// 王が受けるダメージ
		int32 _kingDamage;

		// 穴に入っているか
		bool _isInsideTheHole = false;

		// 王の座標のオフセット
		const double _kingPosOffset = 100;

		const Texture king{ U"👨"_emoji };

		const Texture queen{ U"👩"_emoji };

		const Rect _gaugeBackImage{ 200, 50, 800, 50 };

		RectF _hpGaugebackImage;

		const double _hpGaugebackImageWidth = 100;

		const double _hpGaugebackImageHeight = 30;

		const double _invisibleSec = 2.0;

		double _invisibleCount = 0;

		std::vector<std::function<void()>> _winDelegates;

		std::vector<std::function<void()>> _loseDelegates;

		bool _hasWin = false;

		bool _hasLose = false;

	public:
		Circle collider{ 400, 300, 40 };

		KingMoveManager(double kingXPosition, double scrollSpeed, double gamePlayDuration, int32 kingHP, int32 kingDamage){
			_kingXPosition = kingXPosition;
			_scrollSpeedPerSec = scrollSpeed;
			_kingMoveTimeSec = gamePlayDuration;
			_timeFramePerSec = _kingMoveTimeSec;
			_kingMaxHP = kingHP;
			_kingHP = _kingMaxHP;
			_kingDamage = kingDamage;
			_hpGaugebackImage = { kingXPosition - (_hpGaugebackImageWidth / 2), Scene::Height() / 2 - 100, _hpGaugebackImageWidth, _hpGaugebackImageHeight };

		}
		void AddWinEvent(std::function<void()> func)
		{
    		_winDelegates.push_back(func);
		}

		void InvokeWinEvent()
		{
			if (_hasWin) return;
			_hasWin = true;
			for (auto& delegate : _winDelegates)
			{
				delegate();
			}
		}

		void AddLoseEvent(std::function<void()> func)
		{
    		_loseDelegates.push_back(func);
		}

		void InvokeLoseEvent()
		{
			if (_hasWin) return;
			_hasLose = true;
			for (auto& delegate : _loseDelegates)
			{
				delegate();
			}
		}

		bool IsInsideTheHole(){
			return _isInsideTheHole;
		}

		void FellIntoTheHole(){
			_isInsideTheHole = true;
		}

		void CameOutOfTheHole(){
			_isInsideTheHole = false;
		}

		void OnKingDamaged(){
			if (_isInsideTheHole) return;
			if (_invisibleCount > 0) return;
			_invisibleCount = _invisibleSec;
			_kingHP -= _kingDamage;
		}

		void Update(){
			Print(_invisibleCount);
			Print(_kingHP);
			if (_invisibleCount > 0)
				_invisibleCount -= Scene::DeltaTime();
			if (!_isInsideTheHole && _timeFramePerSec > 0)
				_timeFramePerSec -= Scene::DeltaTime();
			if (_invisibleCount > 0)
				_invisibleCount -= Scene::DeltaTime();
			if (_kingHP <= 0){
				InvokeLoseEvent();
				_kingHP = 0;
			}
			if (_timeFramePerSec <= 0){
				InvokeWinEvent();
			}
		}

		void Draw(){
			_gaugeBackImage.draw();
			_hpGaugebackImage.draw();
			RectF{ _gaugeBackImage.x + 10, _gaugeBackImage.y + 10, (_gaugeBackImage.w - 20) * (_timeFramePerSec / _kingMoveTimeSec), _gaugeBackImage.h - 20 }.draw(Palette::Blue);
			RectF{ _hpGaugebackImage.x + 2.5, _hpGaugebackImage.y + 2.5, (_hpGaugebackImage.w - 5) * ((double)_kingHP / (double)_kingMaxHP), _hpGaugebackImage.h - 5 }.draw(Palette::Green);
			king.scaled(0.75).drawAt(_kingXPosition, Scene::Height() / 2);
			queen.scaled(0.75).drawAt((_timeFramePerSec * _scrollSpeedPerSec) + _kingXPosition + _kingPosOffset, Scene::Height() / 2);
			if (_timeFramePerSec <= 0){
				FontAsset(U"TitleFont")(U"Clear").drawAt(100, 100);
			}
		}
};

void Clear(){
	Console << U"Win";
}

void Lose(){
	Console << U"Lose";
}

void Main()
{
	Window::SetTitle(U"兵士はつらいよ");
	Window::Resize(1280, 720);
	Graphics::SetVSyncEnabled(true);

	FontAsset::Register(U"TitleFont", FontMethod::MSDF, 48, Typeface::Bold);

	// Create scene manager
	App manager;

	manager.add<Title>(U"Title");
	manager.add<Game>(U"Game");

	manager.setFadeColor(ColorF{ 0.8, 0.9, 1.0 });

	manager.init(U"Title", 0.75s);

	// 背景の色を設定する | Set the background color
	Scene::SetBackground(ColorF{ 0.6, 0.8, 0.7 });

	KingMoveManager king(100, 30, 120, 100, 10);
	king.AddWinEvent(Clear);
	king.AddLoseEvent(Lose);

	while (System::Update())
	{
		king.Update();
		king.Draw();
		if (KeyA.pressed()){
			king.FellIntoTheHole();
		}
		if (KeyD.pressed()){
			king.CameOutOfTheHole();
		}
		if (KeyS.pressed()){
			king.OnKingDamaged();
		}
		if (not manager.update())
		{
			break;
		}
	}
}
