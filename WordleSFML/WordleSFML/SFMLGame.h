#pragma once

#include "Game.h"

/*
SMFLGame class:
Manages the sf::RenderWindow and game loop by passing information to the Game class.

@author: Peter Mitchell
@version 2022.1
*/
class SFMLGame
{
public:
	// Initialises the game ready to start.
	SFMLGame();
	virtual ~SFMLGame() = default;

	// Continues running the game until 
	void gameLoop();

private:
	// The window used for the game until it ends.
	sf::RenderWindow _window;

	// The font used throughout the game.
	sf::Font _font;

	// Reference to the Game used to manage all the interfaces within the game.
	Game _game;

	// Loads the font
	static sf::Font loadFont();
};


