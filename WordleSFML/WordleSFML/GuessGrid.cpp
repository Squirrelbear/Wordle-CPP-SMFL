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

void GuessGrid::handleKeyInput(const sf::Keyboard::Key key)
{
	switch (key) {
		case sf::Keyboard::Backspace:
			backSpace();
			break;
		case sf::Keyboard::Enter:
			checkSolution();
			break;
		case sf::Keyboard::Key::A:
			tryInsertLetter('A');
			break;
		case sf::Keyboard::Key::B:
			tryInsertLetter('B');
			break;
		case sf::Keyboard::Key::C:
			tryInsertLetter('C');
			break;
		case sf::Keyboard::Key::D:
			tryInsertLetter('D');
			break;
		case sf::Keyboard::Key::E:
			tryInsertLetter('E');
			break;
		case sf::Keyboard::Key::F:
			tryInsertLetter('F');
			break;
		case sf::Keyboard::Key::G:
			tryInsertLetter('G');
			break;
		case sf::Keyboard::Key::H:
			tryInsertLetter('H');
			break;
		case sf::Keyboard::Key::I:
			tryInsertLetter('I');
			break;
		case sf::Keyboard::Key::J:
			tryInsertLetter('J');
			break;
		case sf::Keyboard::Key::K:
			tryInsertLetter('K');
			break;
		case sf::Keyboard::Key::L:
			tryInsertLetter('L');
			break;
		case sf::Keyboard::Key::M:
			tryInsertLetter('M');
			break;
		case sf::Keyboard::Key::N:
			tryInsertLetter('N');
			break;
		case sf::Keyboard::Key::O:
			tryInsertLetter('O');
			break;
		case sf::Keyboard::Key::P:
			tryInsertLetter('P');
			break;
		case sf::Keyboard::Key::Q:
			tryInsertLetter('Q');
			break;
		case sf::Keyboard::Key::R:
			tryInsertLetter('R');
			break;
		case sf::Keyboard::Key::S:
			tryInsertLetter('S');
			break;
		case sf::Keyboard::Key::T:
			tryInsertLetter('T');
			break;
		case sf::Keyboard::Key::U:
			tryInsertLetter('U');
			break;
		case sf::Keyboard::Key::V:
			tryInsertLetter('V');
			break;
		case sf::Keyboard::Key::W:
			tryInsertLetter('W');
			break;
		case sf::Keyboard::Key::X:
			tryInsertLetter('X');
			break;
		case sf::Keyboard::Key::Y:
			tryInsertLetter('Y');
			break;
		case sf::Keyboard::Key::Z:
			tryInsertLetter('Z');
			break;
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
	for (int i = 0; i < _solution.length(); i++) {
		char guess = _guessLetters.at(_currentWordIndex).at(i).getLetter();
		if (guess == _solution.at(i)) {
			_guessLetters.at(_currentWordIndex).at(i).setSolutionState(PuzzleLetter::SolutionState::CORRECT);
			++solveCount;
		}
		else {
			// If the letter is in the solution
			int requiredLetterCount = std::count(_solution.begin(), _solution.end(), guess);
			if (requiredLetterCount > 0) {
				// Find the matching positions for incorrect placement and the number of correct placements.
				int correctPositionThisLetter = 0;
				std::vector<int> outOfPositionPositions;
				for (int j = 0; j < _guessLetters.at(_currentWordIndex).size(); j++) {
					if (guess == _guessLetters.at(_currentWordIndex).at(j).getLetter()) {
						if (guess == _solution.at(j)) {
							correctPositionThisLetter++;
						}
						else {
							outOfPositionPositions.emplace_back(j);
						}
					}
				}
				// Remove excessive letters
				while (correctPositionThisLetter + outOfPositionPositions.size() > requiredLetterCount) {
					outOfPositionPositions.pop_back();
				}
				
				// Flag as wrong position only if within reaching the minimum.
				if (std::find(outOfPositionPositions.begin(), outOfPositionPositions.end(), i) != outOfPositionPositions.end()) {
					_guessLetters.at(_currentWordIndex).at(i).setSolutionState(PuzzleLetter::SolutionState::WRONG_POS);
				}
				else {
					_guessLetters.at(_currentWordIndex).at(i).setSolutionState(PuzzleLetter::SolutionState::NO_STATE);
				}
			}
			else {
				_guessLetters.at(_currentWordIndex).at(i).setSolutionState(PuzzleLetter::SolutionState::NO_STATE);
			}
		}
	}

	++_currentWordIndex;
	_insertPosition = 0;
	if (solveCount == _solution.length()) {
		_solved = true;
	}
}

bool GuessGrid::isSolved() const
{
	return _solved;
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
