#pragma once
#include "Room.h"
#include "Vector2i.h"
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

		level type_of_level;

private:

	std::vector<std::vector<Room>> map_body;
	std::vector<Vector2i> possible_position;
	std::vector<Vector2i> secret_position;

	std::map<std::string, int> room_limiter{
		{"Treasure", 1},
		{"Curse", 1},
		{"Shop", 1},
		{"Boss", 1},
		{"Arena",1},
		{"Start", 1},
		{"Secret", 1},
		{"SSecret", 1},
		{"Normal",0},
		{"Possible",0}
	};


private:

	void room_limiter_set(level type_of_level);
	void set_possibility();
	void fill_empty_poss();
	void fill_empty_sec();
	void find_the_farthest_room();

	Vector2i the_farthest_room();
	
	void search_for_possibility(ROOM::types type_of_room );

	ROOM::types analise_poss_v2(int y, int x, ROOM::types type_of_room);

	ROOM::types give_me_a_reason();

	void sum_everything_up();





};

