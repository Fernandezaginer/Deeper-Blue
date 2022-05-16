#include "Pieza.h"
#include "ChessRules.h"
#include <sstream>
using namespace std;

bool pieza_t::aux_detectar_comer_y_propias_piezas(tablero_info_t& matriz, int i, int j, pieza_t casilla)
{
	if (casilla.getForma() != NO_PIEZA) {
		if (casilla.getColor() == this->getColor()) {
			matriz.TAB[i][j] = NO_PERMITIDO;
			return 1;
		}
		else {
			matriz.TAB[i][j] = COMER_PIEZA;
			return 1;
		}
	}
	return 0;
}

void pieza_t::aux_permite_mov_vert_hor(tablero_info_t& matriz, pieza_t** tab, int row, int col)
{
	for (int i = row - 1, j = col; i >= 0; i--) {
		if (aux_detectar_comer_y_propias_piezas(matriz, i, j, tab[i][j])) {
			break;
		}
		matriz.TAB[i][j] = PERMITIDO;
	}
	for (int i = row + 1, j = col; i < ROW_SIZE; i++) {
		if (aux_detectar_comer_y_propias_piezas(matriz, i, j, tab[i][j])) {
			break;
		}
		matriz.TAB[i][j] = PERMITIDO;
	}
	for (int i = row, j = col - 1; j >= 0; j--) {
		if (aux_detectar_comer_y_propias_piezas(matriz, i, j, tab[i][j])) {
			break;
		}
		matriz.TAB[i][j] = PERMITIDO;
	}
	for (int i = row, j = col + 1; j < COL_SIZE; j++) {
		if (aux_detectar_comer_y_propias_piezas(matriz, i, j, tab[i][j])) {
			break;
		}
		matriz.TAB[i][j] = PERMITIDO;
	}
}

void pieza_t::aux_permite_mov_diag(tablero_info_t& matriz, pieza_t** tab, int row, int col)
{
	for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--) {
		if (aux_detectar_comer_y_propias_piezas(matriz, i, j, tab[i][j])) {
			break;
		}
		matriz.TAB[i][j] = PERMITIDO;
	}
	for (int i = row - 1, j = col + 1; i >= 0 && j < COL_SIZE; i--, j++) {
		if (aux_detectar_comer_y_propias_piezas(matriz, i, j, tab[i][j])) {
			break;
		}
		matriz.TAB[i][j] = PERMITIDO;
	}
	for (int i = row + 1, j = col - 1; i < ROW_SIZE && j >= 0; i++, j--) {
		if (aux_detectar_comer_y_propias_piezas(matriz, i, j, tab[i][j])) {
			break;
		}
		matriz.TAB[i][j] = PERMITIDO;
	}
	for (int i = row + 1, j = col + 1; i < ROW_SIZE && j < COL_SIZE; i++, j++) {
		if (aux_detectar_comer_y_propias_piezas(matriz, i, j, tab[i][j])) {
			break;
		}
		matriz.TAB[i][j] = PERMITIDO;
	}
}

char pieza_t::pieza_to_char()
{
	char car;
	switch (forma)
	{
	case PEON:
		car = 'P';
		break;
	case CABALLO:
		car = 'C';
		break;
	case ALFIL:
		car = 'A';
		break;
	case TORRE:
		car = 'T';
		break;
	case DAMA:
		car = 'D';
		break;
	case REY:
		car = 'R';
		break;
	default:
		car = '-';
		break;
	}

	return car;
}

int pieza_t::valor()
{
	int valor_pieza;

	switch (forma)
	{
	case PEON:
		valor_pieza = 1;
		break;
	case CABALLO:
		valor_pieza = 3;
		break;
	case ALFIL:
		valor_pieza = 3;
		break;
	case TORRE:
		valor_pieza = 5;
		break;
	case DAMA:
		valor_pieza = 9;
		break;
	case REY:
		valor_pieza = 0;
		break;
	default:
		valor_pieza = 0;
		break;
	}
	return 0;
}

string mov_print(tablero_info_t t) {
	ostringstream o;
	for (int i = 0; i < ROW_SIZE; i++) {
		for (int j = 0; j < COL_SIZE; j++) {
			char car;

			switch (t.TAB[i][j])
			{
			case PROPIA_PIEZA:
				car = 'P';
				break;
			case PERMITIDO:
				car = 'O';
				break;
			case NO_PERMITIDO:
				car = '-';
				break;
			case COMER_PIEZA:
				car = 'X';
				break;
			case ENROQUE_C:
				car = 'e';
				break;
			case ENROQUE_L:
				car = 'E';
				break;
			case COMER_AL_PASO_L:
				car = 'x';
				break;
			case COMER_AL_PASO_R:
				car = 'x';
				break;
			default:
				car = '-';
				break;
			}

			o << " " << car << " ";

		}
		o << endl;
	}


	return o.str();
}

bool operator==(pieza_t lhs, pieza_t rhs)
{
	if (lhs.color == rhs.color && lhs.forma == rhs.forma) {
		return true;
	}
	return false;
}
