#include "Cell.h"

Cell::Cell(): 
	north(false), south(false), east(false), west(false), built(false), visited(false), parent(nullptr) {}

Cell::Cell(bool _north, bool _south, bool _east, bool _west) :
	north(_north), south(_south), east(_east), west(_west), built(false), visited(false), parent(nullptr) {}

ostream& operator<<(ostream& os, const Cell* c){

	int total = 0;
	total += c->north ? 1 : 0;
	total += c->south ? 2 : 0;
	total += c->east  ? 4 : 0;
	total += c->west  ? 8 : 0;
 
	string extra = "|";
	if (total < 10) {
		extra = " " + extra;
	}
 os << '|' << total <<  extra;

 return os;
}

