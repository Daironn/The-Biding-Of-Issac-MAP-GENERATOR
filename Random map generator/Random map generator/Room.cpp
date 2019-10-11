#include "pch.h"
#include "Room.h"

std::ostream & operator<<(std::ostream & os, Room & obj)
{
	char type_char[1];
	if (obj.get_type() == ROOM::Normal) {
		type_char[0] = 'N';
	}
	else if (obj.get_type() == ROOM::Curse) {
		type_char[0] = 'C';
	}
	else if (obj.get_type() == ROOM::Boss) {
		type_char[0] = 'B';
	}
	else if (obj.get_type() == ROOM::Arena) {
		type_char[0] = 'A';
	}
	else if (obj.get_type() == ROOM::Shop) {
		type_char[0] = 'R';
	}
	else if (obj.get_type() == ROOM::Start) {
		type_char[0] = 'S';
	}
	else {
		type_char[0] = 'E';
	}

	os << type_char[0];

	return os;
}

Room::Room(ROOM::types type, int loc_x, int loc_y):
	type(type), location_x(loc_x),location_y(loc_y)
{
}

ROOM::types Room::get_type() const
{
	return this->type;
}

void Room::set_type(ROOM::types type)
{
	this->type = type;
}
