#pragma once

#include "freeglut.h"
#include <vector>
#include <string>
#include "Vector3D.h"

class Figura {
private:
	std::vector<Vector3D> vertices;
	std::vector<Vector2D> UVs;
	const char* texturePath;
public:
	Figura();
	Figura(const char* path, const char* textura);
	void dibuja();
};

