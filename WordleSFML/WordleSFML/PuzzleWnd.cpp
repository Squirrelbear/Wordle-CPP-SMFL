#include "PuzzleWnd.h"

PuzzleWnd::PuzzleWnd(const sf::IntRect & bounds, const sf::Font & font, std::default_random_engine & randomEngine)
	: WndInterface(bounds), _font(font), _randomEngine(randomEngine), testText("Test text", font, 50),
	_keyboard(bounds, font)
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
}

void PuzzleWnd::handleMousePress(const sf::Vector2i & mousePosition, bool isLeft)
{
	_keyboard.handleMousePress(mousePosition, isLeft);
}

void PuzzleWnd::handleMouseMove(const sf::Vector2i & mousePosition)
{
	_keyboard.handleMouseMove(mousePosition);
}
