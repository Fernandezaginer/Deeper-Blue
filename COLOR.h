#pragma once
class COLOR
{
public:
	COLOR(unsigned char r = 255, unsigned char v = 255, unsigned char a = 255) : rojo(r), verde(v), azul(a) {}
	~COLOR() {};

	unsigned char rojo;
	unsigned char verde;
	unsigned char azul;

	void setColor(unsigned char r, unsigned char v, unsigned char a);
};

