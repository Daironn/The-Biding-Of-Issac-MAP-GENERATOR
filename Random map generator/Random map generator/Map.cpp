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
	this->sum_everything_up();
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
		std::cout <<" "<<i<<std::endl;
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

		
		unsigned direction = rand() % 100 + 1;

		if (direction == 100) {

			current_positionX = start_positionX;
			current_positionY = start_positionY;
			
		}
		else if (direction >=1 && direction <=20) {
			

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
		else if (direction >= 21 && direction <= 50) {
				
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
		else if (direction >= 51 && direction <= 70) {
			
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
		else if (direction >= 71 && direction <= 89) {
			
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
		else if (direction >= 90 && direction <= 99) {

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
		room_limiter["Normal"] = 10;
	}
	else if (type_of_level == Cave) {
		room_limiter["Normal"] = 16;
	}
	else if (type_of_level == Necro) {
		room_limiter["Normal"] =20;
	}
	else if (type_of_level == Womb) {
		room_limiter["Treasure"] = 0;
		room_limiter["Normal"] = 24;
	}
	else if (type_of_level == Catedral) {
		room_limiter["Treasure"] = 0;
		room_limiter["Normal"] = 26;
	}
	else if (type_of_level == Chest) {
		room_limiter["Treasure"] = 0;
		room_limiter["Normal"] = 30;
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

		ROOM::types chosen_type = this->give_me_a_reason();

		if (map_body[possible_position[chosen_one].y()]
			[possible_position[chosen_one].x()].get_type() == ROOM::Possible) {

			map_body[possible_position[chosen_one].y()]
				[possible_position[chosen_one].x()].set_type(chosen_type);

			room_limiter["Possible"]--;
		}
		else continue;

	}

}

void Map::fill_empty_sec()
{
	srand(time(NULL));

	unsigned chosen_one = rand() % secret_position.size();


		for (int i = 0; i < secret_position.size(); i++) {

			if (i == chosen_one) {

				map_body[secret_position[i].y()]
					[secret_position[i].x()].set_type(ROOM::Secret);
			}
			else
				map_body[secret_position[i].y()]
				[secret_position[i].x()].set_type(ROOM::None);
		}
	
}


ROOM::types Map::give_me_a_reason()
{
	int curse_chance = rand() % 5;
	int arena_chance = rand() % 5;

	if (room_limiter["Treasure"] > 0) {
		room_limiter["Treasure"]--;
		return ROOM::Treasure;
	}

	else if (room_limiter["SSecret"] > 0) {
		room_limiter["SSecret"]--;
		return ROOM::SSecret;
	}

	else if (room_limiter["Curse"] > 0) {

		if (curse_chance == 2 || curse_chance || 4) {
			room_limiter["Curse"]--;
			return ROOM::Curse;
		}
		else
			room_limiter["Curse"]--;
	}

	else if (room_limiter["Arena"] > 0) {

		if (arena_chance == 1 || arena_chance || 3) {
			room_limiter["Arena"]--;
			return ROOM::Arena;
		}
		else
			room_limiter["Arena"]--;
	}

	else {
		return ROOM::None;
	}
}

void Map::sum_everything_up()
{
	this->create_map_default();
	this->search_for_possibility(ROOM::Possible);
	this->find_the_farthest_room();
	this->fill_empty_poss();
	this->search_for_possibility(ROOM::Secret);
	this->fill_empty_sec();
}

void Map::find_the_farthest_room()
{

	Vector2i room = this->the_farthest_room();
	map_body[room.y()][room.x()].set_type(ROOM::Boss);
	room_limiter["Boss"]--;
	room_limiter["Possible"]--;

}

Vector2i Map::the_farthest_room()
{
	int start_positionX = map_size_y / 2;
	int start_positionY = map_size_y / 2;

	float current_positionX = 0;
	float current_positionY = 0;

	float max = 0;
	float pit = 0;

	Vector2i startVec(start_positionY, start_positionX);
	Vector2i maxVec(0,0);
	for (auto i : possible_position) {

		current_positionX = abs(i.x() - start_positionX);
		current_positionY = abs(i.y() - start_positionY);

		float pit = sqrt(pow(current_positionX,2) + pow(current_positionY,2));

		if (pit > max) {
			max = pit;
			maxVec = i;
		

			std::cout << maxVec <<  std::endl;
		}
	}

	return maxVec;
}


ROOM::types Map::analise_poss_v2(int y, int x, ROOM::types type_of_room)
{
	{
		unsigned NoneCounter = 0;

		if (map_body[y][x].get_type() == ROOM::None) {



			if (type_of_room == ROOM::Possible) {

				if (map_body[y][x + 1].get_type() == ROOM::None)
					NoneCounter++;
				if (map_body[y][x - 1].get_type() == ROOM::None)
					NoneCounter++;
				if (map_body[y + 1][x].get_type() == ROOM::None)
					NoneCounter++;
				if (map_body[y - 1][x].get_type() == ROOM::None) 
					NoneCounter++;

				if (NoneCounter == 3) {

					room_limiter["Possible"]++;
					possible_position.push_back(Vector2i(y, x));
					return type_of_room;
				}
			}
			if (type_of_room == ROOM::Secret) {

				if (map_body[y][x + 1].get_type() == ROOM::None)
					NoneCounter++;

				else if (map_body[y][x + 1].get_type() == ROOM::Boss
						|| map_body[y][x + 1].get_type() == ROOM::Secret)

							NoneCounter += 100;

				if (map_body[y][x - 1].get_type() == ROOM::None)
					NoneCounter++;

				else if (map_body[y][x - 1].get_type() == ROOM::Boss
						|| map_body[y][x - 1].get_type() == ROOM::Secret)

							NoneCounter += 100;

				if (map_body[y + 1][x].get_type() == ROOM::None)
					NoneCounter++;

				else if (map_body[y + 1][x].get_type() == ROOM::Boss
						|| map_body[y + 1][x].get_type() == ROOM::Secret)

							NoneCounter += 100;

				if (map_body[y - 1][x].get_type() == ROOM::None)
					NoneCounter++;

				else if (map_body[y - 1][x].get_type() == ROOM::Boss
						|| map_body[y - 1][x].get_type() == ROOM::Secret)

							NoneCounter += 100;

				if (NoneCounter < 3) {

					secret_position.push_back(Vector2i(y, x));
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
