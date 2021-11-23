#pragma once

#include <utility>
#include "Graphics.h"
#include "Location.h"
#include "Board.h"
#include "snake.h"
#include <random>

class Food
{
public: 
	Food(std::mt19937 & rng, const Board& board, const Snake& snake);
	void respawn(std::mt19937 & rng, const Board& board, const Snake& snake);
	void draw(Board& board) const;
	Location getLocation() const;
	void glow();
private:
	Color c = { 0, 205, 0 };
	bool colourIsIncreasing = false;
	static constexpr int glowInterval = 15;
	Location loc;
};

