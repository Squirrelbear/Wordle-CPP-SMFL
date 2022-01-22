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

	// Updates the current state of the window.
	virtual void update(const float deltaTime) override;

	// Draws all the components of the PuzzleWnd.
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

	/**
	 * Handles the key input from a keyboard action.
	 *
	 * @param keyCode The key that was pressed.
	 */
	virtual void handleKeyInput(const sf::Keyboard::Key key) override;

	const GuessGrid& getGuessGrid() const;

	// Gets the state to check if the window is requesting an action.
	WndResultState getResultState() const override;

private:
	// Reference to the font used for elements on the window.
	const sf::Font& _font;

	// Title text
	sf::Text _gameTitle;

	// Author text
	sf::Text _author;

	// The keyboard used for clicking for input
	KeyboardWnd _keyboard;

	// The grid of guesses where the keyboards input goes.
	GuessGrid _guessGrid;

	// The current state of this window. Changes to finished when ready to close.
	WndResultState _currentState;
};

