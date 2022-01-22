#pragma once
#include "WndInterface.h"
#include "Button.h"

/*
Keyboard class:
Defines a keyboard that positions itself at the bottom centrally within the specified bounds.

@author Peter Mitchell
@version 2022.1
*/
class KeyboardWnd :
	public WndInterface
{
public:
	// Initialises the keyboard to centre itself at the bottom middle of bounds.
	KeyboardWnd(const sf::IntRect& bounds, const sf::Font& font);
	virtual ~KeyboardWnd() = default;

	// Does nothing.
	virtual void update(const float deltaTime) override {};

	// Draws all the buttons on the keyboard.
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

	// Gets the value of actionID and resets it to default -1.
	int getActionIDReset();

	// Applies rule colours to keyboard keys
	void applyRules(std::vector<std::string> rules);

private:
	// List of buttons on the keyboard
	std::vector<Button> _buttons;

	// Current actionID
	int _actionID;

	// Initialises all the buttons for the keyboard.
	void initialiseButtons(const sf::Font& font);
};

