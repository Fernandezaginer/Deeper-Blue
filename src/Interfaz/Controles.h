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

	static bool fp_estado;
	static bool fn_estado;

	controles();
	void coger_pos();
	
};