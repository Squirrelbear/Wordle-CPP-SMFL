#include "Game.h"
#include <chrono>       // std::chrono::system_clock
#include "PuzzleWnd.h"

Game::Game(const sf::IntRect & gameBounds, const sf::Font & font)
	: _bounds(gameBounds), _font(font)
{
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	_randomEngine = std::default_random_engine(seed);
	_terminateGame = false;
	_activeInterface = nullptr;
	_activeInterface = new PuzzleWnd(gameBounds, font, "YEAST");
}

Game::~Game()
{
	if (_activeInterface != nullptr) {
		delete _activeInterface;
	}
}

void Game::update(const float deltaTime)
{
	if (_activeInterface != nullptr) {
		_activeInterface->update(deltaTime);
	}
}

void Game::draw(sf::RenderWindow & renderWindow) const
{
	if (_activeInterface != nullptr) {
		_activeInterface->draw(renderWindow);
	}
}

void Game::handleMousePress(const sf::Vector2i & mousePosition, bool isLeft)
{
	if (_activeInterface != nullptr) {
		_activeInterface->handleMousePress(mousePosition, isLeft);
	}
}

void Game::handleMouseMove(const sf::Vector2i & mousePosition)
{
	if (_activeInterface != nullptr) {
		_activeInterface->handleMouseMove(mousePosition);
	}
}

void Game::handleKeyInput(const sf::Keyboard::Key key)
{
	if (_activeInterface != nullptr) {
		_activeInterface->handleKeyInput(key);
	}
}

bool Game::getGameCloseRequested()
{
	return _terminateGame;
}
