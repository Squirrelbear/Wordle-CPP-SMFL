#pragma once
#include "WndInterface.h"
#include <random>

class PuzzleWnd :
	public WndInterface
{
public:
	PuzzleWnd(const sf::IntRect& bounds, const sf::Font& font, std::default_random_engine& randomEngine);
	virtual ~PuzzleWnd();

	// Inherited via WndInterface
	virtual void update(const float deltaTime) override;
	virtual void draw(sf::RenderWindow & renderWindow) const override;

private:
	const sf::Font& _font;
	std::default_random_engine& _randomEngine;
	sf::Text testText;
};

