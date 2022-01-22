#pragma once
#include "WndInterface.h"
#include "KeyboardWnd.h"
#include "GuessGrid.h"

/*
PuzzleWnd class:
Manages the keyboard and inputs from the user to play the Wordle game.

@author: Peter Mitchell
@version: 2022.1
*/
class PuzzleWnd :
	public WndInterface
{
public:
	// Initialises the Puzzle with a new puzzle to be played.
	PuzzleWnd(const sf::IntRect& bounds, const sf::Font& font, const std::string& solution);
	virtual ~PuzzleWnd();

	// TODO
	virtual void update(const float deltaTime) override;

	// TODO
	virtual void draw(sf::RenderWindow & renderWindow) const override;

	/**
	 * Handle updates related to the mouse pressing at the specified position.
	 *
	 * @param mousePosition Position of the mouse cursor during the press.
	 * @param isLeft If true, the mouse button is left, otherwise is right.
	 */
	virtual void handleMousePress(const sf::Vector2i& mousePosition, bool isLeft) override;

	/**
	 * Handle updates related to the mouse being moved.
	 *
	 * @param mousePosition Position of the mouse during this movement.
	 */
	virtual void handleMouseMove(const sf::Vector2i& mousePosition) override;

private:
	const sf::Font& _font;
	sf::Text testText;
	KeyboardWnd _keyboard;
	GuessGrid _guessGrid;
};

