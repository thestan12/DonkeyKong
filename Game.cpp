#include "pch.h"
#include "StringHelpers.h"
#include "Game.h"
#include "EntityManager.h"
#include "PlayerEntity.h"

const float Game::PlayerSpeed = 100.f;
const sf::Time Game::TimePerFrame = sf::seconds(1.f / 60.f);

Game::Game()
	: mWindow(sf::VideoMode(840, 600), "Donkey Kong 1981", sf::Style::Close)
	, mTexture()
	, mPlayer()
	, mFont()
	, mStatisticsText()
	, mStatisticsUpdateTime()
	, mStatisticsNumFrames(0)
	, mIsMovingUp(false)
	, mIsMovingDown(false)
	, mIsMovingRight(false)
	, mIsMovingLeft(false)
{
	mWindow.setFramerateLimit(160);



	// Draw blocks

	_TextureBlock.loadFromFile("Media/Textures/Block.png");
	_sizeBlock = _TextureBlock.getSize();

	for (int i = 0; i < BLOCK_COUNT_X; i++)
	{
		for (int j = 0; j < BLOCK_COUNT_Y; j++)
		{
			_Block[i][j].setTexture(_TextureBlock);
			_Block[i][j].setPosition(100.f + 70.f * (i + 1), 0.f + BLOCK_SPACE * (j + 1));

			std::shared_ptr<Entity> se = std::make_shared<Entity>();
			se->m_sprite = _Block[i][j];
			se->m_type = EntityType::block;
			se->m_size = _TextureBlock.getSize();
			se->m_position = _Block[i][j].getPosition();
			EntityManager::m_Entities.push_back(se);
		}
	}

	// Draw Echelles
	

	_TextureEchelle.loadFromFile("Media/Textures/Echelle.png");

	for (int i = 0; i < ECHELLE_COUNT; i++)
	{
		_Echelle[i].setTexture(_TextureEchelle);
		_Echelle[i].setPosition(100.f + 70.f * (i + 1), 0.f + BLOCK_SPACE * (i + 1)  );

		std::shared_ptr<Entity> se = std::make_shared<Entity>();
		se->m_sprite = _Echelle[i];
		se->m_type = EntityType::echelle;
		se->m_size = _TextureEchelle.getSize();
		se->m_position = _Echelle[i].getPosition();

		EntityManager::m_Entities.push_back(se);
	}

	// Boule


	BouleTexture.loadFromFile("Media/Textures/Piece.png");

	mBoule.setTexture(BouleTexture);

	sf::Vector2f posBoule;
	posBoule.x = 10.f + 70.f * 6;
	posBoule.y = BLOCK_SPACE * 1 - BouleTexture.getSize().y - 40;

	mBoule.setPosition(posBoule);
	
	Game::createBoule();

	// Game Over


	mGameOverTexture.loadFromFile("Media/Textures/gameOver.png");

	mGameOver.setTexture(mGameOverTexture);

	sf::Vector2f posGameOver;
	posGameOver.x = mWindow.getPosition().x - 300;
	posGameOver.y = mWindow.getPosition().y - 100;

	mGameOver.setPosition(posGameOver);

	// Game Win

	mGameWinTexture.loadFromFile("Media/Textures/youWin.png");

	mGameWin.setTexture(mGameWinTexture);

	sf::Vector2f posGameWin;
	posGameWin.x = mWindow.getPosition().x - 350;
	posGameWin.y = mWindow.getPosition().y - 150 ;

	mGameWin.setPosition(posGameWin);

	// Peach 

	peachTexture.loadFromFile("Media/Textures/peach.png");

	_sizeMonkey = peachTexture.getSize();

	mPeach.setTexture(peachTexture);

	sf::Vector2f posPeach;
	posPeach.x = 10.f + 70.f * 9;
	posPeach.y = BLOCK_SPACE * 1 - _sizeMonkey.y;

	mPeach.setPosition(posPeach);

	std::shared_ptr<Entity> peach = std::make_shared<Entity>();
	peach->m_sprite = mPeach;
	peach->m_type = EntityType::princesse;
	peach->m_size = peachTexture.getSize();
	peach->m_position = mPeach.getPosition();

	EntityManager::m_Entities.push_back(peach);

	// Donkey Kong

	monkeyTexture.loadFromFile("Media/Textures/monkey.png");

	_sizeMonkey = monkeyTexture.getSize();

	mMonkey.setTexture(monkeyTexture);

	sf::Vector2f posMonkey;
	posMonkey.x = 10.f + 70.f * 7;
	posMonkey.y = BLOCK_SPACE * 1 - _sizeMonkey.y;

	mMonkey.setPosition(posMonkey);

	std::shared_ptr<Entity> monkey = std::make_shared<Entity>();
	monkey->m_sprite = mMonkey;
	monkey->m_type = EntityType::monkey;
	monkey->m_size = monkeyTexture.getSize();
	monkey->m_position = mMonkey.getPosition();

	EntityManager::m_Entities.push_back(monkey);
	// Draw Mario

	mTexture.loadFromFile("Media/Textures/Mario_small_transparent.png"); // Mario_small.png");

	_sizeMario = mTexture.getSize();
	mPlayer.setTexture(mTexture);
	sf::Vector2f posMario;

	posMario.x = 100.f + 70.f;
	posMario.y = BLOCK_SPACE * 5 - _sizeMario.y;

	mPlayer.setPosition(posMario);

	std::shared_ptr<PlayerEntity> player = std::make_shared<PlayerEntity>();
	player->m_sprite = mPlayer;
	player->m_type = EntityType::player;
	player->m_size = mTexture.getSize();
	player->m_position = mPlayer.getPosition();

	EntityManager::m_Entities.push_back(player);

	EntityManager::m_player = player;


	EntityManager::BouleEntityFactory();
	// Draw Statistic Font 

	mFont.loadFromFile("Media/Textures/Mario_small_transparent.png");
	mStatisticsText.setString("Welcome to Donkey Kong 1981");
	mStatisticsText.setFont(mFont);
	mStatisticsText.setPosition(5.f, 5.f);
	mStatisticsText.setCharacterSize(10);
}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	while (mWindow.isOpen())
	{
		sf::Time elapsedTime = clock.restart();
		timeSinceLastUpdate += elapsedTime;
		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;

			processEvents();
			update(TimePerFrame);
		}
		
		updateStatistics(elapsedTime);
		render();
	}
}

