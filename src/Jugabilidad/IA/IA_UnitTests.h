#pragma once

#include "IA.h"


class IA_UnitTests {
private:
	static bool test_1();
	static bool test_2();
	static bool test_3();

	static tablero_t generarTablero();
public:
	static bool test();
};