#include "Point.h"

using namespace std;

Point::Point(const size_t qty_dimensions) {
	coord = new vector<int>(qty_dimensions,0);
}

Point::Point(vector<int> *coords) : coord(coords){}

Point::~Point()
{
	delete coord;
}

int Point::getCoord(int index)
{
	if (index >= 0 && index < coord->size()) {
		return coord->at(index);
	}
	else {
		cout << "index out of range" << endl;
		return NULL;
	}
	
}

bool Point::isEqualTo(Point other)
{
	for (int i = 0; i < coord->size(); i += 1) {
		if (coord->at(i) != other.getCoord(i)) {
			return false;
		}
	}
	return true;
}