void Game::processEvents()
{
	sf::Event event;
	while (mWindow.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::KeyPressed:
			handlePlayerInput(event.key.code, true);
			break;

		case sf::Event::KeyReleased:
			handlePlayerInput(event.key.code, false);
			break;

		case sf::Event::Closed:
			mWindow.close();
			break;
		}
	}
}



void Game::update(sf::Time elapsedTime)
{
	if (EntityManager::m_player->gameOver == false && EntityManager::m_player->winGame == false) {
	sf::Vector2f movement(0.f, 0.f);
	if (mIsMovingUp && EntityManager::m_player->CanMoveUp())
		movement.y -= PlayerSpeed;
	if (mIsMovingDown && EntityManager::m_player->CanMoveDown())
		movement.y += PlayerSpeed;
	
	if (mIsMovingLeft && EntityManager::m_player->CanMoveSideway()) {
		EntityManager::m_player->lastDirIsRight = false;
		movement.x -= PlayerSpeed;
	}
		
	if (mIsMovingRight && EntityManager::m_player->CanMoveSideway()) {
		EntityManager::m_player->lastDirIsRight = true;
		movement.x += PlayerSpeed;
	}
		
	mTexture.loadFromFile(EntityManager::m_player->Animate());
	mPlayer.setTexture(mTexture);

	movement.y -= EntityManager::m_player->JumpSpeed;
	movement.y += EntityManager::m_player->GravitySpeed;

	EntityManager::m_player->m_sprite.move(movement * elapsedTime.asSeconds());


	bool stop = false;

	for (std::shared_ptr <BouleEntity> boule : EntityManager::GetBoules()) {
		movement.y = 0;
		movement.x = 0;

		if (boule->GoRight()) {
			movement.x -= boule->speedEntity;
		}
		if (boule->GoLeft()) {
			movement.x += boule->speedEntity;
		}

		movement.y += boule->GravitySpeed;

		boule->m_sprite.move(movement * elapsedTime.asSeconds());
	}
	}
}

