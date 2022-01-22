#pragma once
#include "WndInterface.h"
#include "PuzzleLetter.h"

class GuessGrid :
	public WndInterface
{
public:
	GuessGrid(const sf::IntRect& bounds, const sf::Font& font, const std::string& solution, const int maxGuesses);
	virtual ~GuessGrid() = default;

	// Does nothing.
	virtual void update(const float deltaTime) override {};

	// Draws the grid of guessed letters.
	virtual void draw(sf::RenderWindow & renderWindow) const override;

	// Inserts the specified letter if there is room in the current attempt.
	void tryInsertLetter(const char letter);

	// Removes one letter if possible (does nothing if there is no letter for the current attempt to remove).
	void backSpace();

	// Tests the solution 
	void checkSolution();

private:
	// The collection of letters
	std::vector<std::vector<PuzzleLetter>> _guessLetters;

	// Position for next insertion
	int _insertPosition;

	// Position for the current word
	int _currentWordIndex;
	
	// When true it means the solution has been found.
	bool _solved;

	// The solution to check against
	const std::string _solution;

	// Creates an empty grid based on the specified size
	void initialiseAllGuesses(const sf::Font & font, const int wordLength, const int maxGuesses);
};

