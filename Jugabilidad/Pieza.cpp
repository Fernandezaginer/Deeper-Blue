
#include "Pieza.h"
#include <sstream>
using namespace std;

bool pieza_t::aux_detectar_comer_y_propias_piezas(tablero_info_t& matriz, int i, int j, pieza_t casilla, pieza_t* me)
{
	if (casilla.getForma() != NO_PIEZA) {
		if (casilla.getColor() == me->getColor()) {
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

void pieza_t::aux_permite_mov_vert_hor(tablero_info_t& matriz, pieza_t** tab, int row, int col, pieza_t* me)
{
	for (int i = row - 1, j = col; i >= 0; i--) {
		if (aux_detectar_comer_y_propias_piezas(matriz, i, j, tab[i][j], this)) {
			break;
		}
		matriz.TAB[i][j] = PERMITIDO;
	}
	for (int i = row + 1, j = col; i < ROW_SIZE; i++) {
		if (aux_detectar_comer_y_propias_piezas(matriz, i, j, tab[i][j], this)) {
			break;
		}
		matriz.TAB[i][j] = PERMITIDO;
	}
	for (int i = row, j = col - 1; j >= 0; j--) {
		if (aux_detectar_comer_y_propias_piezas(matriz, i, j, tab[i][j], this)) {
			break;
		}
		matriz.TAB[i][j] = PERMITIDO;
	}
	for (int i = row, j = col + 1; j < COL_SIZE; j++) {
		if (aux_detectar_comer_y_propias_piezas(matriz, i, j, tab[i][j], this)) {
			break;
		}
		matriz.TAB[i][j] = PERMITIDO;
	}
}


void pieza_t::aux_permite_mov_diag(tablero_info_t& matriz, pieza_t** tab, int row, int col, pieza_t* me)
{
	for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--) {
		if (aux_detectar_comer_y_propias_piezas(matriz, i, j, tab[i][j], this)) {
			break;
		}
		matriz.TAB[i][j] = PERMITIDO;
	}
	for (int i = row - 1, j = col + 1; i >= 0 && j < COL_SIZE; i--, j++) {
		if (aux_detectar_comer_y_propias_piezas(matriz, i, j, tab[i][j], this)) {
			break;
		}
		matriz.TAB[i][j] = PERMITIDO;
	}
	for (int i = row + 1, j = col - 1; i < ROW_SIZE && j >= 0; i++, j--) {
		if (aux_detectar_comer_y_propias_piezas(matriz, i, j, tab[i][j], this)) {
			break;
		}
		matriz.TAB[i][j] = PERMITIDO;
	}
	for (int i = row + 1, j = col + 1; i < ROW_SIZE && j < COL_SIZE; i++, j++) {
		if (aux_detectar_comer_y_propias_piezas(matriz, i, j, tab[i][j], this)) {
			break;
		}
		matriz.TAB[i][j] = PERMITIDO;
	}
}


tablero_info_t pieza_t::get_mov_permitidos(pieza_t** tab)
{
	// Aux
	pieza_t* a = this;

	// Inicializar matriz de movimientos permitidos:
	tablero_info_t matriz;
	for (int i = 0; i < ROW_SIZE; i++) {
		for (int j = 0; j < COL_SIZE; j++) {
			matriz.TAB[i][j] = NO_PERMITIDO;
		}
	}

	// Obtener la posición de la ficha
	int row, col;
	for (int i = 0; i < ROW_SIZE; i++) {
		for (int j = 0; j < COL_SIZE; j++) {
			if (this == &(tab[i][j])) {
				row = i;
				col = j;
			}
		}
	}


	if (this->getForma() == PEON) {       // Leo
		if (this->getColor() == BLANCA) {
			matriz.TAB[row][col] = PROPIA_PIEZA;
			if (row > 0) {
				matriz.TAB[row - 1][col] = tab[row - 1][col].getForma() == NO_PIEZA ? PERMITIDO : NO_PERMITIDO;
				if (row > 0) {
					matriz.TAB[row - 1][col - 1] = tab[row - 1][col - 1].getForma() != NO_PIEZA ? tab[row - 1][col - 1].getColor() == this->color ? NO_PERMITIDO :COMER_PIEZA : NO_PERMITIDO;
				}
				if (row < ROW_SIZE - 1) {
					matriz.TAB[row - 1][col + 1] = tab[row - 1][col + 1].getForma() != NO_PIEZA ? tab[row - 1][col + 1].getColor() == this->color ? NO_PERMITIDO : COMER_PIEZA : NO_PERMITIDO;
				}
			}
			if (row > 1) {
				matriz.TAB[row - 2][col] = tab[row - 2][col].getForma() == NO_PIEZA && row == 6 ? PERMITIDO : NO_PERMITIDO;
			}
		}
		else if (this->getColor() == NEGRA) {
			matriz.TAB[row][col] = PROPIA_PIEZA;
			matriz.TAB[row][col] = PROPIA_PIEZA;
			if (row + 1 < ROW_SIZE) {
				matriz.TAB[row + 1][col] = tab[row + 1][col].getForma() == NO_PIEZA ? PERMITIDO : NO_PERMITIDO;
				if (col > 0) {
					matriz.TAB[row + 1][col - 1] = tab[row + 1][col - 1].getForma() != NO_PIEZA ? tab[row + 1][col - 1].getColor() == this->color ? NO_PERMITIDO : COMER_PIEZA : NO_PERMITIDO;
				}
				if (col < COL_SIZE - 1) {
					matriz.TAB[row + 1][col + 1] = tab[row + 1][col + 1].getForma() != NO_PIEZA ? tab[row + 1][col + 1].getColor() == this->color ? NO_PERMITIDO : COMER_PIEZA : NO_PERMITIDO;
				}
			}
			if (row + 2 < ROW_SIZE) {
				matriz.TAB[row + 2][col] = tab[row + 2][col].getForma() == NO_PIEZA && row == 1 ? PERMITIDO : NO_PERMITIDO;
			}
		}
	}



	if (this->getForma() == CABALLO) {   // Leo
		matriz.TAB[row][col] = PROPIA_PIEZA;
		if (row > 3) {
			if (col > 0) {
				matriz.TAB[row - 2][col - 1] = tab[row - 2][col - 1].getForma() == NO_PIEZA ? PERMITIDO : tab[row - 2][col - 1].getColor() == this->color ? NO_PERMITIDO : COMER_PIEZA;
			}
			if (col < ROW_SIZE) {
				matriz.TAB[row - 2][col + 1] = tab[row - 2][col + 1].getForma() == NO_PIEZA ? PERMITIDO : tab[row - 2][col + 1].getColor() == this->color ? NO_PERMITIDO : COMER_PIEZA;
			}
		}
		if (row < COL_SIZE - 1) {
			if (col > 0) {
				matriz.TAB[row + 2][col - 1] = tab[row + 2][col - 1].getForma() == NO_PIEZA ? PERMITIDO : tab[row + 2][col - 1].getColor() == this->color ? NO_PERMITIDO : COMER_PIEZA;
			}
			if (col < ROW_SIZE) {
				matriz.TAB[row + 2][col + 1] = tab[row + 2][col + 1].getForma() == NO_PIEZA ? PERMITIDO : tab[row + 2][col + 1].getColor() == this->color ? NO_PERMITIDO : COMER_PIEZA;
			}
		}
		if (col > 2) {
			if (col > 0) {
				matriz.TAB[row - 1][col - 2] = tab[row - 1][col - 2].getForma() == NO_PIEZA ? PERMITIDO : tab[row - 1][col - 2].getColor() == this->color ? NO_PERMITIDO : COMER_PIEZA;
			}
			if (col < COL_SIZE) {
				matriz.TAB[row + 1][col - 2] = tab[row + 1][col - 2].getForma() == NO_PIEZA ? PERMITIDO : tab[row + 1][col - 2].getColor() == this->color ? NO_PERMITIDO : COMER_PIEZA;
			}
		}
		if (col < ROW_SIZE - 1) {
			if (row > 0) {
				matriz.TAB[row - 1][col + 2] = tab[row - 1][col + 2].getForma() == NO_PIEZA ? PERMITIDO : tab[row - 1][col + 2].getColor() == this->color ? NO_PERMITIDO : COMER_PIEZA;
			}
			if (row < COL_SIZE) {
				matriz.TAB[row + 1][col + 2] = tab[row + 1][col + 2].getForma() == NO_PIEZA ? PERMITIDO : tab[row + 1][col + 2].getColor() == this->color ? NO_PERMITIDO : COMER_PIEZA;
			}
		}
	}

	if (this->getForma() == ALFIL) {     // Leo
		int i = 1;
		while (row + i < ROW_SIZE && col + i < COL_SIZE) {
			if (tab[row + i][col + i].getForma() == NO_PIEZA) {
				matriz.TAB[row + i][col + i] = PERMITIDO;
			}
			else {
				matriz.TAB[row + i][col + i] = tab[row + i][col + i].getColor() == this->color ? NO_PERMITIDO : COMER_PIEZA;
				break;
			}
			i++;
		}
		i = 1;
		while (row + i < ROW_SIZE && col - i >= 0) {
			if (tab[row + i][col - i].getForma() == NO_PIEZA) {
				matriz.TAB[row + i][col - i] = PERMITIDO;
			}
			else {
				matriz.TAB[row + i][col - i] = tab[row + i][col + i].getColor() == this->color ? NO_PERMITIDO : COMER_PIEZA;
				break;
			}
			i++;
		}
		i = 1;
		while (row - i >= 0 && col - i >= 0) {
			if (tab[row - i][col - i].getForma() == NO_PIEZA) {
				matriz.TAB[row - i][col - i] = PERMITIDO;
			}
			else {
				matriz.TAB[row - i][col - i] = tab[row + i][col + i].getColor() == this->color ? NO_PERMITIDO : COMER_PIEZA;
				break;
			}
			i++;
		}
		i = 1;
		while (row - i >= 0 && col + i < COL_SIZE) {
			if (tab[row - i][col + i].getForma() == NO_PIEZA) {
				matriz.TAB[row - i][col + i] = PERMITIDO;
			}
			else {
				matriz.TAB[row - i][col + i] = tab[row + i][col + i].getColor() == this->color ? NO_PERMITIDO : COMER_PIEZA;
				break;
			}
			i++;
		}
		matriz.TAB[row][col] = PROPIA_PIEZA;
	}

	if (this->getForma() == TORRE) {     // Andrés

		// Movimiento en vertical y horizontal
		aux_permite_mov_vert_hor(matriz, tab, row, col, this);


		// Propia pieza
		matriz.TAB[row][col] = PROPIA_PIEZA;

		// Analizar si está clavada (próximanemnte)

	}

	if (this->getForma() == DAMA) {      // Andrés

		// Movimiento en vertical y horizontal
		aux_permite_mov_vert_hor(matriz, tab, row, col, this);

		// Movimiento en diagonal
		aux_permite_mov_diag(matriz, tab, row, col, this);


		// Propia pieza
		matriz.TAB[row][col] = PROPIA_PIEZA;



		// Analizar si está clavada (próximanemnte)


	}

	if (this->getForma() == REY) {      // Andrés

		// Movimiento a las casillas cercanas
		const int mat_aux[8][2] = { {-1,0}, {-1,1}, {0,1}, {1,1}, {1,0}, {1,-1}, {0,-1}, {-1,-1} };
		for (int i = 0; i < 8; i++) {
			matriz.TAB[row + mat_aux[i][0]][col + mat_aux[i][1]] = PERMITIDO;
			aux_detectar_comer_y_propias_piezas(matriz, row + mat_aux[i][0], col + mat_aux[i][1], tab[row + mat_aux[i][0]][col + mat_aux[i][1]], this);
		}
		matriz.TAB[row][col] = PROPIA_PIEZA;


		// Aplicar la recursividad por si con algun mov entra en jaque: (próximanemnte)


	}


	return matriz;
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

