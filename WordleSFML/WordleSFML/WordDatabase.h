#pragma once

#include <vector>
#include <random>

/*
WordDatabase class:
Manages a collection of words.

@author: Peter Mitchell
@version 2022.1
*/
class WordDatabase
{
public:
	// Initialises the word database with the associated file
	WordDatabase(std::default_random_engine& randomEngine);
	virtual ~WordDatabase() = default;

	// Returns true if the word specified is a word in the database
	bool isValidWord(const std::string& word) const;

	// Returns a random word from the database.
	std::string getRandomWord() const;

private:
	// The database
	std::vector<std::string> _words;

	// Shared randomEngine used for all the randomisation.
	std::default_random_engine& _randomEngine;

	// Loads the word list in and sorts in alphabetically
	void loadDatabase();
};

