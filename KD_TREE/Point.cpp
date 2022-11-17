#include "Point.h"

using namespace std;

Point::Point(const size_t qty_dimensions) {
	coord = vector<int>(qty_dimensions);
}

Point::~Point() {

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
		if (coord[i] != other.getCoord(i)) {
			return false;
		}
	}
	return true;
}

