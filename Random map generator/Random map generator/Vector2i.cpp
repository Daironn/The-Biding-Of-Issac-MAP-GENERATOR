#include "pch.h"
#include "Vector2i.h"

std::ostream& operator<<(std::ostream& os, const Vector2i& obj)
{
	os << obj.X << obj.Y;
	return os;
}