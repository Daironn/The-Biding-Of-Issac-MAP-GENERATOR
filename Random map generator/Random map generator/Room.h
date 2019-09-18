#pragma once
#include <iostream>
#include <string>
enum types{
	None,
	Possible,
	Normal,
	Curse,
	Boss,
	Arena,
	RedArena,
	Start
};

class Room
{
public:

	Room(types type, int loc_x,int loc_y);
	~Room() = default ;
public:

	friend std::ostream & operator<<(std::ostream & os,const Room & obj);
public:
	inline types get_type() const;
	inline void set_type(types type);
private:

	types type;
	unsigned location_x;
	unsigned location_y;

};

