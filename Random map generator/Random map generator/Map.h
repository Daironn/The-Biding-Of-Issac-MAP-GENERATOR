#pragma once
#include "Room.h"
#include <vector>
#include <map>

enum level {
	Basement,
	Cave,
	Necro,
	Womb,
	Catedral,
	Chest
};
class Map
{
public:

	Map(level level_type);
	~Map() = default;
public:

	void draw_map() const;
	void create_map_default();
private:

	unsigned int map_size_x;
	unsigned int map_size_y;
private:

	std::vector<std::vector<Room>> map_body;
	std::map<std::string, int> room_limiter{
		{"Treasure", 1}, // ok
		{"Curse", 1}, // ok
		{"Shop", 1}, // ok
		{"Boss", 1}, // ok
		{"Arena",1}, // ok
		{"Start", 1}, // ok
		{"Normal",0}, // ok
		{"Possible",0},
		{"ALL", 0}
	};
private:

	level type_of_level;
private:
	void room_counter();
	void room_limiter_set(level type_of_level);
	void set_possibility();
	bool analise(int x, int y);
	void fill_empty_space();



};

