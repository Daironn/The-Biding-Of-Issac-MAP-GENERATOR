#include "pch.h"
#include "Vector2i.h"

std::ostream& operator<<(std::ostream& os, const Vector2i& obj)
{
	os << obj.X << obj.Y;
	return os;
}

const bool  operator<(const Vector2i & obj, const Vector2i & obj2)
{
	if (obj.X < obj2.X) {
		if (obj.Y < obj2.Y)
			return true;
	}
	else
		return false;
}

const bool  operator>(const Vector2i & obj, const Vector2i & obj2)
{
	if (obj.X > obj2.X) {
		if (obj.Y > obj2.Y)
			return true;
	}
	else
		return false;
}
