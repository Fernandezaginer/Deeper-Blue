#include "VECTOR.h"

VECTOR VECTOR::operator+(VECTOR v)
{
	VECTOR RES;
	RES.x = x + v.x;
	RES.y = y + v.y;
	return RES;
}

VECTOR VECTOR::operator-(VECTOR v)
{
	VECTOR RES;
	RES.x = x - v.x;
	RES.y = y - v.y;
	return RES;
}

float VECTOR::operator*(VECTOR v)
{
	return x * v.x + y * v.y;
}

VECTOR VECTOR::operator*(float f)
{
	VECTOR RES;
	RES.x = f * x;
	RES.y = f * y;
	return RES;
}

VECTOR VECTOR::operator/(float f)
{
	return *this*(1/f);
}
