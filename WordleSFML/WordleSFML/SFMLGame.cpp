#include "SFMLGame.h"

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
#define FONT_FILE_PATH "../Fonts/arial.ttf"

SFMLGame::SFMLGame()
	: _window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Wordle - by Peter Mitchell (2022)", sf::Style::Titlebar | sf::Style::Close),
	_font(loadFont()), _game(sf::IntRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT), _font)
{
}

void SFMLGame::gameLoop()
{
	sf::Clock clock;
	while (_window.isOpen())
	{
		sf::Time elapsed = clock.restart();
		float deltaTime = elapsed.asSeconds();
		sf::Event event;
		while (_window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				_window.close();
			}
			else if (event.type == sf::Event::MouseButtonPressed) {
				_game.handleMousePress(sf::Vector2i(event.mouseButton.x, event.mouseButton.y), event.mouseButton.button == sf::Mouse::Left);
			}
			else if (event.type == sf::Event::MouseMoved) {
				_game.handleMouseMove(sf::Vector2i(event.mouseMove.x, event.mouseMove.y));
			}
			else if (event.type == sf::Event::KeyPressed) {
				_game.handleKeyInput(event.key.code);
			}
		}
		_game.update(deltaTime);

		_window.clear(sf::Color::Black);
		_game.draw(_window);
		_window.display();

		if (_game.getGameCloseRequested()) {
			_window.close();
		}
	}
}

sf::Font SFMLGame::loadFont()
{
	sf::Font font;
	if (!font.loadFromFile(FONT_FILE_PATH))
	{
		throw("Failed to load font.");
	}

	return font;
}
