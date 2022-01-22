#include <SFML/Graphics.hpp>

/**
 * PuzzleLetter class:
 * Defines a letter that is drawn in a box.
 *
 * @author Peter Mitchell
 * @version 2022.1
 */
class PuzzleLetter
{
public:
	// Defines the state used for solutions
	enum SolutionState { NO_STATE, CORRECT, WRONG_POS };

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

	// Changes the background colour and stores the solution state.
	void setSolutionState(const SolutionState& solutionState);

	// Get solution state of this element
	SolutionState getSolutionState() const;

private:
	// The bounds of the rectangle used for isPositionInside().
	sf::IntRect _bounds;

	// The character shown on the puzzle letter.
	char _letter;

	// Element Background
	sf::RectangleShape _background;

	// Text Render
	sf::Text _textVisual;

	// The current solution state of this letter.
	SolutionState _currentState;

	// Changes the background colour to the specified colour.
	void setBackgroundColour(const sf::Color& colour);
};