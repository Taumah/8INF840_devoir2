#include "Point.h"

Point::Point(const size_t qty_dimensions) {
	coord = new vector<int>(qty_dimensions);
}

Point::~Point() {
	delete coord;
}

int Point::getCoord(int index)
{
	if (index < coord.size()) {
		return coord.at(index);
	}
	else {
		cout << "index out of range" << endl;
		return NULL;
	}
	
}

bool Point::isEqualTo(Point other)
{
	for (int i = 0; i < coord.size(); i += 1) {
		if (coord[i] != other.getCoord[i]) {
			return false;
		}
	}
	return true;
}

