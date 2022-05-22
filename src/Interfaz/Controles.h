#pragma once
#include "freeglut.h"


class controles {
public:
	POINT mousePos;
	float ay;
	float az;
	static int boton;
	static int estado;

	static bool fp_estado;
	static bool fn_estado;
	static unsigned char key;

	controles();
	void coger_pos();
	static bool read_fp();
	static bool read_fn();
	static unsigned char read_key();
};