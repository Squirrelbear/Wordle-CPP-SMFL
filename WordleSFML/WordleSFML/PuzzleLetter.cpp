#include "PuzzleLetter.h"

PuzzleLetter::PuzzleLetter(const sf::IntRect & bounds, const sf::Font & font)
	: _bounds(bounds), _letter(' '),
	_background(sf::Vector2f(_bounds.width - 2, _bounds.height - 2)),
	_textVisual('A', font, 30)
{
	_textVisual.setFillColor(sf::Color::White);
	_textVisual.setStyle(sf::Text::Bold);
	_textVisual.setPosition(sf::Vector2f(_bounds.left + _bounds.width / 2 - _textVisual.getGlobalBounds().width / 2, _bounds.top + _bounds.height / 2 - 20));
	_textVisual.setString(' ');

	_background.setPosition(sf::Vector2f(_bounds.left + 1, _bounds.top + 1));
	_background.setFillColor(sf::Color(5, 5, 5));
	_background.setOutlineThickness(1);
	_background.setOutlineColor(sf::Color::White);
}

void PuzzleLetter::draw(sf::RenderWindow & renderWindow) const
{
	renderWindow.draw(_background);
	renderWindow.draw(_textVisual);
}

char PuzzleLetter::getLetter() const
{
	return _letter;
}

void PuzzleLetter::setLetter(const char letter)
{
	_letter = letter;
	_textVisual.setString(letter);
}

void PuzzleLetter::setBackgroundColour(const sf::Color & colour)
{
	_background.setFillColor(colour);
}
