#include "pch.h"
#include "Map.h"
#include <time.h>



Map::Map(level level_type):
	type_of_level(level_type)
{
	if (type_of_level == Basement) {

		map_size_x = 15;
		map_size_y = 15;
		this->room_limiter_set(type_of_level);
	}
	else if (type_of_level == Cave) {

		map_size_x = 15;
		map_size_y = 15;
		this->room_limiter_set(type_of_level);
	}
	else if (type_of_level == Necro) {

		map_size_x = 15;
		map_size_y = 15;
		this->room_limiter_set(type_of_level);
	}
	else if (type_of_level == Womb) {

		map_size_x = 15;
		map_size_y = 15;
		this->room_limiter_set(type_of_level);
	}
	else if (type_of_level == Catedral) {

		map_size_x = 15;
		map_size_y = 15;
		this->room_limiter_set(type_of_level);
	}
	else if (type_of_level == Chest) {

		map_size_x = 15;
		map_size_y = 15;
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
	this->set_possibility();
	this->fill_empty_space();
}

void Map::draw_map() const
{
	for (int i = 0; i < map_size_y; i++) {
		for (int j = 0; j < map_size_x; j++) {
			if (map_body[i][j].get_type() == None)
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

void Map::set_possibility()
{
	for (int y = 0; y < 15; y++) {
		for (int x = 0; x < 15; x++) {

			if (map_body[y][x].get_type() == Normal) {

				if (x == map_size_x) {

					if (map_body[y - 1][x].get_type() == None) {

						if (analise(y - 1, x) == true) {

							map_body[y - 1][x].set_type(Possible);

						}
					}
					else if (map_body[y + 1][x].get_type() == None) {

						if (analise(y + 1, x) == true) {

							map_body[y + 1][x].set_type(Possible);

						}
					}
					else if (map_body[y][x - 1].get_type() == None) {

						if (analise(y, x - 1) == true) {

							map_body[y][x - 1].set_type(Possible);

						}
					}
				}



				else if (x == 0) {

					if (map_body[y - 1][x].get_type() == None) {

						if (analise(y - 1, x) == true) {

							map_body[y - 1][x].set_type(Possible);

						}
					}

					else if (map_body[y + 1][x].get_type() == None) {

						if (analise(y + 1, x) == true) {

							map_body[y + 1][x].set_type(Possible);

						}
					}
					else if (map_body[y][x + 1].get_type() == None) {

						if (analise(y, x + 1) == true) {

							map_body[y][x + 1].set_type(Possible);

						}
					}
				}



				else if (y == map_size_y) {

					if (map_body[y][x + 1].get_type() == None) {

						if (analise(y, x + 1) == true) {

							map_body[y][x + 1].set_type(Possible);

						}
					}
					else if (map_body[y][x - 1].get_type() == None) {

						if (analise(y, x - 1) == true) {

							map_body[y][x - 1].set_type(Possible);

						}
					}
					else if (map_body[y - 1][x].get_type() == None) {

						if (analise(y - 1,x) == true) {

							map_body[y - 1][x].set_type(Possible);

						}
					}
				}


				else if (y == 0) {

					if (map_body[y][x + 1].get_type() == None) {

						if (analise(y, x + 1) == true) {

							map_body[y][x + 1].set_type(Possible);

						}
					}
					else if (map_body[y][x - 1].get_type() == None) {

						if (analise(y, x - 1) == true) {

							map_body[y][x - 1].set_type(Possible);

						}
					}
					else if (map_body[y + 1][x].get_type() == None) {

						if (analise(y + 1, x) == true) {

							map_body[y + 1][x].set_type(Possible);

						}
					}

				}
				else {

					if (map_body[y][x + 1].get_type() == None) {

						if (analise(y, x + 1) == true) {

							map_body[y][x + 1].set_type(Possible);

						}
					}
					else if (map_body[y][x - 1].get_type() == None) {

						if (analise(y, x - 1) == true) {

							map_body[y][x - 1].set_type(Possible);

						}
					}
					else if (map_body[y + 1][x].get_type() == None) {

						if (analise(y + 1, x) == true) {

							map_body[y + 1][x].set_type(Possible);
							room_limiter["Possible"]++;

						}
					}
					else if (map_body[y - 1][x].get_type() == None) {

						if (analise(y - 1, x) == true) {

							map_body[y - 1][x].set_type(Possible);

						}
					}
				}
			}
		}
	}
}

bool Map::analise(int y, int x) 
{
	int noneCounter = 0;
	if (x == map_size_x) {
		return false;
	}
	else if (x == 0) {
		return false;
	}
	else if (y == map_size_y) {
		return false;
	}
	else if (y == 0) {
		return false;
	}
	else {
		if (map_body[y + 1][x].get_type() == None) {
			noneCounter++;
		}
		if (map_body[y - 1][x].get_type() == None) {
			noneCounter++;
		}
		if (map_body[y][x + 1].get_type() == None) {
			noneCounter++;
		}
		if (map_body[y][x - 1].get_type() == None) {
			noneCounter++;
		}

		if (noneCounter == 3) {
			return true;
		}
	}
	return false;
}

void Map::fill_empty_space()
{
	srand(time(NULL));
	int curse_chance = rand() % 2;

	srand(time(NULL));
	int shop_above_necro = rand() % 2;

	if (this->type_of_level < 4) {
		for (int y = 0; y < 15; y++) {
			for (int x = 0; x < 15; x++) {

				if (map_body[y][x].get_type() == Possible
					&& room_limiter["Boss"] == 1) {

					room_limiter["Boss"]--;
					map_body[y][x].set_type(Boss);
				}
				else if (map_body[y][x].get_type() == Possible
					&& room_limiter["Treasure"] == 1) {

					room_limiter["Treasure"]--;
					map_body[y][x].set_type(Treasure);
				}

				else if (map_body[y][x].get_type() == Possible
					&& room_limiter["Curse"] == 1
					&& curse_chance == 0) {

					room_limiter["Curse"]--;
					map_body[y][x].set_type(Curse);
				}

				else if (map_body[y][x].get_type() == Possible
					&& room_limiter["Shop"] == 1) {

					room_limiter["Shop"]--;
					map_body[y][x].set_type(Shop);
				}
				else if (map_body[y][x].get_type() == Possible
					&& room_limiter["Arena"] == 1) {

					room_limiter["Arena"]--;
					map_body[y][x].set_type(Arena);
				}
			}
		}
	}
}
