#include "PostGameWnd.h"

PostGameWnd::PostGameWnd(const sf::IntRect & bounds, const sf::Font & font, const std::string & solution, const bool wonGame, const int attempts)
	: WndInterface(bounds)
{
	_resultState = WndResultState::NothingState;

	_fullScreenBackground = std::make_unique<sf::RectangleShape>(sf::Vector2f(bounds.width, bounds.height));
	_fullScreenBackground->setFillColor(sf::Color(20, 20, 20, 150));

	_background = std::make_unique<sf::RectangleShape>(sf::Vector2f(bounds.width / 2, bounds.height / 2));
	_background->setFillColor(sf::Color(60, 60, 60, 230));
	_background->setOutlineColor(sf::Color::White);
	_background->setOutlineThickness(1);
	_background->setPosition(bounds.left + bounds.width / 4 + 1, bounds.top + bounds.height / 4 + 1);

	_buttons.emplace_back(Button(sf::IntRect(bounds.left + bounds.width / 2 - 225, bounds.top + bounds.height * 3 / 4 - 70, 200, 60), "New Word", 0, font));
	_buttons.emplace_back(Button(sf::IntRect(bounds.left + bounds.width / 2 + 25, bounds.top + bounds.height * 3 / 4 - 70, 200, 60), "Quit", 1, font));

}

void PostGameWnd::draw(sf::RenderWindow & renderWindow) const
{
	renderWindow.draw(*_fullScreenBackground);
	renderWindow.draw(*_background);
	for (const auto& button : _buttons) {
		button.draw(renderWindow);
	}
}

void PostGameWnd::handleMousePress(const sf::Vector2i & mousePosition, bool isLeft)
{
	for (auto& button : _buttons) {
		if (button.isPositionInside(mousePosition)) {
			if (button.getActionID() == 0) {
				_resultState = WndResultState::Restart;
			}
			else if (button.getActionID() == 1) {
				_resultState = WndResultState::Quit;
			}
		}
	}
}

void PostGameWnd::handleMouseMove(const sf::Vector2i & mousePosition)
{
	for (auto& button : _buttons) {
		button.setHovering(button.isPositionInside(mousePosition));
	}
}

WndResultState PostGameWnd::getResultState() const
{
	return _resultState;
}
