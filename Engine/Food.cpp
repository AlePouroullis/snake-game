#include "Food.h"


Food::Food(std::mt19937& rng, const Board& board, const Snake& snake)
{
	respawn(rng, board, snake);
}

void Food::respawn(std::mt19937& rng, const Board& board, const Snake& snake) {
	std::uniform_int_distribution<int> xPos(1 + board.getBorderSize(), board.getWidth() - 2 - board.getBorderSize());
	std::uniform_int_distribution<int> yPos(1 + board.getBorderSize(), board.getHeight() - 2 - board.getBorderSize());
	Location new_loc;
	do {
		new_loc = { xPos(rng), yPos(rng) };

	} while (snake.isInSnake(new_loc));
	loc = new_loc;
	c = { 0, 205, 0 };
	colourIsIncreasing = true;
}

void Food::glow() {
	int r = c.GetR();
	int g = c.GetG();
	int b = c.GetB();
	if (colourIsIncreasing) {
		if (g + glowInterval >= 255) {
			g = 255;
		}
		else
			g += glowInterval;
		// r and b are always the same value so it's not necessary to check both.
		if (r + glowInterval >= 255) {
			r = b = 255;
			colourIsIncreasing = false;
		}
		else {
			r += glowInterval;
			b += glowInterval;
		}
	}
	else {
		if (g - glowInterval <= 205)
			g = 205;
		else
			g -= glowInterval;

		if (r - glowInterval <= 0) {
			r = b = 0;
			colourIsIncreasing = true;
		}
		else {
			r -= glowInterval;
			b -= glowInterval;
		}
	}
	c = Color(r, g, b);
}


void Food::draw(Board& board) const {
	board.drawCell(loc, c);
}

Location Food::getLocation() const {
	return { loc.x, loc.y };
}

