#pragma once


struct Location {
	int x, y;
	bool operator ==(const Location loc) const {
		return (x == loc.x && y == loc.y);
	}
};