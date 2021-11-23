#pragma once

#include <vector>
#include <utility>
#include "Graphics.h"
#include "Location.h"
#include "Board.h"

class Snake {
	class Segment {
	public:
		Segment(const Location& loc, Color c);
		void follow(const Segment& next);
		void move(const int dir);
		void draw(Board& board) const;
		Location getLocation() const;
	private:
		Location loc;
		Color c;
	};
public: 
	Snake(const Location& loc);
	void move();
	void grow();
	Location getHead() const;
	void draw(Board& board) const;
	void setDir(const int dir);
	bool isInSnake(const Location& loc) const;
	bool collidingWithSelf() const;
private:
	static constexpr Color headColour = { 255, 51, 51 };
	static constexpr Color bodyColour = { 255, 204, 0 };
	static constexpr int LEFT = 0;
	static constexpr int RIGHT = 1;
	static constexpr int UP = 2;
	static constexpr int DOWN = 3;
	std::vector<Segment> segments;
	Location last_location;
	int direction;
};