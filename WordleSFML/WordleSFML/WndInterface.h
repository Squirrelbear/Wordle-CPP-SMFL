#pragma once

#include <SFML/Graphics.hpp>

// States available for returning from WndInterface::getResultState().
enum WndResultState { NothingState, Finished, Restart, Menu, Quit };

/**
 * WndInterface class:
 * Defines a pure virtual class to use for multiple interfaces.
 *
 * @author Peter Mitchell
 * @version 2022.1
 */
class WndInterface
{
public:
	/**
	 * Initialise the interface with bounds and make it enabled.
	 *
	 * @param bounds Bounds of the interface.
	 */
	WndInterface(sf::IntRect bounds) : _bounds(bounds), _isEnabled(true) {};

	virtual ~WndInterface() = default;

	/**
	 * Update the interface elements.
	 *
	 * @param deltaTime Time since last update.
	 */
	virtual void update(const float deltaTime) = 0;

	/**
	 * Draw all elements to the interface.
	 *
	 * @param renderWindow Reference to the target window for rendering.
	 */
	virtual void draw(sf::RenderWindow& renderWindow) const = 0;

	/**
	 * Handle updates related to the mouse pressing at the specified position.
	 *
	 * @param mousePosition Position of the mouse cursor during the press.
	 * @param isLeft If true, the mouse button is left, otherwise is right.
	 */
	virtual void handleMousePress(const sf::Vector2i& mousePosition, bool isLeft) {};

	/**
	 * Handle updates related to the mouse being moved.
	 *
	 * @param mousePosition Position of the mouse during this movement.
	 */
	virtual void handleMouseMove(const sf::Vector2i& mousePosition) {};

	/**
	 * Handles the key input from a keyboard action.
	 *
	 * @param keyCode The key that was pressed.
	 */
	virtual void handleKeyInput(const sf::Keyboard::Key key) {};

	/**
	 * Change the enabled state of this object.
	 *
	 * @param enabled New state to set the enabled/disabled state of this object.
	 */
	void setEnabled(bool enabled) { _isEnabled = enabled; };

	/**
	 * Get the current enabled state of the object.
	 *
	 * @return True if the object is enabled.
	 */
	bool isEnabled() const { return _isEnabled; }

	// By default this method returns WndResultState::Nothing unless overriden.
	virtual WndResultState getResultState() const { return WndResultState::NothingState; };

protected:
	// Bounds of this interface.
	sf::IntRect _bounds;
	
	// State of whether the object is enabled so it can be used for managing updates.
	bool _isEnabled;
};

