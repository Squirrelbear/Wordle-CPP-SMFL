#include "PuzzleWnd.h"

PuzzleWnd::PuzzleWnd(const sf::IntRect & bounds, const sf::Font & font, std::default_random_engine & randomEngine)
	: WndInterface(bounds), _font(font), _randomEngine(randomEngine), testText("Test text", font, 50)
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
}
