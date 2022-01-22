#include "HorizontalHistogram.h"

HorizontalHistogram::HorizontalHistogram(const sf::IntRect & bounds, const sf::Font & font, std::vector<std::pair<int, int>> data, const int highlightIndex)
{
	auto cmp = [](const std::pair<char, int>& a, const std::pair<char, int>& b) {
		return a.second < b.second;
	};
	int max = std::max_element(data.begin(), data.end(), cmp)->second;

	int padding = 5;
	int barHeight = bounds.height / data.size() - 10;

	for (int i = 0; i < data.size(); i++) {
		_bars.emplace_back(std::make_unique<HistogramBar>(sf::IntRect(bounds.left, bounds.top + i * (barHeight + padding), 
							bounds.width, barHeight), font, data.at(i).first, data.at(i).second, max));
	}

	if (highlightIndex >= 0 && highlightIndex <= _bars.size()) {
		_bars.at(highlightIndex)->setBarColour(sf::Color(93, 141, 74));
	}
}

void HorizontalHistogram::draw(sf::RenderWindow & renderWindow) const
{
	for (const auto& bar : _bars) {
		bar->draw(renderWindow);
	}
}
