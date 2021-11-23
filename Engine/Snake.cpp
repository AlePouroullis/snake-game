#include "Snake.h"

// added comment 2

Snake::Segment::Segment(const Location& loc, Color c)
	:
	loc(loc),
	c(c)
{
}

Location Snake::Segment::getLocation() const {
	return loc;
}

Snake::Snake(const Location& loc) {
	Segment head(loc, Snake::headColour);
	segments.push_back(head);
}

void Snake::grow() {
	Segment segment(last_location, Snake::bodyColour);
	segments.push_back(segment);
}

void Snake::setDir(int dir) {
	if (dir == UP && direction != DOWN)
		this->direction = dir;
	else if (dir == DOWN && direction != UP)
		this->direction = dir;
	else if (dir == RIGHT && direction != LEFT)
		this->direction = dir;
	else if (dir == LEFT && direction != RIGHT)
		this->direction = dir;
}

void Snake::Segment::follow(const Segment& next) {
	loc = next.loc;
}

Location Snake::getHead() const {
	return segments.front().getLocation();
}

void Snake::Segment::move(const int dir) {
	if (dir == LEFT) 
		loc.x -= 1;
	else if (dir == RIGHT) 
		loc.x += 1;
	else if (dir == UP) 
		loc.y -= 1;
	else if (dir == DOWN) 
		loc.y += 1;
}

bool Snake::isInSnake(const Location& loc) const {
	for (int i = 0; i < segments.size(); i++) {
		if (loc == segments[i].getLocation())
			return true;
	}
	return false;
}

bool Snake::collidingWithSelf() const {
	for (int i = 1; i < segments.size(); i++) {
		if (getHead() == segments[i].getLocation())
			return true;
	}
	return false;
}

void Snake::move() {
	last_location = segments.back().getLocation();
	for (int i = segments.size()-1; i > 0; i--) 
		segments[i].follow(segments[i-1]);
	
	Segment& head = segments.front();
	head.move(direction);
}

void Snake::Segment::draw(Board& board) const {
	board.drawCell(loc, c);
}

void Snake::draw(Board& board) const {
	for (Segment segment : segments) {
		segment.draw(board);
	}
}
