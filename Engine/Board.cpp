#include "Board.h"
#include <assert.h>

Board::Board(Graphics& gfx) :
	gfx(gfx)
{
}

// draws from top left corner
void Board::drawCell(const Location& loc, const Color& color){
	assert(loc.x >= 0);
	assert(loc.x < WIDTH);
	assert(loc.y >= 0);
	assert(loc.y < HEIGHT);
	gfx.drawRect(loc.x * DIMENSION, loc.y * DIMENSION, DIMENSION, DIMENSION, color);
}

int Board::getHeight() const {
	return HEIGHT;
}

int Board::getWidth() const {
	return WIDTH;
}

/*
void Board::drawSnake(const Snake& snake) {
	for(Segment seg : snake.segments)
}
*/

int Board::getBorderSize() const {
	return BORDER;
}

bool Board::isInsideBoard(const Location& loc) const {
	return (loc.x >= BORDER && loc.x < WIDTH - BORDER &&
		loc.y >= BORDER && loc.y < HEIGHT - BORDER);
}

void Board::drawBoard() {
	for (int i = 1; i < HEIGHT - 1; i++) {
		for (int j = 1; j < WIDTH - 1; j++) {
			if ((i % 2 == 0 && j % 2 == 0) || (i%2 == 1 && j%2 == 1))
				drawCell({ j,i }, tileColour1);
			else
				drawCell({ j, i }, tileColour2);
		}
	}
	gfx.drawBorder(BORDER * DIMENSION, BORDER * DIMENSION, { 65, 3, 252 } , 15);
}