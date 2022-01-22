#include "PuzzleWnd.h"

PuzzleWnd::PuzzleWnd(const sf::IntRect & bounds, const sf::Font & font, const std::string& solution)
	: WndInterface(bounds), _font(font), _gameTitle("Wordle", font, 50), _author("By Peter Mitchell", font, 15),
	_keyboard(bounds, font), _guessGrid(bounds, font, solution, 6)
{
	_gameTitle.setPosition(sf::Vector2f(5, 5));
	_author.setPosition(sf::Vector2f(5, 5 + 10 + 50));
	_currentState = WndResultState::NothingState;
}

PuzzleWnd::~PuzzleWnd()
{
}

void PuzzleWnd::update(const float deltaTime)
{
	if (_guessGrid.isSolved()) {
		_currentState = WndResultState::Finished;
	}
}

void PuzzleWnd::draw(sf::RenderWindow & renderWindow) const
{
	renderWindow.draw(_gameTitle);
	renderWindow.draw(_author);
	_keyboard.draw(renderWindow);
	_guessGrid.draw(renderWindow);
}

void PuzzleWnd::handleMousePress(const sf::Vector2i & mousePosition, bool isLeft)
{
	_keyboard.handleMousePress(mousePosition, isLeft);
	int action = _keyboard.getActionIDReset();
	if (action == static_cast<int>('<')) {
		_guessGrid.backSpace();
	}
	else if (action == 1) {
		_guessGrid.checkSolution();
	}
	else if (action != -1) {
		_guessGrid.tryInsertLetter(static_cast<char>(action));
	}
}

void PuzzleWnd::handleMouseMove(const sf::Vector2i & mousePosition)
{
	_keyboard.handleMouseMove(mousePosition);
}

void PuzzleWnd::handleKeyInput(const sf::Keyboard::Key key)
{
	_guessGrid.handleKeyInput(key);
	if (_guessGrid.getKeyCheckReset()) {
		_keyboard.applyRules(_guessGrid.getAllRules());
	}
}

WndResultState PuzzleWnd::getResultState() const
{
	return _currentState;
}
