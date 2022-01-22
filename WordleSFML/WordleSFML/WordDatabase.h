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
	WordDatabase(std::default_random_engine& randomEngine);
	virtual ~WordDatabase() = default;

	bool isValidWord(const std::string& word) const;

	std::string getRandomWord() const;

private:
	// The database
	std::vector<std::string> _words;

	// Shared randomEngine used for all the randomisation.
	std::default_random_engine& _randomEngine;

	// Loads the word list in and sorts in alphabetically
	void loadDatabase();
};

