#include "pch.h"
#include "Map.h"
#include <time.h>



Map::Map(level level_type):
	type_of_level(level_type),
	map_size_x(32),
	map_size_y(32)

{
	this->room_limiter_set(type_of_level);

	for (int i = 0; i < map_size_y; i++) {
		std::vector<Room> v;
		for (int j = 0; j < map_size_x; j++) {
			v.push_back(Room(ROOM::None, i, j));
		}
		map_body.push_back(v);
	}
	this->create_map_default();
	this->search_for_possibility(ROOM::Possible);
	this->fill_empty_poss();
	this->search_for_possibility(ROOM::Secret);
}

void Map::draw_map() const
{
	for (int i = 0; i < map_size_y; i++) {
		for (int j = 0; j < map_size_x; j++) {
			if (map_body[i][j].get_type() == ROOM::None)
				std::cout << " ";
			else
			std::cout << map_body[i][j].get_type();
		}
		std::cout << std::endl;
	}
}

void Map::create_map_default()
{
	unsigned start_positionX = map_size_y / 2;
	unsigned start_positionY = map_size_y / 2;

	map_body[start_positionY][start_positionX].set_type(ROOM::Start);
	
	int current_positionX = start_positionX;
	int current_positionY = start_positionY;


	bool previous_was_x = false;
	bool previous_was_y = false;

	bool previous_was_plus = false;
	bool previous_was_back = true;

	srand(time(NULL));

	while (room_limiter["Normal"] != 0) {

		
		unsigned direction = rand() % 15 + 1;

		if (direction == 14) {

			current_positionX = start_positionX;
			current_positionY = start_positionY;
			
		}
		else if (direction == 1 || direction == 2 || direction == 3) {
			

				current_positionX += 1;
				if (current_positionX > map_size_x) {
					
					std::cout << "We gotta go back in time" << std::endl;
					current_positionX -= 1;
				}
				else {
					if (map_body[current_positionY][current_positionX].get_type() == ROOM::None) {

						map_body[current_positionY][current_positionX].set_type(ROOM::Normal);


						room_limiter["Normal"] -= 1;
					}
				}
				previous_was_y = false;
				previous_was_x = true;

				previous_was_plus = true;
				previous_was_back = false;
		}
		else if (direction == 4 || direction == 5 || direction == 6) {
				
				current_positionX -= 1;
				if (current_positionX < 0) {
					
					std::cout << "We gotta go back in time" << std::endl;
					current_positionX += 1;
				}
				else {
					if (map_body[current_positionY][current_positionX].get_type() == ROOM::None) {

						map_body[current_positionY][current_positionX].set_type(ROOM::Normal);


						room_limiter["Normal"] -= 1;
					}
				}
				previous_was_y = false;
				previous_was_x = true;

				previous_was_plus = false;
				previous_was_back = false;
		}
		else if (direction == 7 || direction == 8 || direction == 9) {
			
				current_positionY += 1;
				if(current_positionY > map_size_y-1){
					std::cout << "We gotta go back in time" << std::endl;
					current_positionY -= 1;
				}
				else {
					if (map_body[current_positionY][current_positionX].get_type() == ROOM::None) {

						map_body[current_positionY][current_positionX].set_type(ROOM::Normal);


						room_limiter["Normal"] -= 1;
					}
				}
				previous_was_y = true;
				previous_was_x = false;

				previous_was_plus = true;
				previous_was_back = false;
		}
		else if (direction == 10 || direction == 11 || direction == 12) {
			
				current_positionY -= 1;
				if (current_positionY < 0) {
					std::cout << "We gotta go back in time" << std::endl;
					current_positionY += 1;
				}
				else {
					if (map_body[current_positionY][current_positionX].get_type() == ROOM::None) {

						map_body[current_positionY][current_positionX].set_type(ROOM::Normal);


						room_limiter["Normal"] -= 1;
					}
				}

				previous_was_y = true;
				previous_was_x = false;

				previous_was_plus = false;
				previous_was_back = false;
		}
		else if (direction == 13) {

			if (previous_was_back == false) {

				if (previous_was_plus == true) {

					if (previous_was_x == true) {

						current_positionX--;
					}
					else {
						current_positionY--;
					}
				}
				else {

					if (previous_was_x == true) {

						current_positionX++;
					}
					else {
						current_positionY++;
					}
				}
				previous_was_back = true;
			}
		}
	}
}

void Map::room_limiter_set(level type_of_level)
{
	if (type_of_level == Basement) {
		room_limiter["Normal"] = 8;
	}
	else if (type_of_level == Cave) {
		room_limiter["Normal"] = 12;
	}
	else if (type_of_level == Necro) {
		room_limiter["Normal"] =14;
	}
	else if (type_of_level == Womb) {
		room_limiter["Treasure"] = 0;
		room_limiter["Normal"] = 16;
	}
	else if (type_of_level == Catedral) {
		room_limiter["Treasure"] = 0;
		room_limiter["Normal"] = 20;
	}
	else if (type_of_level == Chest) {
		room_limiter["Treasure"] = 0;
		room_limiter["Normal"] = 26;
		room_limiter["Shop"] = 0;
		room_limiter["Curse"] = 0;
		room_limiter["Arena"] = 0;
	}
}