void Game::render()
{
	mWindow.clear();
	
	for (std::shared_ptr<Entity> entity : EntityManager::m_Entities)
	{
		if (entity->m_enabled == false)
		{
			continue;
		}

		mWindow.draw(entity->m_sprite);
	}

	if (EntityManager::m_player->gameOver == true) {
		mWindow.draw(mGameOver);
	}

	if (EntityManager::m_player->winGame == true) {
		mWindow.draw(mGameWin);
	}

	mWindow.draw(mStatisticsText);
	mWindow.display();
}

void Game::updateStatistics(sf::Time elapsedTime)
{
	mStatisticsUpdateTime += elapsedTime;
	mStatisticsNumFrames += 1;
	int test = 0;

	if (mStatisticsUpdateTime >= sf::seconds(1.0f))
	{
		mStatisticsText.setString(
			"Frames / Second = " + toString(mStatisticsNumFrames) + "\n" +
			"Time / Update = " + toString(mStatisticsUpdateTime.asMicroseconds() / mStatisticsNumFrames) + "us");

		mStatisticsUpdateTime -= sf::seconds(1.0f);
		mStatisticsNumFrames = 0;

		if (EntityManager::m_boule != nullptr) {
			bouleStep = EntityManager::m_boule->step;
			if (bouleStep > 1) {
				this->createBoule();
				bouleStep = 0;
				
			}
		}

	}

	
	//
	// Handle collision
	//

	if (mStatisticsUpdateTime >= sf::seconds(0.050f))
	{
		if (EntityManager::m_player->gameOver == false && EntityManager::m_player->winGame == false) {
			// Handle collision weapon enemies
			EntityManager::InitCollisions();
			EntityManager::InitJump();
			EntityManager::InitGravity();

			for (std::shared_ptr <BouleEntity> boule : EntityManager::GetBoules()) {
				boule->EnabledGravity();
			}

			mTexture.loadFromFile(EntityManager::m_player->Animate()); // Mario_small.png");
			mPlayer.setTexture(mTexture);
		}
		else {
			if (EntityManager::m_player->winGame == true) {
				mWindow.draw(mGameWin);
			}
			else {
				mWindow.draw(mGameOver);
			}

		}
	}
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
	if (key == sf::Keyboard::Up)
		mIsMovingUp = isPressed;
	else if (key == sf::Keyboard::Down)
		mIsMovingDown = isPressed;
	else if (key == sf::Keyboard::Left)
		mIsMovingLeft = isPressed;
	else if (key == sf::Keyboard::Right)
		mIsMovingRight = isPressed;


	if (key == sf::Keyboard::Space)
	{
		EntityManager::m_player->Jump();
	}
}

void Game::createBoule() {
	std::shared_ptr<BouleEntity> bouleb = std::make_shared<BouleEntity>();
	bouleb->m_sprite = mBoule;
	bouleb->m_type = EntityType::boule;
	bouleb->m_size = BouleTexture.getSize();
	bouleb->m_position = mBoule.getPosition();

	EntityManager::m_Entities.push_back(bouleb);
	EntityManager::AddBoule(bouleb);
}

void Game::GameOver() {
	std::shared_ptr<BouleEntity> monkey = std::make_shared<BouleEntity>();
	monkey->m_sprite = mGameOver;
	monkey->m_type = EntityType::boule;
	monkey->m_size = mGameOverTexture.getSize();
	monkey->m_position = mGameOver.getPosition();

	EntityManager::m_Entities.push_back(monkey);
	EntityManager::AddBoule(monkey);

}

void Game::GameWin() {
	std::shared_ptr<BouleEntity> monkey = std::make_shared<BouleEntity>();
	monkey->m_sprite = mGameWin;
	monkey->m_type = EntityType::boule;
	monkey->m_size = mGameWinTexture.getSize();
	monkey->m_position = mGameWin.getPosition();

	EntityManager::m_Entities.push_back(monkey);
	EntityManager::AddBoule(monkey);

}


