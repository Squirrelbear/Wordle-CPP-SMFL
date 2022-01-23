#include "Game.h"
#include <chrono>       // std::chrono::system_clock
#include "PuzzleWnd.h"
#include "PostGameWnd.h"

Game::Game(const sf::IntRect & gameBounds, const sf::Font & font)
	: _bounds(gameBounds), _font(font)
{
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	_randomEngine = std::default_random_engine(seed);
	_wordDatabase = std::make_unique<WordDatabase>(_randomEngine);
	_playHistory = std::make_unique<PlayHistory>("../Saves/save.dat");

	_terminateGame = false;
	_activeInterface = nullptr;
	_activeOverlay = nullptr;
	
	_activeInterface = new PuzzleWnd(gameBounds, font, _wordDatabase->getRandomWord());
}

Game::~Game()
{
	if (_activeInterface != nullptr) {
		delete _activeInterface;
	}
}

void Game::update(const float deltaTime)
{
	if (_activeOverlay != nullptr) {
		_activeOverlay->update(deltaTime);
		if (_activeOverlay->getResultState() == WndResultState::Restart) {
			delete _activeOverlay;
			_activeOverlay = nullptr;
			delete _activeInterface;
			_activeInterface = new PuzzleWnd(_bounds, _font, _wordDatabase->getRandomWord());
		}
		else if (_activeOverlay->getResultState() == WndResultState::Quit) {
			_terminateGame = true;
		}
	}
	else if (_activeInterface != nullptr) {
		_activeInterface->update(deltaTime);
		if (_activeInterface->getResultState() == WndResultState::Finished && _activeOverlay == nullptr) {
			auto guessGrid = dynamic_cast<PuzzleWnd*>(_activeInterface)->getGuessGrid();
			auto rules = guessGrid.getAllRules();
			std::string solution = guessGrid.getSolution();
			if (guessGrid.isSolved()) {
				_playHistory->insertHistory(rules.size() - 1);
			}
			else {
				_playHistory->insertHistoryLoss();
			}
			_activeOverlay = new PostGameWnd(_bounds, _font, solution, guessGrid.isSolved(), rules.size(), _playHistory);
		}
	}
}

void Game::draw(sf::RenderWindow & renderWindow) const
{
	if (_activeInterface != nullptr) {
		_activeInterface->draw(renderWindow);
	}

	if (_activeOverlay != nullptr) {
		_activeOverlay->draw(renderWindow);
	}
}

void Game::handleMousePress(const sf::Vector2i & mousePosition, bool isLeft)
{
	if (_activeOverlay != nullptr) {
		_activeOverlay->handleMousePress(mousePosition, isLeft);
	}
	else if (_activeInterface != nullptr) {
		_activeInterface->handleMousePress(mousePosition, isLeft);
	}
}

void Game::handleMouseMove(const sf::Vector2i & mousePosition)
{
	if (_activeOverlay != nullptr) {
		_activeOverlay->handleMouseMove(mousePosition);
	}
	else if (_activeInterface != nullptr) {
		_activeInterface->handleMouseMove(mousePosition);
	}
}

void Game::handleKeyInput(const sf::Keyboard::Key key)
{
	if (_activeOverlay != nullptr) {
		_activeOverlay->handleKeyInput(key);
	}
	else if (_activeInterface != nullptr) {
		_activeInterface->handleKeyInput(key);
	}
}

bool Game::getGameCloseRequested()
{
	return _terminateGame;
}
