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

	// Gets a reference to the history.
	const std::vector<std::pair<int, int>>& getHistory() const;

private:
	// The history containing all saved values.
	std::vector<std::pair<int, int>> _playHistory;

	// Reference to the filename for saving history.
	std::string _saveFileName;

	// Loads the file into the history.
	void loadFile();

	// Saves the history into the file.
	void saveFile();

	// Initialises a default dataset with 0s for everything.
	void initialiseDefault();
};

