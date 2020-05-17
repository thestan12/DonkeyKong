#pragma once

#define ECHELLE_COUNT 4
#define BLOCK_COUNT_X 8
#define BLOCK_COUNT_Y 5
#define BLOCK_SPACE 110.f

class Game
{
public:
	Game();
	~Game() { };
	void run();



private:
	void processEvents();
	void update(sf::Time elapsedTime);
	void render();

	void updateStatistics(sf::Time elapsedTime);
	void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);

	void createBoule();

	void GameOver();

	void GameWin();



private:
	static const float		PlayerSpeed;
	static const sf::Time	TimePerFrame;

	sf::RenderWindow		mWindow;
	sf::Texture	mTexture;
	sf::Texture	monkeyTexture;
	sf::Texture	peachTexture;
	sf::Texture	BouleTexture;
	sf::Sprite	mPlayer;
	sf::Sprite	mMonkey;
	sf::Sprite	mPeach;
	sf::Sprite	mBoule;
	sf::Font	mFont;
	sf::Text	mStatisticsText;
	sf::Time	mStatisticsUpdateTime;

	sf::Sprite mGameOver;
	sf::Texture mGameOverTexture;


	sf::Sprite mGameWin;
	sf::Texture mGameWinTexture;


	std::size_t	mStatisticsNumFrames;
	bool mIsMovingUp;
	bool mIsMovingDown;
	bool mIsMovingRight;
	bool mIsMovingLeft;
	int bouleStep = 0;


	sf::Texture	_TextureEchelle;
	sf::Sprite	_Echelle[ECHELLE_COUNT];
	sf::Texture	_TextureBlock;
	sf::Sprite	_Block[BLOCK_COUNT_X][BLOCK_COUNT_Y];
	sf::Texture	_TextureWeapon;
	sf::Sprite	_Weapon;
	sf::Vector2u _sizeBlock;
	sf::Vector2u _sizeMario;
	sf::Vector2u _sizeMonkey;
};

