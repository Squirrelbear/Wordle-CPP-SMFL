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

	++_totalWon;
	++_totalPlayed;
	++_currentStreak;
	if (_currentStreak > _maxStreak) {
		_maxStreak = _currentStreak;
	}
	++_playHistory.at(countToIncrement).second;
	saveFile();
}

void PlayHistory::insertHistoryLoss()
{
	++_totalPlayed;
	_currentStreak = 0;
	saveFile();
}

const std::vector<std::pair<int, int>>& PlayHistory::getHistory() const
{
	return _playHistory;
}

int PlayHistory::getTotalPlayed() const
{
	return _totalPlayed;
}

int PlayHistory::getCurrentStreak() const
{
	return _currentStreak;
}

int PlayHistory::getMaxStreak() const
{
	return _maxStreak;
}

int PlayHistory::getWinPercent() const
{
	return _totalWon * 100 / _totalPlayed;
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
			std::cout << "Failed to read expected data from save file (histogram data). Using default values." << std::endl;
			initialiseDefault();
			file.close();
			return;
		}
		_playHistory.emplace_back(std::pair<int, int>(key, value));
	}
	file >> _totalPlayed >> _totalWon >> _currentStreak >> _maxStreak;

	if (file.fail()) {
		std::cout << "Failed to read expected data from save file (streak history). Using default values." << std::endl;
		initialiseDefault();
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
	file << _totalPlayed << " " << _totalWon << " " << _currentStreak << " " << _maxStreak;

	file.close();
}

void PlayHistory::initialiseDefault()
{
	for (int i = 0; i < 6; i++) {
		_playHistory.emplace_back(std::pair<int, int>(i+1, 0));
	}
	_maxStreak = 0;
	_currentStreak = 0;
	_totalPlayed = 0;
	_totalWon = 0;
}