void Map::set_possibility()
{
	for (int y = 0; y < map_size_y; y++) {
		for (int x = 0; x < map_size_x; x++) {

			if (map_body[y][x].get_type() == ROOM::Normal) {


				if (analise_poss_v2(y, x + 1, ROOM::Possible) == ROOM::Possible) {

					map_body[y][x + 1].set_type(ROOM::Possible);
				}
				////////////////////////////////////////////RIGHT
				if (analise_poss_v2(y, x - 1, ROOM::Possible) == ROOM::Possible) {

					map_body[y][x - 1].set_type(ROOM::Possible);
				}
				///////////////////////////////////////////////LEFT
				 if (analise_poss_v2(y + 1, x, ROOM::Possible) == ROOM::Possible) {

					map_body[y + 1][x].set_type(ROOM::Possible);
				}
				///////////////////////////////////////////UP
				 if (analise_poss_v2(y - 1, x, ROOM::Possible) == ROOM::Possible) {

					map_body[y - 1][x].set_type(ROOM::Possible);
				}
				///////////////////////////////////////////////DOWN
			}
		}
	}
}

void Map::fill_empty_poss()
{
	srand(time(NULL));

	while (room_limiter["Possible"] != 0) {

		unsigned chosen_one = rand() % possible_position.size();
		
		ROOM::types type = this->give_me_a_reason();

		if (map_body[possible_position[chosen_one].y()]
			[possible_position[chosen_one].x()].get_type() == ROOM::Possible) {

			map_body[possible_position[chosen_one].y()]
				[possible_position[chosen_one].x()].set_type(type);

			room_limiter["Possible"]--;
		}
		else continue;

	}

}


ROOM::types Map::give_me_a_reason()
{
	int curse_chance = rand() % 5;
	int arena_chance = rand() % 5;

	if (room_limiter["Boss"] != 0) {
		room_limiter["Boss"]--;
		return ROOM::Boss;
	}

	else if (room_limiter["Treasure"] != 0) {
		room_limiter["Treasure"]--;
		return ROOM::Treasure;
	}

	else if (room_limiter["SSecret"] != 0) {
		room_limiter["SSecret"]--;
		return ROOM::SSecret;
	}

	else if (room_limiter["Curse"] !=0) {

		if (curse_chance == 2 || curse_chance || 4) {
			room_limiter["Curse"]--;
			return ROOM::Curse;
		}
		else
			room_limiter["Curse"]--;
	}

	else if (room_limiter["Arena"] != 0) {

		if (arena_chance == 1 || arena_chance || 3) {
			room_limiter["Arena"]--;
			return ROOM::Arena;
		}
		else
			room_limiter["Arena"]--;
	}

	else if (room_limiter["Secret"] != 0) {

	}

	else {
		return ROOM::None;
	}
}


ROOM::types Map::analise_poss_v2(int y, int x, ROOM::types type_of_room)
{
	{
		unsigned NoneCounter = 0;

		if (map_body[y][x].get_type() == ROOM::None) {



			if (map_body[y][x + 1].get_type() == ROOM::None)
				NoneCounter++;
			if (map_body[y][x - 1].get_type() == ROOM::None)
				NoneCounter++;
			if (map_body[y + 1][x].get_type() == ROOM::None)
				NoneCounter++;
			if (map_body[y - 1][x].get_type() == ROOM::None) // dodaæ sprawdzanie boss roomow
				NoneCounter++;

			if (type_of_room == ROOM::Possible) {
				if (NoneCounter == 3) {

					room_limiter["Possible"]++;
					possible_position.push_back(Vector2i(y, x));
					return type_of_room;
				}
			}
			if (type_of_room == ROOM::Secret) {
				if (NoneCounter < 3) {

					room_limiter["Secret"]++;
					possible_position.push_back(Vector2i(y, x));
					return type_of_room;
				}
				
			}
			else return ROOM::None;
		}
	}
}

void Map::search_for_possibility(ROOM::types type_of_room)
{

	for (int y = 0; y < map_size_y; y++) {
		for (int x = 0; x < map_size_x; x++) {

			if (map_body[y][x].get_type() == ROOM::Normal) {


				if (analise_poss_v2(y, x + 1, type_of_room) == type_of_room) {

					map_body[y][x + 1].set_type(type_of_room);
				}
				////////////////////////////////////////////RIGHT
				if (analise_poss_v2(y, x - 1, type_of_room) == type_of_room) {

					map_body[y][x - 1].set_type(type_of_room);
				}
				///////////////////////////////////////////////LEFT
				if (analise_poss_v2(y + 1, x, type_of_room) == type_of_room) {

					map_body[y + 1][x].set_type(type_of_room);
				}
				///////////////////////////////////////////UP
				if (analise_poss_v2(y - 1, x, type_of_room) == type_of_room) {

					map_body[y - 1][x].set_type(type_of_room);
				}
				///////////////////////////////////////////////DOWN
			}
		}
	}
}
