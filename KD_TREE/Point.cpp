#include "Point.h"

using namespace std;

Point::Point(const size_t qty_dimensions) {
	coord = new vector<int>(qty_dimensions,0);
}

Point::Point(vector<int> *coords) : coord(coords){}

Point::Point(int* vals,int spaceDimension)
{
	coord = new vector<int>();
	for (size_t i = 0; i < spaceDimension; i++)
	{
		coord->push_back(vals[i]);
	}
}

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

bool Point::isEqualTo(Point* other)
{
	for (int i = 0; i < coord->size(); i += 1) {
		if (coord->at(i) != other->getCoord(i)) {
			return false;
		}
	}
	return true;
}

ostream& operator<<(ostream& os, const Point *p)
{
	os << "{ ";
	for (int i = 0; i < p->coord->size(); i += 1) {
		os << p->coord->at(i);
		if (i < p->coord->size() - 1) {
			os << ", ";
		}
	}
	return (os << "}" << endl);
}
