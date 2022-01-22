#include "PlayHistory.h"
#include <iostream>
#include <fstream>

PlayHistory::PlayHistory(const std::string & saveFileName)
	: _saveFileName(saveFileName)
{
	loadFile();
}

void PlayHistory::insertHistory(const int countToIncrement)
{
	if (countToIncrement < 0 || countToIncrement >= _playHistory.size()) {
		std::cerr << "ERROR: Failed to insert " << countToIncrement << " into history." << std::endl;
		return;
	}

	++_playHistory.at(countToIncrement).second;
	saveFile();
}

const std::vector<std::pair<int, int>>& PlayHistory::getHistory() const
{
	return _playHistory;
}

void PlayHistory::loadFile()
{
	std::ifstream file(_saveFileName);
	if (!file.is_open()) {
		std::cout << "Failed to open a save file. Using default values." << std::endl;
		initialiseDefault();
		return;
	}

	int key, value;
	for (int i = 0; i < 6; i++) {
		file >> key >> value;
		if (file.fail()) {
			std::cout << "Failed to read expected data from save file. Using default values." << std::endl;
			initialiseDefault();
			file.close();
			return;
		}
		_playHistory.emplace_back(std::pair<int, int>(key, value));
	}

	file.close();
}

void PlayHistory::saveFile()
{
	std::ofstream file(_saveFileName);
	if (!file.is_open()) {
		std::cout << "Failed to open file to save your win. Will not be saved." << std::endl;
		return;
	}

	for (const auto& element : _playHistory) {
		file << element.first << " " << element.second << " ";
	}

	file.close();
}

void PlayHistory::initialiseDefault()
{
	for (int i = 0; i < 6; i++) {
		_playHistory.emplace_back(std::pair<int, int>(i+1, 0));
	}
}
