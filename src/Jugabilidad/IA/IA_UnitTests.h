#pragma once

#include "IA.h"

class IA_UnitTests {
private:
	static IA_dificil IA_d_b;
	static IA_dificil IA_d_n;

	static bool test_1();
	static bool test_2();
	static bool test_3();

	static tablero_t generarTablero();
public:
	static bool test();
};