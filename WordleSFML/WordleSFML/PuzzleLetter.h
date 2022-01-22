#include <SFML/Graphics.hpp>

/**
 * Button class:
 * Defines a simple button consisting of a rectangle region,
 * some text to centre in it, a hover state, and an
 * actionID that is available to give the button context.
 *
 * @author Peter Mitchell
 * @version 2022.1
 */
class PuzzleLetter
{
public:
	/**
	* Defaults to an empty letter at the position.
	*/
	PuzzleLetter(const sf::IntRect& bounds, const sf::Font& font);
	virtual ~PuzzleLetter() = default;

	// Draws the button
	void draw(sf::RenderWindow& renderWindow) const;

	// Gets the letter associated with the object
	char getLetter() const;

	// Sets the letter to the specified letter.
	void setLetter(const char letter);

	// Changes the background colour to the specified colour.
	void setBackgroundColour(const sf::Color& colour);

private:
	// The bounds of the rectangle used for isPositionInside().
	sf::IntRect _bounds;

	// The character shown on the puzzle letter.
	char _letter;

	// Element Background
	sf::RectangleShape _background;

	// Text Render
	sf::Text _textVisual;
};