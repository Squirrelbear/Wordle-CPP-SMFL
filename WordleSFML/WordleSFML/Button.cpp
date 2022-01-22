#include "Button.h"

Button::Button(const sf::IntRect & bounds, const std::string & text, const int actionID, const sf::Font& font)
	: _bounds(bounds), _text(text), _actionID(actionID), 
	_background(sf::Vector2f(_bounds.width - 2, _bounds.height - 2)),
	_textVisual(text, font, 30)
{
	_textVisual.setFillColor(sf::Color::White);
	_textVisual.setStyle(sf::Text::Bold);
	_textVisual.setPosition(sf::Vector2f(_bounds.left + _bounds.width / 2 - _textVisual.getGlobalBounds().width / 2, _bounds.top + _bounds.height / 2 - 20));
	
	_background.setPosition(sf::Vector2f(_bounds.left + 1, _bounds.top + 1));
	_background.setFillColor(sf::Color(5, 5, 5));
	_background.setOutlineThickness(1);
	_background.setOutlineColor(sf::Color::White);

	_isHovered = false;
}

void Button::draw(sf::RenderWindow & renderWindow) const
{
	renderWindow.draw(_background);
	renderWindow.draw(_textVisual);
}

int Button::getActionID() const
{
	return _actionID;
}

void Button::setHovering(const bool isHovering)
{
	_isHovered = isHovering;
	_background.setOutlineThickness(_isHovered ? 3 : 1);
}

bool Button::isPositionInside(const sf::Vector2i & mousePosition) const
{
	return _bounds.contains(mousePosition);
}

void Button::setBackgroundColour(const sf::Color & colour)
{
	_background.setFillColor(colour);
}
