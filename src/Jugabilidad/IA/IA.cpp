#include "IA.h"

bool IA_facil::hacerMovimiento(Juego& partida) {
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

bool IA_dificil::hacerMovimiento(Juego& partida)
{
	Juego temp = Juego(partida);
	arbol tree = IA_dificil::getArbol(temp, this->color, 3);
	movimiento mov = IA_dificil::evaluarArbol(tree);
	if (mov.mov > 0) {
		return partida.haz_movimiento(mov.row_o, mov.col_o, mov.row_f, mov.col_f);
	}
	return false;
}

movimiento IA_dificil::evaluarArbol(arbol tree)
{
	movimiento mejor_mov;
	int best_score = -99999;
	for (int i = 0; i < tree.size(); i++) {
		fruto testing_fruit = tree[i];
		int current_score = IA_dificil::evaluarRama(testing_fruit);
		if (current_score > best_score) {
			mejor_mov = testing_fruit.mov;
			best_score = current_score;
		}
	}
	return mejor_mov;
}

int IA_dificil::evaluarRama(fruto fruta)
{
	if (fruta.hijos->size() == 0) {
		return 0;
	}

	float score = 0;

	for (int i = 0; i < fruta.hijos->size(); i++) {
		score += -1 * ((*fruta.hijos)[i].score + 0.5 * IA_dificil::evaluarRama((*fruta.hijos)[i])) / fruta.hijos->size();
	}

	return (int)score;
}

arbol IA_dificil::getArbol(Juego partida, color_pieza_t player, int depth)
{
	tablero_t tab = partida.get_tablero();
	arbol tree;

	for (int x = 0; x < COL_SIZE; x++) {
		for (int y = 0; y < ROW_SIZE; y++) {
			if (tab[y][x].getColor() == player) {
				lista_movimientos listaMov = partida.get_mov_permitidos_l(tab, y, x);
				for (int mov = 0; mov < listaMov.size(); mov++) {
					Juego partida_aux = Juego(partida);
					if (!partida_aux.haz_movimiento(y, x, listaMov[mov].row_f, listaMov[mov].col_f))
						continue;
					fruto fruta;
					fruta.mov = listaMov[mov];
					fruta.partida = partida_aux;
					fruta.score = IA_dificil::getScore(partida_aux, player);
					IA_dificil::crearRama(fruta, partida_aux, player == BLANCA ? NEGRA : BLANCA, depth - 1);
					tree.push_back(fruta);
				}
			}
		}
	}
	return tree;
}

void IA_dificil::crearRama(fruto& fruta, Juego partida, color_pieza_t player, int depth_left)
{
	if (depth_left == 0)
	{
		fruta.hijos = 0;
		return;
	}

	tablero_t tab = fruta.partida.get_tablero();
	for (int x = 0; x < COL_SIZE; x++) {
		for (int y = 0; y < ROW_SIZE; y++) {
			if (tab[y][x].getColor() == player) {
				lista_movimientos listaMov = fruta.partida.get_mov_permitidos_l(tab, y, x);
				for (int mov = 0; mov < listaMov.size(); mov++) {
					Juego partida_aux = Juego(partida);
					if (!partida_aux.haz_movimiento(y, x, listaMov[mov].row_f, listaMov[mov].col_f))
						continue;
					fruto fruta_n;
					fruta_n.mov = listaMov[mov];
					fruta_n.partida = partida_aux;
					fruta_n.score = IA_dificil::getScore(partida_aux, player);
					IA_dificil::crearRama(fruta, partida_aux, player == BLANCA ? NEGRA : BLANCA, depth_left - 1);

					(*fruta.hijos).push_back(fruta_n);
				}
			}
		}
	}
}

int IA_dificil::contarMovPosibles(Juego partida, color_pieza_t player) {
	tablero_t tab = partida.get_tablero();
	int num = 0;
	for (int x = 0; x < COL_SIZE; x++) {
		for (int y = 0; y < ROW_SIZE; y++) {
			if (tab[y][x].getColor() == player) {
				num += partida.get_mov_permitidos_l(tab, y, x).size();
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
