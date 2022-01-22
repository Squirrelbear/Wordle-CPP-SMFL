#include "PuzzleWnd.h"

PuzzleWnd::PuzzleWnd(const sf::IntRect & bounds, const sf::Font & font, const std::string& solution)
	: WndInterface(bounds), _font(font), testText("Test text", font, 50),
	_keyboard(bounds, font), _guessGrid(bounds, font, solution, 6)
{
}

PuzzleWnd::~PuzzleWnd()
{
}

void PuzzleWnd::update(const float deltaTime)
{
}

void PuzzleWnd::draw(sf::RenderWindow & renderWindow) const
{
	renderWindow.draw(testText);
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
