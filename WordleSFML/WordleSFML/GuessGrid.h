#pragma once
#include "WndInterface.h"
#include "PuzzleLetter.h"

/*
GuessGrid class:
Shows a grid of guesses with methods to insert or remove letters for the current guess.

@author: Peter Mitchell
@version: 2022.1
*/
class GuessGrid :
	public WndInterface
{
public:
	// Initialises the full grid as an empty set of elements waiting to be filled.
	GuessGrid(const sf::IntRect& bounds, const sf::Font& font, const std::string& solution, const int maxGuesses);
	virtual ~GuessGrid() = default;

	// Does nothing.
	virtual void update(const float deltaTime) override {};

	// Draws the grid of guessed letters.
	virtual void draw(sf::RenderWindow & renderWindow) const override;

	/**
	 * Handles the key input from a keyboard action.
	 *
	 * @param keyCode The key that was pressed.
	 */
	virtual void handleKeyInput(const sf::Keyboard::Key key) override;

	// Inserts the specified letter if there is room in the current attempt.
	void tryInsertLetter(const char letter);

	// Removes one letter if possible (does nothing if there is no letter for the current attempt to remove).
	void backSpace();

	// Tests the solution 
	void checkSolution();

	// Check if the solution has been reached
	bool isSolved() const;

	// Check if the user has run out of guesses
	bool hasMoreGuesses() const;

	// Gets expressions for all the rules for solving based on guesses
	std::vector<std::string> getAllRules() const;

	// Get and reset the changed via keys state.
	bool getKeyCheckReset();

	// Gets the solution that the user is matching
	std::string getSolution() const;

	// Gets a string representing the finished puzzle state.
	std::string getShareString() const;

private:
	// The collection of letters
	std::vector<std::vector<PuzzleLetter>> _guessLetters;

	// Position for next insertion
	int _insertPosition;

	// Position for the current word
	int _currentWordIndex;
	
	// When true it means the solution has been found.
	bool _solved;

	// Used keys to check
	bool _usedKeyCheck;

	// The solution to check against
	const std::string _solution;

	// Creates an empty grid based on the specified size
	void initialiseAllGuesses(const sf::Font & font, const int wordLength, const int maxGuesses);
};

