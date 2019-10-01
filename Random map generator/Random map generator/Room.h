#pragma once
#include <iostream>
#include <string>
enum types {
	Start,
	Normal,
	Boss,
	Treasure,
	Shop,
	Curse,
	Arena,
	Secret,
	Possible,
	None
};

class Room
{
public:

	Room(types type, int loc_x,int loc_y);
	~Room() = default ;

public:

	friend std::ostream & operator<<(std::ostream & os,const Room & obj);

public:

	types get_type() const;
	void set_type(types type);

private:

	types type;
	unsigned location_x;
	unsigned location_y;

};

