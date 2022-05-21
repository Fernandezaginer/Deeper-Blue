#pragma once
class inicio {
public:
	inicio();

	float coor_y;
	float coor_yr;
	std::string direct;
	void draw();
	void carga();
	void output(int x, int y, float r, float g, float b, void* font, const char* string);
	
};
