#pragma once

class Vector3D {
public:
	float x;
	float y;
	float z;

	Vector3D():x(0),y(0),z(0){}
	Vector3D(float x, float y, float z): x(x), y(y), z(z){}
};

class Vector2D {
public:
	float x;
	float y;

	Vector2D() :x(0), y(0) {}
	Vector2D(float x, float y, float z) : x(x), y(y) {}
};