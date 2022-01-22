#pragma once
#include "WndInterface.h"
#include "Button.h"

class KeyboardWnd :
	public WndInterface
{
public:
	KeyboardWnd(const sf::IntRect& bounds, const sf::Font& font);
	virtual ~KeyboardWnd();

	// Inherited via WndInterface
	virtual void update(const float deltaTime) override;
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
	std::vector<Button> _buttons;

	void initialiseButtons(const sf::Font& font);
};

