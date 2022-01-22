#include "PostGameWnd.h"

PostGameWnd::PostGameWnd(const sf::IntRect & bounds, const sf::Font & font, const std::string & solution, const bool wonGame, const int attempts, const std::unique_ptr<PlayHistory>& playHistory)
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

	_titleText = std::make_unique<sf::Text>((wonGame ? "You solved it!" : "Better Luck Next Time!"), font, 40);
	_titleText->setPosition(sf::Vector2f(bounds.left + bounds.width / 2 - _titleText->getGlobalBounds().width / 2, bounds.top + bounds.height / 4 + 10));
	_titleText->setFillColor(wonGame ? sf::Color(93, 141, 74) : sf::Color(230, 93, 74));

	_solutionText = std::make_unique<sf::Text>("Solution: " + solution, font, 30);
	_solutionText->setPosition(sf::Vector2f(bounds.left + bounds.width / 2 - _solutionText->getGlobalBounds().width / 2, bounds.top + bounds.height / 4 + 10 + 50));

	_buttons.emplace_back(Button(sf::IntRect(bounds.left + bounds.width / 2 - 225, bounds.top + bounds.height * 3 / 4 - 70, 200, 60), "New Word", 0, font));
	_buttons.emplace_back(Button(sf::IntRect(bounds.left + bounds.width / 2 + 25, bounds.top + bounds.height * 3 / 4 - 70, 200, 60), "Quit", 1, font));

	sf::IntRect histogramRect = sf::IntRect(bounds.left + bounds.width / 4 + 30, bounds.top + bounds.height / 4 + 10 + 50 + 40 + 10,
		bounds.width / 2 - 60, bounds.top + bounds.height * 3 / 4 - 70 - (bounds.top + bounds.height / 4 + 10 + 50 + 40));

	_histogram = std::make_unique<HorizontalHistogram>(histogramRect, font, playHistory->getHistory(), wonGame ? attempts-1 : -1);
}

void PostGameWnd::draw(sf::RenderWindow & renderWindow) const
{
	renderWindow.draw(*_fullScreenBackground);
	renderWindow.draw(*_background);
	renderWindow.draw(*_titleText);
	renderWindow.draw(*_solutionText);
	_histogram->draw(renderWindow);
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
