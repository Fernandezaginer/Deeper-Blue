#pragma once
#include "freeglut.h"


class controles {
public:
	POINT mousePos;
	float anchop;
	float altop;
	float ay;
	float az;
	static int boton;
	static int estado;

	controles();
	void coger_pos();
	
};