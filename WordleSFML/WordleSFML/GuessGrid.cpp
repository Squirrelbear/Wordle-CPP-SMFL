#include "GuessGrid.h"

GuessGrid::GuessGrid(const sf::IntRect & bounds, const sf::Font & font, const std::string& solution, const int maxGuesses)
	: WndInterface(bounds), _solution(solution)
{
	initialiseAllGuesses(font, solution.length(), maxGuesses);
	_solved = false;
	_currentWordIndex = 0;
	_insertPosition = 0;
}

void GuessGrid::draw(sf::RenderWindow & renderWindow) const
{
	for (const auto& row : _guessLetters) {
		for (const auto& letter : row) {
			letter.draw(renderWindow);
		}
	}
}

void GuessGrid::tryInsertLetter(const char letter)
{
	// If max guesses reached, solved, or current guess is full do nothing.
	if (_currentWordIndex == _guessLetters.size() || _solved || _insertPosition == _guessLetters.at(_currentWordIndex).size()) 
		return;

	// Insert the letter and move one position forward.
	_guessLetters.at(_currentWordIndex).at(_insertPosition).setLetter(letter);
	++_insertPosition;
}

void GuessGrid::backSpace()
{
	// Do nothing if there are no letters to backspace at or it has been solved
	if (_solved || _insertPosition == 0 || _currentWordIndex == _guessLetters.size()) 
		return;

	// Move back and erase one
	--_insertPosition;
	_guessLetters.at(_currentWordIndex).at(_insertPosition).setLetter(' ');
}

void GuessGrid::checkSolution()
{
	// If solved or word is not full do nothing.
	if (_solved || _insertPosition != _guessLetters.at(_currentWordIndex).size())
		return;

	int solveCount = 0;
	for (int i = 0; i < _guessLetters.at(_currentWordIndex).size(); i++) {
		if (_guessLetters.at(_currentWordIndex).at(i).getLetter() == _solution.at(i)) {
			_guessLetters.at(_currentWordIndex).at(i).setBackgroundColour(sf::Color(93, 141, 74));
			++solveCount;
		}
	}

	++_currentWordIndex;
	_insertPosition = 0;
	if (solveCount == _guessLetters.at(_currentWordIndex).size()) {
		_solved = true;
	}
}

void GuessGrid::initialiseAllGuesses(const sf::Font & font, const int wordLength, const int maxGuesses)
{
	int elementHeight = 60;
	int elementWidth = 60;

	int leftSide = _bounds.left + _bounds.width / 2 - ((elementWidth + 10) * wordLength) / 2;
	int posY = _bounds.top + 30;
	int posX = leftSide;

	for (int i = 0; i < maxGuesses; i++, posY += elementHeight + 10, posX = leftSide) {
		std::vector<PuzzleLetter> row;

		for (int j = 0; j < wordLength; j++, posX += elementWidth + 10) {
			row.emplace_back(PuzzleLetter(sf::IntRect(posX, posY, elementHeight, elementWidth), font));
		}

		_guessLetters.emplace_back(row);
	}
}
