#include "HistogramBar.h"

HistogramBar::HistogramBar(const sf::IntRect & bounds, const sf::Font& font, const int title, const int value, const int max)
{
	_titleText = std::make_unique<sf::Text>(std::to_string(title), font, 20);
	_titleText->setPosition(sf::Vector2f(bounds.left, bounds.top + bounds.height/2 - 10));
	
	_valueText = std::make_unique<sf::Text>(std::to_string(value), font, 20);
	int width = (bounds.width - 20) * value / max;
	if (width < _valueText->getGlobalBounds().width + 20) {
		width = _valueText->getGlobalBounds().width + 20;
	}
	sf::IntRect barRect(bounds.left + 20, bounds.top, width, bounds.height);
	_bar = std::make_unique<sf::RectangleShape>(sf::Vector2f(barRect.width, barRect.height));
	_bar->setFillColor(sf::Color(40, 40, 40));
	_bar->setPosition(sf::Vector2f(barRect.left, barRect.top));

	_valueText->setPosition(sf::Vector2f(barRect.left + barRect.width - 20, bounds.top + bounds.height / 2 - 13));
}

void HistogramBar::draw(sf::RenderWindow & renderWindow) const
{
	renderWindow.draw(*_titleText);
	renderWindow.draw(*_bar);
	renderWindow.draw(*_valueText);
}

void HistogramBar::setBarColour(const sf::Color & colour)
{
	_bar->setFillColor(colour);
}
