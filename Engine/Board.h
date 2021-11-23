#pragma once

#include "Graphics.h"
#include "Location.h"

class Board
{
public:
	Board(Graphics& gfx);
	void drawBoard();
	void drawCell(const Location& loc, const Color& color);
	int getHeight() const;
	int getBorderSize() const;
	int getWidth() const;
	bool isInsideBoard(const Location& loc) const;
private:
	static constexpr Color tileColour1 = { 20, 20, 20 };
	static constexpr Color tileColour2 = { 40, 40, 40 };
	static constexpr int HEIGHT = 40;
	static constexpr int WIDTH = 40;
	static constexpr int DIMENSION = 20;
	static constexpr int BORDER = 1;
	Graphics& gfx;
};

