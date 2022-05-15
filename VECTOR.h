#pragma once
class VECTOR
{
public:
	VECTOR(float i = 0, float j = 0) : x(i), y(i) {}
	~VECTOR() {}

	float x;
	float y;

	VECTOR operator+(VECTOR v);
	VECTOR operator-(VECTOR v);
	float operator*(VECTOR v);
	VECTOR operator*(float f);
	VECTOR operator/(float f);


};

