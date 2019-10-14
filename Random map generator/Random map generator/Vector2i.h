#pragma once
#include <iostream>
class Vector2i
{
public:

	Vector2i(int y, int x) :Y(y), X(x){};
	Vector2i() :Y(0),X(0){};
	~Vector2i() = default;
public:
	
	int X;
	int Y;
public:

	inline int x() { return X; };
	inline int y() { return Y; };
public:

	friend std::ostream & operator<< (std::ostream & os, const Vector2i & obj);

	friend const  bool  operator < (const Vector2i & obj, const Vector2i & obj2);
	friend const bool  operator > (const Vector2i & obj, const Vector2i & obj2);
};

