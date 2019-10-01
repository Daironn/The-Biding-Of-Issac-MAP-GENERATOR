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
		{"Treasure", 1},
		{"Curse", 1},
		{"Shop", 1},
		{"Boss", 1},
		{"Arena",1},
		{"Start", 1},
		{"Secret", 1},
		{"Normal",0},
		{"Possible",0},
	};
private:

	level type_of_level;

private:

	void room_limiter_set(level type_of_level);
	void set_possibility();
	void fill_empty_poss();

	types analise_poss(int x, int y);



};

