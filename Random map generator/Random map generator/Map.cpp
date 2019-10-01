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
					if (map_body[current_positionY][current_positionX].get_type() == None) {

						map_body[current_positionY][current_positionX].set_type(Normal);

						room_limiter["ALL"] -= 1;
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
					if (map_body[current_positionY][current_positionX].get_type() == None) {

						map_body[current_positionY][current_positionX].set_type(Normal);

						room_limiter["ALL"] -= 1;
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
					if (map_body[current_positionY][current_positionX].get_type() == None) {

						map_body[current_positionY][current_positionX].set_type(Normal);

						room_limiter["ALL"] -= 1;
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
					if (map_body[current_positionY][current_positionX].get_type() == None) {

						map_body[current_positionY][current_positionX].set_type(Normal);

						room_limiter["ALL"] -= 1;
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

			if (map_body[y][x].get_type() == Normal) {


				if (analise(y, x + 1) == Possible) {

					map_body[y][x + 1].set_type(Possible);
				}
				else if (analise(y, x + 1) == Secret) {

					map_body[y][x + 1].set_type(Secret);
				}
				////////////////////////////////////////////RIGHT
				 if (analise(y, x - 1) == Possible) {

					map_body[y][x - 1].set_type(Possible);
				}
				else if (analise(y, x - 1) == Secret) {

					map_body[y][x - 1].set_type(Secret);
				}
				///////////////////////////////////////////////LEFT
				 if (analise(y + 1, x) == Possible) {

					map_body[y + 1][x].set_type(Possible);
				}
				else if (analise(y + 1, x) == Secret) {

					map_body[y + 1][x].set_type(Secret);
				}
				///////////////////////////////////////////UP
				 if (analise(y - 1, x) == Possible) {

					map_body[y - 1][x].set_type(Possible);
				}
				else if (analise(y - 1, x) == Secret) {

					map_body[y - 1][x].set_type(Secret);
				}
				///////////////////////////////////////////////DOWN
			}

		}
	}
}

types Map::analise(int y, int x) 
{
	unsigned NoneCounter = 0;

	if (map_body[y][x].get_type() == None) {



		if (map_body[y][x + 1].get_type() == None)
			NoneCounter++;
		if (map_body[y][x - 1].get_type() == None)
			NoneCounter++;
		if (map_body[y + 1][x].get_type() == None)
			NoneCounter++;
		if (map_body[y - 1][x].get_type() == None) // dodaæ sprawdzanie boss roomow
			NoneCounter++;

		if (NoneCounter == 3) {
			room_limiter["Posible"]++;
			return Possible;
		}
		else
			return None;
	}
}

void Map::fill_empty_space()
{
	bool stopu = false;
	srand(time(NULL));

}
