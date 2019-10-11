#pragma once
#include <iostream>
#include <string>

namespace ROOM {

	enum types {
		Start,
		Normal,
		Boss,
		Treasure,
		Shop,
		Curse,
		Arena,
		Secret,
		SSecret,
		Possible,
		None
	};
}

	class Room
	{
	public:

		Room(ROOM::types type, int loc_x, int loc_y);
		~Room() = default;

	public:

		friend std::ostream & operator<<(std::ostream & os, const Room & obj);

	public:

		ROOM::types get_type() const;
		void set_type(ROOM::types type);

	private:

		ROOM::types type;
		unsigned location_x;
		unsigned location_y;

	};

