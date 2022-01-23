#pragma once
#include <vector>

/*
PlayHistory class:
Manages a history of played games storing the results to a file.

@author: Peter Mitchell
@version: 2022.1
*/
class PlayHistory
{
public:
	// Loads the save data from the specified file or creates a new dataset.
	PlayHistory(const std::string& saveFileName);
	virtual ~PlayHistory() = default;

	// Inserts into the history by incrementing the count by 1 if that element exists.
	void insertHistory(const int countToIncrement);

	// Inserts a loss
	void insertHistoryLoss();

	// Gets a reference to the history.
	const std::vector<std::pair<int, int>>& getHistory() const;

	// Gets the total played games
	int getTotalPlayed() const;

	// Gets the current streak of wins
	int getCurrentStreak() const;

	// Gets the maximum win streak
	int getMaxStreak() const;

	// Gets the win % as a whole number
	int getWinPercent() const;

private:
	// The history containing all saved values.
	std::vector<std::pair<int, int>> _playHistory;

	// Total games played
	int _totalPlayed;

	// Total games won
	int _totalWon;

	// Current win streak
	int _currentStreak;

	// Maximum streak
	int _maxStreak;

	// Reference to the filename for saving history.
	std::string _saveFileName;

	// Loads the file into the history.
	void loadFile();

	// Saves the history into the file.
	void saveFile();

	// Initialises a default dataset with 0s for everything.
	void initialiseDefault();
};

