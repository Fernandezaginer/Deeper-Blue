#include "IA.h"

bool IA_facil::hacerMovimiento() {
	srand(time(NULL));
	bool searching = true;
	time_t t_0 = time(NULL);
	while (time(NULL) < t_0 + 5) {
		for (int i = 0; i < ROW_SIZE; i++) {
			for (int j = 0; j < COL_SIZE; j++) {
				if (this->partida.get_tablero()[i][j].getColor() == this->color) {
					if (rand() % 10 == 5) {
						bool moving = true;
						while (moving) {
							moving = false;
							for (int m = 0; m < ROW_SIZE; m++) {
								for (int n = 0; n < COL_SIZE; n++) {
									if (this->partida.get_mov_permitidos(&this->partida.get_tablero()[i][j], this->partida.get_tablero()).TAB[m][n] > 0) {
										moving = true;
										if (rand() % 5 == 3) {
											if (this->partida.haz_movimiento(i, j, m, n)) {
												return true;
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
	return false;
}

bool IA_dificil::hacerMovimiento()
{
	return false;
}


const int IA_dificil::pawntable[ROW_SIZE][COL_SIZE] = {
	{ 0,   0,   0,   0,   0,   0,   0,   0},
	{ 5,  10,  10, -20, -20,  10,  10,   5},
	{ 5,  -5, -10,   0,   0, -10,  -5,   5},
	{ 0,   0,   0,  20,  20,   0,   0,   0},
	{ 5,   5,  10,  25,  25,  10,   5,   5},
	{10,  10,  20,  30,  30,  20,  10,  10},
	{50,  50,  50,  50,  50,  50,  50,  50},
	{ 0,   0,   0,   0,   0,   0,   0,   0}
};
const int IA_dificil::knightstable[ROW_SIZE][COL_SIZE] = {
	{-50, -40, -30, -30, -30, -30, -40, -50},
	{-40, -20,   0,   5,   5,   0, -20, -40},
	{-30,   5,  10,  15,  15,  10,   5, -30},
	{-30,   0,  15,  20,  20,  15,   0, -30},
	{-30,   5,  15,  20,  20,  15,   5, -30},
	{-30,   0,  10,  15,  15,  10,   0, -30},
	{-40, -20,   0,   0,   0,   0, -20, -40},
	{-50, -40, -30, -30, -30, -30, -40, -50}
};
const int IA_dificil::bishopstable[ROW_SIZE][COL_SIZE] = {
	{-20, -10, -10, -10, -10, -10, -10, -20},
	{-10,   5,   0,   0,   0,   0,   5, -10},
	{-10,  10,  10,  10,  10,  10,  10, -10},
	{-10,   0,  10,  10,  10,  10,   0, -10},
	{-10,   5,   5,  10,  10,   5,   5, -10},
	{-10,   0,   5,  10,  10,   5,   0, -10},
	{-10,   0,   0,   0,   0,   0,   0, -10},
	{-20, -10, -10, -10, -10, -10, -10, -20}
};
const int IA_dificil::rookstable[ROW_SIZE][COL_SIZE] = {
	{  0,   0,   0,   5,   5,   0,   0,   0},
	{ -5,   0,   0,   0,   0,   0,   0,  -5},
	{ -5,   0,   0,   0,   0,   0,   0,  -5},
	{ -5,   0,   0,   0,   0,   0,   0,  -5},
	{ -5,   0,   0,   0,   0,   0,   0,  -5},
	{ -5,   0,   0,   0,   0,   0,   0,  -5},
	{  5,  10,  10,  10,  10,  10,  10,   5},
	{  0,   0,   0,   0,   0,   0,   0,   0}
};
const int IA_dificil::queenstable[ROW_SIZE][COL_SIZE] = {
	{-20, -10, -10,  -5,  -5, -10, -10, -20},
	{-10,   0,   0,   0,   0,   0,   0, -10},
	{-10,   5,   5,   5,   5,   5,   0, -10},
	{  0,   0,   5,   5,   5,   5,   0,  -5},
	{ -5,   0,   5,   5,   5,   5,   0,  -5},
	{-10,   0,   5,   5,   5,   5,   0, -10},
	{-10,   0,   0,   0,   0,   0,   0, -10},
	{-20, -10, -10,  -5,  -5, -10, -10, -20}
};
const int IA_dificil::kingstable[ROW_SIZE][COL_SIZE] = {
	{ 20,  30,  10,   0,   0,  10,  30,  20},
	{ 20,  20,   0,   0,   0,   0,  20,  20},
	{-10, -20, -20, -20, -20, -20, -20, -10},
	{-20, -30, -30, -40, -40, -30, -30, -20},
	{-30, -40, -40, -50, -50, -40, -40, -30},
	{-30, -40, -40, -50, -50, -40, -40, -30},
	{-30, -40, -40, -50, -50, -40, -40, -30},
	{-30, -40, -40, -50, -50, -40, -40, -30}
};
