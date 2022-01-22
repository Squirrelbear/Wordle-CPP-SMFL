#pragma once
#include "WndInterface.h"
#include <random>
#include "WordDatabase.h"

/*
Game class:
Manages instances of the puzzle window.

@author: Peter Mitchell
@version 2022.1
*/
class Game
{
public:
	// Initialises the game with the Lobby.
	Game(const sf::IntRect& gameBounds, const sf::Font& font);
	virtual ~Game();

	// Updates the current state of the active window.
	void update(const float deltaTime);

	// Draws the current window.
	void draw(sf::RenderWindow & renderWindow) const;

	// Handles passing events on to the active interface.
	void handleMousePress(const sf::Vector2i& mousePosition, bool isLeft);

	// Handles passing the mouse moved event to the active interface.
	void handleMouseMove(const sf::Vector2i& mousePosition);

	// Handles passing key pressed event to the active interface.
	void handleKeyInput(const sf::Keyboard::Key key);

	//  When true, the game should end.
	bool getGameCloseRequested();

private:
	// Bounds of the game area.
	const sf::IntRect _bounds;

	// Reference to the font
	const sf::Font& _font;

	// Shared randomEngine used for all the randomisation.
	std::default_random_engine _randomEngine;

	// Reference to the current active interface.
	WndInterface* _activeInterface;

	// Reference to the current active overlay if one exists.
	WndInterface* _activeOverlay;

	// When true, the game should end.
	bool _terminateGame;

	// Collection of words
	std::unique_ptr<WordDatabase> _wordDatabase;
};
