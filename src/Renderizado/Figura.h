#pragma once

#include "freeglut.h"
#include <vector>
#include <string>
#include "Vector3D.h"
#include "ETSIDI.h"

class Figura {
private:
	std::vector<Vector3D> vertices;
	std::vector<Vector2D> UVs;

	const char* texturePath;

	GLuint textureID;

	Vector3D _pos;
	float scale;
public:
	Figura();
	Figura(const char* path, const char* textura, float escala = 1, float nx = 0, float ny = 0, float nz = 0);
	Figura(const char* path, const char* textura, float escala = 1, Vector3D pos = Vector3D());
	void dibuja();

	inline void setPos(Vector3D pos) { this->_pos = pos; }
	inline void setPos(float nx, float ny, float nz) { this->_pos = Vector3D(nx, ny, nz); }
	inline void setEscala(float escala) { this->scale = escala; }

	inline Vector3D getPos() { return this->_pos; }
	inline float getPosX() { return this->_pos.x; }
	inline float getPosY() { return this->_pos.y; }
	inline float getPosZ() { return this->_pos.z; }
	inline float getEscala() { return this->scale; }

	GLuint asdf(GLuint ID);
};

