#include "Cell.h"

Cell::Cell(bool _north, bool _south, bool _east, bool _west) :
	north(_north), south(_south), east(_east), west(_west), visited(false){}
