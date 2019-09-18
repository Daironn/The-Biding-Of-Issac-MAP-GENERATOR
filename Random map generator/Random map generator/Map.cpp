#include "pch.h"
#include "Map.h"
#include <time.h>



Map::Map(level level_type):
	type_of_level(level_type)
{
	if (type_of_level == Basement) {

		map_size_x = 10;
		map_size_y = 6;
		this->room_limiter_set(type_of_level);
	}
	else if (type_of_level == Cave) {

		map_size_x = 11;
		map_size_y = 7;
		this->room_limiter_set(type_of_level);
	}
	else if (type_of_level == Necro) {

		map_size_x = 12;
		map_size_y = 8;
		this->room_limiter_set(type_of_level);
	}
	else if (type_of_level == Womb) {

		map_size_x = 13;
		map_size_y = 9;
		this->room_limiter_set(type_of_level);
	}
	else if (type_of_level == Catedral) {

		map_size_x = 14;
		map_size_y = 10;
		this->room_limiter_set(type_of_level);
	}
	else if (type_of_level == Chest) {

		map_size_x = 15;
		map_size_y = 11;
		this->room_limiter_set(type_of_level);
	}

	for (int i = 0; i < map_size_y; i++) {
		std::vector<Room> v;
		for (int j = 0; j < map_size_x; j++) {
			v.push_back(Room(None, i, j));
		}
		map_body.push_back(v);
	}
	this->create_map_default();
}

void Map::draw_map() const
{
	for (int i = 0; i < map_size_y; i++) {
		for (int j = 0; j < map_size_x; j++) {
			std::cout << map_body[i][j].get_type();
		}
		std::cout << std::endl;
	}
}

void Map::create_map_default()
{
	unsigned start_positionX = map_size_y / 2;
	unsigned start_positionY = map_size_y / 2;
	map_body[start_positionY][start_positionX].set_type(Start);
	
	int current_positionX = start_positionX;
	int current_positionY = start_positionY;
	
	srand(time(NULL));

	while (room_limiter["Normal"] != 0) {

		
		unsigned direction = rand() % 14 + 1;



		if (direction == 13) {

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
					if (map_body[current_positionY][current_positionX].get_type() == None) {

						map_body[current_positionY][current_positionX].set_type(Normal);

						room_limiter["ALL"] -= 1;
						room_limiter["Normal"] -= 1;
					}
				}
			
		}
		else if (direction == 4 || direction == 5 || direction == 6) {
				
				current_positionX -= 1;
				if (current_positionX < 0) {
					
					std::cout << "We gotta go back in time" << std::endl;
					current_positionX += 1;
				}
				else {
					if (map_body[current_positionY][current_positionX].get_type() == None) {

						map_body[current_positionY][current_positionX].set_type(Normal);

						room_limiter["ALL"] -= 1;
						room_limiter["Normal"] -= 1;
					}
				}
		}
		else if (direction == 7 || direction == 8 || direction == 9) {
			
				current_positionY += 1;
				if(current_positionY > map_size_y-1){
					std::cout << "We gotta go back in time" << std::endl;
					current_positionY -= 1;
				}
				else {
					if (map_body[current_positionY][current_positionX].get_type() == None) {

						map_body[current_positionY][current_positionX].set_type(Normal);

						room_limiter["ALL"] -= 1;
						room_limiter["Normal"] -= 1;
					}
				}
		}
		else if (direction == 10 || direction == 11 || direction == 12) {
			
				current_positionY -= 1;
				if (current_positionY < 0) {
					std::cout << "We gotta go back in time" << std::endl;
					current_positionY += 1;
				}
				else {
					if (map_body[current_positionY][current_positionX].get_type() == None) {

						map_body[current_positionY][current_positionX].set_type(Normal);

						room_limiter["ALL"] -= 1;
						room_limiter["Normal"] -= 1;
					}
				}
			

		}
	}
	
}

void Map::room_counter()
{
	room_limiter["ALL"] += room_limiter["Treasure"];

	room_limiter["ALL"] += room_limiter["Curse"];

	room_limiter["ALL"] += room_limiter["Boss"];

	room_limiter["ALL"] += room_limiter["Arena"];

	room_limiter["ALL"] += room_limiter["Start"];

	room_limiter["ALL"] += room_limiter["Normal"];
}

void Map::room_limiter_set(level type_of_level)
{
	if (type_of_level == Basement) {
		room_limiter["Normal"] = 8;
		this->room_counter();
	}
	else if (type_of_level == Cave) {
		room_limiter["Normal"] = 12;
		this->room_counter();
	}
	else if (type_of_level == Necro) {
		room_limiter["Normal"] =14;
		this->room_counter();
	}
	else if (type_of_level == Womb) {
		room_limiter["Treasure"] = 0;
		room_limiter["Normal"] = 16;
		this->room_counter();
	}
	else if (type_of_level == Catedral) {
		room_limiter["Treasure"] = 0;
		room_limiter["Normal"] = 20;
		this->room_counter();
	}
	else if (type_of_level == Chest) {
		room_limiter["Treasure"] = 0;
		room_limiter["Normal"] = 26;
		this->room_counter();

	}
}

bool Map::check_possibility(int x, int y)
{
	
	if (map_body[x][y].get_type() == Normal) {

		if (x == map_size_x) {

		}
		else if (x == 0) {

		}
		else if (y == map_size_y) {

			if (map_body[x + 1][y].get_type() == None) {

				if (analise(x + 1, y) == true) {

					map_body[x + 1][y].set_type(Possible);

				}
			}
			else if (map_body[x - 1][y].get_type() == None) {

				if (analise(x - 1, y) == true) {

					map_body[x - 1][y].set_type(Possible);

				}
			}
			else if (map_body[x][y + 1].get_type() == None) {

				if (analise(x, y + 1) == true) {

					map_body[x + 1][y - 1].set_type(Possible);

				}
			}
		}
		else if (y == 0) {

			if (map_body[x+1][y].get_type() == None) {

				if (analise(x + 1, y) == true) {

					map_body[x + 1][y].set_type(Possible);

				}
			}
			else if (map_body[x - 1][y].get_type() == None) {

				if (analise(x - 1, y) == true) {

					map_body[x - 1][y].set_type(Possible);

				}
			}
			else if (map_body[x][y + 1].get_type() == None) {

				if (analise(x, y + 1) == true) {

					map_body[x + 1][y + 1].set_type(Possible);

				}
			}

		}
		else {
			std::cout << "TODO";
		}

	}
}




