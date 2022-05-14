#include "IA.h"

bool IA_facil::hacerMovimiento(Juego partida) {
	srand(time(NULL));
	bool searching = true;
	time_t t_0 = time(NULL);
	while (time(NULL) < t_0 + 5) {
		for (int i = 0; i < ROW_SIZE; i++) {
			for (int j = 0; j < COL_SIZE; j++) {
				if (partida.get_tablero()[i][j].getColor() == this->color) {
					if (rand() % 10 == 5) {
						bool moving = true;
						while (moving) {
							moving = false;
							for (int m = 0; m < ROW_SIZE; m++) {
								for (int n = 0; n < COL_SIZE; n++) {
									if (partida.get_mov_permitidos(&partida.get_tablero()[i][j], partida.get_tablero()).TAB[m][n] > 0) {
										moving = true;
										if (rand() % 5 == 3) {
											if (partida.haz_movimiento(i, j, m, n)) {
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

bool IA_dificil::hacerMovimiento(Juego partida)
{
	tablero_t tablero = partida.get_tablero();
	int score = 0;
	return false;
}

arbol IA_dificil::getArbol(Juego partida, color_pieza_t player, int depth)
{
	tablero_t tab = partida.get_tablero();
	arbol tree;

	rama rama_aux;
	for (int x = 0; x < COL_SIZE; x++) {
		for (int y = 0; y < ROW_SIZE; y++) {
			if (tab[y][x].getColor() == player) {
				lista_movimientos listaMov = partida.get_mov_permitidos_l(&tab[y][x], tab);
				for (int mov = 0; mov < listaMov.size(); mov++) {
					Juego partida_aux = Juego(partida).haz_movimiento(y, x, listaMov[mov].y, listaMov[mov].x);
					fruto fruta;
					fruta.mov = listaMov[mov];
					fruta.partida = partida_aux;
					fruta.score = IA_dificil::getScore(partida_aux, player);
					rama_aux.push_back(fruta);
				}
			}
		}
	}
	tree.push_back(rama_aux);

	for (int i = 0; i < depth; i++) {
		rama_aux = rama();
		for (int x = 0; x < COL_SIZE; x++) {
			for (int y = 0; y < ROW_SIZE; y++) {
				if (tab[y][x].getColor() == player) {
				}
			}
		}
		tree.push_back(rama_aux);
	}
	return tree;
}

int IA_dificil::contarMovPosibles(Juego partida, color_pieza_t player) {
	tablero_t tab = partida.get_tablero();
	int num = 0;
	for (int x = 0; x < COL_SIZE; x++) {
		for (int y = 0; y < ROW_SIZE; y++) {
			if (tab[y][x].getColor() == player) {
				num += partida.get_mov_permitidos_l(&tab[y][x], tab).size();
			}
		}
	}
	return num;
}

int IA_dificil::getScore(Juego partida, color_pieza_t player)
{
	tablero_t tablero = partida.get_tablero();
	int score = IA_dificil::getBoardScore(tablero, player);
	if (partida.jaque_player(BLANCA, tablero)) {
		if (player == BLANCA)
			score += 9999;
		else
			score -= 9999;
	}
	if (partida.jaque_player(NEGRA, tablero)) {
		if (player == NEGRA)
			score += 9999;
		else
			score -= 9999;
	}
	return 0;
}

int IA_dificil::getBoardScore(tablero_t tablero, color_pieza_t player) {
	int score = 0;
	for (int x = 0; x < ROW_SIZE; x++) {
		for (int y = 0; y < COL_SIZE; y++) {
			forma_pieza_t forma = tablero[y][x].getForma();
			score += (IA_dificil::valorPiezas[forma]) * (tablero[y][x].getColor() == player ? 1 : -1); //Cálculo de puntaje material
			score += (IA_dificil::individualsTable[forma][(tablero[y][x].getColor() == BLANCA ? 7 - y : y)][x]) * (tablero[y][x].getColor() == player ? 1 : -1); //Cálculo de puntaje de piezas individuales
		}
	}
	return score;
}

//enum forma_pieza_t { NO_PIEZA, PEON, CABALLO, ALFIL, TORRE, DAMA, REY };
const int IA_dificil::individualsTable[7][ROW_SIZE][COL_SIZE] = {
	{
		{ 0,   0,   0,   0,   0,   0,   0,   0},
		{ 0,   0,   0,   0,   0,   0,   0,   0},
		{ 0,   0,   0,   0,   0,   0,   0,   0},
		{ 0,   0,   0,   0,   0,   0,   0,   0},
		{ 0,   0,   0,   0,   0,   0,   0,   0},
		{ 0,   0,   0,   0,   0,   0,   0,   0},
		{ 0,   0,   0,   0,   0,   0,   0,   0},
		{ 0,   0,   0,   0,   0,   0,   0,   0},
	},
	{
		{ 0,   0,   0,   0,   0,   0,   0,   0},
		{ 5,  10,  10, -20, -20,  10,  10,   5},
		{ 5,  -5, -10,   0,   0, -10,  -5,   5},
		{ 0,   0,   0,  20,  20,   0,   0,   0},
		{ 5,   5,  10,  25,  25,  10,   5,   5},
		{10,  10,  20,  30,  30,  20,  10,  10},
		{50,  50,  50,  50,  50,  50,  50,  50},
		{ 0,   0,   0,   0,   0,   0,   0,   0}
	},
	{
		{-50, -40, -30, -30, -30, -30, -40, -50},
		{-40, -20,   0,   5,   5,   0, -20, -40},
		{-30,   5,  10,  15,  15,  10,   5, -30},
		{-30,   0,  15,  20,  20,  15,   0, -30},
		{-30,   5,  15,  20,  20,  15,   5, -30},
		{-30,   0,  10,  15,  15,  10,   0, -30},
		{-40, -20,   0,   0,   0,   0, -20, -40},
		{-50, -40, -30, -30, -30, -30, -40, -50}
	},
	{
		{-20, -10, -10, -10, -10, -10, -10, -20},
		{-10,   5,   0,   0,   0,   0,   5, -10},
		{-10,  10,  10,  10,  10,  10,  10, -10},
		{-10,   0,  10,  10,  10,  10,   0, -10},
		{-10,   5,   5,  10,  10,   5,   5, -10},
		{-10,   0,   5,  10,  10,   5,   0, -10},
		{-10,   0,   0,   0,   0,   0,   0, -10},
		{-20, -10, -10, -10, -10, -10, -10, -20}
	},
	{
		{  0,   0,   0,   5,   5,   0,   0,   0},
		{ -5,   0,   0,   0,   0,   0,   0,  -5},
		{ -5,   0,   0,   0,   0,   0,   0,  -5},
		{ -5,   0,   0,   0,   0,   0,   0,  -5},
		{ -5,   0,   0,   0,   0,   0,   0,  -5},
		{ -5,   0,   0,   0,   0,   0,   0,  -5},
		{  5,  10,  10,  10,  10,  10,  10,   5},
		{  0,   0,   0,   0,   0,   0,   0,   0}
	},
	{
		{-20, -10, -10,  -5,  -5, -10, -10, -20},
		{-10,   0,   0,   0,   0,   0,   0, -10},
		{-10,   0,   5,   5,   5,   5,   0, -10},
		{  0,   0,   5,   5,   5,   5,   0,  -5},
		{ -5,   0,   5,   5,   5,   5,   0,  -5},
		{-10,   0,   5,   5,   5,   5,   0, -10},
		{-10,   0,   0,   0,   0,   0,   0, -10},
		{-20, -10, -10,  -5,  -5, -10, -10, -20}
	},
	{
		{ 20,  30,  10,   0,   0,  10,  30,  20},
		{ 20,  20,   0,   0,   0,   0,  20,  20},
		{-10, -20, -20, -20, -20, -20, -20, -10},
		{-20, -30, -30, -40, -40, -30, -30, -20},
		{-30, -40, -40, -50, -50, -40, -40, -30},
		{-30, -40, -40, -50, -50, -40, -40, -30},
		{-30, -40, -40, -50, -50, -40, -40, -30},
		{-30, -40, -40, -50, -50, -40, -40, -30}
	}
};

const int IA_dificil::valorPiezas[7] = { 0, 100, 320, 330, 500, 900, 9999 };

bool IA_base::hacerMovimiento(Juego partida)
{
	return false;
}
