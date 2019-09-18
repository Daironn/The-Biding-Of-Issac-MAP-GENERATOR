#include "pch.h"
#include "Room.h"

std::ostream & operator<<(std::ostream & os, Room & obj)
{
	char type_char;
	if (obj.get_type() == Normal) {
		type_char = 'N';
	}
	else if (obj.get_type() == Curse) {
		type_char = 'C';
	}
	else if (obj.get_type() == Boss) {
		type_char = 'B';
	}
	else if (obj.get_type() == Arena) {
		type_char = 'A';
	}
	else if (obj.get_type() == Shop) {
		type_char = 'R';
	}
	else if (obj.get_type() == Start) {
		type_char = 'S';
	}
	else {
		type_char = 'E';
	}

	os << type_char;

	return os;
}

Room::Room(types type, int loc_x, int loc_y):
	type(type), location_x(loc_x),location_y(loc_y)
{
}

types Room::get_type() const
{
	return this->type;
}

void Room::set_type(types type)
{
	this->type = type;
}
