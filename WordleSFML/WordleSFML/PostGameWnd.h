#pragma once
#include "WndInterface.h"
#include "Button.h"

/*
PostGameWnd class:
A class to represent the interface for when the player is viewing the results of their game.

@author: Peter Mitchell
@version 2022.1
*/
class PostGameWnd :
	public WndInterface
{
public:
	// Initialises the window with details about the game and a choice to start a new game or quit.
	PostGameWnd(const sf::IntRect& bounds, const sf::Font& font, const std::string& solution, const bool wonGame, const int attempts);
	virtual ~PostGameWnd() = default;

	// Does nothing
	virtual void update(const float deltaTime) override {};

	// Draws the interface elements.
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

	// Gets the WndResultState that changes from NothingState when the window is done.
	WndResultState getResultState() const override;

private:
	// Changes when the post-game is finished.
	WndResultState _resultState;

	// Buttons to choose what to do next
	std::vector<Button> _buttons;

	// Background for only the interface
	std::unique_ptr<sf::RectangleShape> _background;

	// Background to cover all elements
	std::unique_ptr<sf::RectangleShape> _fullScreenBackground;

	// Title text
	std::unique_ptr<sf::Text> _titleText;

	// Text showing the solution
	std::unique_ptr<sf::Text> _solutionText;
};

