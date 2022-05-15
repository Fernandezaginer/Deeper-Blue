#include "Pieza.h"
#include "ChessRules.h"

#include <sstream>
#include <iostream>
using namespace std;


//-------------------------------------------------
//                  HISTORIAL
//-------------------------------------------------

bool Juego::anade_movimiento_historial(tablero_t posicion)
{
	if (numero_mov < NUM_MAX_MOV) {
		historial[numero_mov] = posicion;
		numero_mov++;
		return true;
	}
	return false;
}



//-------------------------------------------------
//           INFORMACIÓN DE LA PARTIDA
//-------------------------------------------------

bool Juego::tablas()
{
	return tablas_por_repeticiones_de_posicion() || tablas_por_rey_ahogado();
}

bool Juego::jaque_mate()
{
	return jaque_mate_playerA() || jaque_mate_playerB();
}

bool Juego::tablas_por_repeticiones_de_posicion()
{
	int num_repeticiones = 0;

	for (int i = 0; i < numero_mov; i++) {
		for (int j = i; j < numero_mov; j++) {
			if (tableros_iguales(&(historial[i]), &(historial[j])) == 1) {
				num_repeticiones++;
			}
		}
	}


	if (num_repeticiones > NUM_POS_TABLAS) {
		return true;
	}

	return false;
}

bool Juego::tablas_por_rey_ahogado()
{

	return false;
}

bool Juego::tablas_por_rey_ahogado(color_pieza_t color)
{

	int num_piezas = 0;

	for (int i = 0; i < ROW_SIZE; i++) {
		for (int j = 0; j < ROW_SIZE; j++) {

		}
	}


	return false;
}

bool Juego::jaque_player(color_pieza_t color, tablero_t mat)
{

	int row = -1, col = -1;
	bool jaque = false;

	// Obtener la posición del rey en cuestion
	for (int i = 0; i < ROW_SIZE; i++) {
		for (int j = 0; j < COL_SIZE; j++) {
			if (mat[i][j].getForma() == REY && mat[i][j].getColor() == color) {
				row = i;
				col = j;
			}
		}
	}

	// Ver si alguien se lo puede comer
	for (int i = 0; i < ROW_SIZE; i++) {
		for (int j = 0; j < COL_SIZE; j++) {
			if (mat[i][j].getColor() != color && mat[i][j].getColor() != NO_COLOR && mat[i][j].getForma() != REY && mat[i][j].getForma() != NO_PIEZA) {
				tablero_info_t aux = get_mov_permitidos(&(mat[i][j]), mat);
				if (aux.TAB[row][col] == COMER_PIEZA) {
					jaque = true;
					break;
				}
			}
		}
	}


	return jaque;
}

bool Juego::jaque_mate_player(color_pieza_t color, tablero_t mat)
{
	return false;
}

bool Juego::jaque_mate_playerA()
{


	return false;
}

bool Juego::jaque_mate_playerB()
{

	return false;
}


bool Juego::jaque_playerA()
{
	return jaque_player(BLANCA, tab) || !(jaque_mate_playerA());
}

bool Juego::jaque_playerB()
{
	return jaque_player(NEGRA, tab) || !(jaque_mate_playerB());
}


bool Juego::tableros_iguales(tablero_t* t1, tablero_t* t2)
{
	for (int i = 0; i < ROW_SIZE; i++) {
		for (int j = 0; j < ROW_SIZE; j++) {
			if (!(*(t1[i][j]) == *(t2[i][j]))) {
				return false; // Alguna pieza distinta
			}
		}
	}
	return true;
}



//-------------------------------------------------
//                  MOVIMIENTOS
//-------------------------------------------------


Juego::Juego()
{

	// Informacion del enrroque
	playerA_enroque_permitido = 1;
	playerB_enroque_permitido = 1;

	// Auxiliar:
	analisis_mov = 0;

	// Tablas por repeticion de movimiento
	numero_mov = 0;
	historial = new tablero_t[NUM_MAX_MOV];
	for (int i = 0; i < NUM_MAX_MOV; i++) {
		historial[i] = NULL;
	}


	// Reserva de memoria tablero
	tab = new pieza_t * [ROW_SIZE];
	for (int i = 0; i < ROW_SIZE; i++) {
		*(tab + i) = new pieza_t[COL_SIZE];
	}


	// Poner en blanco el tablero:
	for (int i = 0; i < ROW_SIZE; i++) {
		pieza_t* aux;
		aux = *(tab + i);
		for (int j = 0; j < COL_SIZE; j++) {
			(aux + j)->setColor(NO_COLOR);
			(aux + j)->setForma(NO_PIEZA);
		}
	}


	// Posicion inicial de la partida (Para una partida normal de momento)

	// Negras
	tab[0][0] = pieza_t(TORRE, NEGRA);
	tab[0][1] = pieza_t(CABALLO, NEGRA);
	tab[0][2] = pieza_t(ALFIL, NEGRA);
	tab[0][3] = pieza_t(DAMA, NEGRA);
	tab[0][4] = pieza_t(REY, NEGRA);
	tab[0][5] = pieza_t(ALFIL, NEGRA);
	tab[0][6] = pieza_t(CABALLO, NEGRA);
	tab[0][7] = pieza_t(TORRE, NEGRA);
	for (int i = 0; i < COL_SIZE; i++) {
		tab[1][i] = pieza_t(PEON, NEGRA);
	}

	// Blancas
	tab[7][0] = pieza_t(TORRE, BLANCA);
	tab[7][1] = pieza_t(CABALLO, BLANCA);
	tab[7][2] = pieza_t(ALFIL, BLANCA);
	tab[5][3] = pieza_t(DAMA, BLANCA);
	tab[7][4] = pieza_t(REY, BLANCA);
	tab[7][5] = pieza_t(ALFIL, BLANCA);
	tab[7][6] = pieza_t(CABALLO, BLANCA);
	tab[7][7] = pieza_t(TORRE, BLANCA);
	for (int i = 0; i < COL_SIZE-1; i++) {
		tab[6][i] = pieza_t(PEON, BLANCA);
	}


	// Test unitarios movimientos de piezas:
	//int aux_i = 3;
	//int aux_j = 0;

	//tab[aux_i][aux_j] = pieza_t(PEON, NEGRA);

	// Test enroque
	/*
	auto m = get_mov_permitidos(&(tab[7][4]), tab);
	cout << mov_print(m);
	*/

	// Test jaque:
	/*
	tab[1][3] = pieza_t(NO_PIEZA, NO_COLOR);
	tab[7][3] = pieza_t(REY, BLANCA);
	cout << jaque_player(BLANCA, tab) << endl;
	*/

	// Test recursividad:
	/*
	tab[1][3] = pieza_t(NO_PIEZA, NO_COLOR);
	cout << this->print();
	auto m = get_mov_permitidos(&(tab[7][4]), tab);
	cout << mov_print(m);
	*/


}

void Juego::tablero_inicio_normal()
{
	// Posicion inicial de la partida

	// Negras
	tab[0][0] = pieza_t(TORRE, NEGRA);
	tab[0][1] = pieza_t(CABALLO, NEGRA);
	tab[0][2] = pieza_t(ALFIL, NEGRA);
	tab[0][3] = pieza_t(DAMA, NEGRA);
	tab[0][4] = pieza_t(REY, NEGRA);
	tab[0][5] = pieza_t(ALFIL, NEGRA);
	tab[0][6] = pieza_t(CABALLO, NEGRA);
	tab[0][7] = pieza_t(TORRE, NEGRA);
	for (int i = 0; i < COL_SIZE; i++) {
		tab[1][i] = pieza_t(PEON, NEGRA);
	}

	// Blancas
	tab[7][0] = pieza_t(TORRE, BLANCA);
	tab[7][1] = pieza_t(CABALLO, BLANCA);
	tab[7][2] = pieza_t(ALFIL, BLANCA);
	tab[7][3] = pieza_t(DAMA, BLANCA);
	tab[7][4] = pieza_t(REY, BLANCA);
	tab[7][5] = pieza_t(ALFIL, BLANCA);
	tab[7][6] = pieza_t(CABALLO, BLANCA);
	tab[7][7] = pieza_t(TORRE, BLANCA);
	for (int i = 0; i < COL_SIZE; i++) {
		tab[6][i] = pieza_t(PEON, BLANCA);
	}
}


Juego::~Juego()
{
	for (int i = 0; i < ROW_SIZE; i++) {
		delete[] tab[i];
	}
	delete[] tab;
}

string Juego::print()
{
	ostringstream o;

	for (int i = 0; i < ROW_SIZE; i++) {
		pieza_t* aux;
		aux = *(this->tab + i);
		for (int j = 0; j < COL_SIZE; j++) {
			char car;

			switch ((aux + j)->getForma())
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

			o << " " << car << " ";

		}
		o << endl;
	}
	return o.str();
}


tablero_info_t Juego::get_mov_permitidos(pieza_t* a, tablero_t tab)
{

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
			if (a == &(tab[i][j])) {
				row = i;
				col = j;
			}
		}
	}

	// Obtener el color
	color_pieza_t color = tab[row][col].getColor();




	if (a->getForma() == PEON) {       // Leo

		if (a->getColor() == BLANCA) {
			matriz.TAB[row][col] = PROPIA_PIEZA;
			if (row > 0) {
				matriz.TAB[row - 1][col] = (tab[row - 1][col].getForma() == NO_PIEZA) ? PERMITIDO : NO_PERMITIDO;
				if (row > 0) {
					matriz.TAB[row - 1][col - 1] = tab[row - 1][col - 1].getForma() != NO_PIEZA ? tab[row - 1][col - 1].getColor() == a->getColor() ? NO_PERMITIDO : COMER_PIEZA : NO_PERMITIDO;
				}
				if (row < ROW_SIZE - 1) {
					matriz.TAB[row - 1][col + 1] = tab[row - 1][col + 1].getForma() != NO_PIEZA ? tab[row - 1][col + 1].getColor() == a->getColor() ? NO_PERMITIDO : COMER_PIEZA : NO_PERMITIDO;
				}
			}
			if (row > 1) {
				matriz.TAB[row - 2][col] = tab[row - 2][col].getForma() == NO_PIEZA && row == 6 ? PERMITIDO : NO_PERMITIDO;
			}
		}

		else if (a->getColor() == NEGRA) {
			matriz.TAB[row][col] = PROPIA_PIEZA;
			matriz.TAB[row][col] = PROPIA_PIEZA;
			if (row + 1 < ROW_SIZE) {
				matriz.TAB[row + 1][col] = tab[row + 1][col].getForma() == NO_PIEZA ? PERMITIDO : NO_PERMITIDO;
				if (col > 0) {
					matriz.TAB[row + 1][col - 1] = tab[row + 1][col - 1].getForma() != NO_PIEZA ? tab[row + 1][col - 1].getColor() == a->getColor() ? NO_PERMITIDO : COMER_PIEZA : NO_PERMITIDO;
				}
				if (col < COL_SIZE - 1) {
					matriz.TAB[row + 1][col + 1] = tab[row + 1][col + 1].getForma() != NO_PIEZA ? tab[row + 1][col + 1].getColor() == a->getColor() ? NO_PERMITIDO : COMER_PIEZA : NO_PERMITIDO;
				}
			}
			if (row + 2 < ROW_SIZE) {
				matriz.TAB[row + 2][col] = tab[row + 2][col].getForma() == NO_PIEZA && row == 1 ? PERMITIDO : NO_PERMITIDO;
			}
		}
	}



	if (a->getForma() == CABALLO) {   // Leo
		matriz.TAB[row][col] = PROPIA_PIEZA;
		if (row > 3) {
			if (col > 0) {
				matriz.TAB[row - 2][col - 1] = tab[row - 2][col - 1].getForma() == NO_PIEZA ? PERMITIDO : tab[row - 2][col - 1].getColor() == a->getColor() ? NO_PERMITIDO : COMER_PIEZA;
			}
			if (col < ROW_SIZE) {
				matriz.TAB[row - 2][col + 1] = tab[row - 2][col + 1].getForma() == NO_PIEZA ? PERMITIDO : tab[row - 2][col + 1].getColor() == a->getColor() ? NO_PERMITIDO : COMER_PIEZA;
			}
		}
		if (row < COL_SIZE - 1) {
			if (col > 0) {
				matriz.TAB[row + 2][col - 1] = tab[row + 2][col - 1].getForma() == NO_PIEZA ? PERMITIDO : tab[row + 2][col - 1].getColor() == a->getColor() ? NO_PERMITIDO : COMER_PIEZA;
			}
			if (col < ROW_SIZE) {
				matriz.TAB[row + 2][col + 1] = tab[row + 2][col + 1].getForma() == NO_PIEZA ? PERMITIDO : tab[row + 2][col + 1].getColor() == a->getColor() ? NO_PERMITIDO : COMER_PIEZA;
			}
		}
		if (col > 2) {
			if (row > 0) {
				matriz.TAB[row - 1][col - 2] = tab[row - 1][col - 2].getForma() == NO_PIEZA ? PERMITIDO : tab[row - 1][col - 2].getColor() == a->getColor() ? NO_PERMITIDO : COMER_PIEZA;
			}
			if (row < COL_SIZE) {
				matriz.TAB[row + 1][col - 2] = tab[row + 1][col - 2].getForma() == NO_PIEZA ? PERMITIDO : tab[row + 1][col - 2].getColor() == a->getColor() ? NO_PERMITIDO : COMER_PIEZA;
			}
		}
		if (col < ROW_SIZE - 1) {
			if (row > 0) {
				matriz.TAB[row - 1][col + 2] = tab[row - 1][col + 2].getForma() == NO_PIEZA ? PERMITIDO : tab[row - 1][col + 2].getColor() == a->getColor() ? NO_PERMITIDO : COMER_PIEZA;
			}
			if (row < COL_SIZE) {
				matriz.TAB[row + 1][col + 2] = tab[row + 1][col + 2].getForma() == NO_PIEZA ? PERMITIDO : tab[row + 1][col + 2].getColor() == a->getColor() ? NO_PERMITIDO : COMER_PIEZA;
			}
		}
	}

	if (a->getForma() == ALFIL) {     // Leo
		int i = 1;
		while (row + i < ROW_SIZE && col + i < COL_SIZE) {
			if (tab[row + i][col + i].getForma() == NO_PIEZA) {
				matriz.TAB[row + i][col + i] = PERMITIDO;
			}
			else {
				matriz.TAB[row + i][col + i] = tab[row + i][col + i].getColor() == a->getColor() ? NO_PERMITIDO : COMER_PIEZA;
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
				matriz.TAB[row + i][col - i] = tab[row + i][col + i].getColor() == a->getColor() ? NO_PERMITIDO : COMER_PIEZA;
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
				matriz.TAB[row - i][col - i] = tab[row + i][col + i].getColor() == a->getColor() ? NO_PERMITIDO : COMER_PIEZA;
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
				matriz.TAB[row - i][col + i] = tab[row + i][col + i].getColor() == a->getColor() ? NO_PERMITIDO : COMER_PIEZA;
				break;
			}
			i++;
		}
		matriz.TAB[row][col] = PROPIA_PIEZA;
	}

	if (a->getForma() == TORRE) {     // Andrés

		// Movimiento en vertical y horizontal
		a->aux_permite_mov_vert_hor(matriz, tab, row, col);


		// Propia pieza
		matriz.TAB[row][col] = PROPIA_PIEZA;

		// Analizar si está clavada:
		aux_detectar_jaques_a_la_descubierta(matriz, tab, row, col);

	}

	if (a->getForma() == DAMA) {      // Andrés

		// Movimiento en vertical y horizontal
		a->aux_permite_mov_vert_hor(matriz, tab, row, col);

		// Movimiento en diagonal
		a->aux_permite_mov_diag(matriz, tab, row, col);


		// Propia pieza
		matriz.TAB[row][col] = PROPIA_PIEZA;



		// Analizar si está clavada:
		aux_detectar_jaques_a_la_descubierta(matriz, tab, row, col);


	}

	if (a->getForma() == REY) {      // Andrés

		// Movimiento a las casillas cercanas
		const int mat_aux[8][2] = { {-1,0}, {-1,1}, {0,1}, {1,1}, {1,0}, {1,-1}, {0,-1}, {-1,-1} };
		for (int i = 0; i < 8; i++) {
			if (row + mat_aux[i][0] > 0 && row + mat_aux[i][0] < ROW_SIZE && col + mat_aux[i][1] > 0 && col + mat_aux[i][1] < COL_SIZE) {
				matriz.TAB[row + mat_aux[i][0]][col + mat_aux[i][1]] = PERMITIDO;
				a->aux_detectar_comer_y_propias_piezas(matriz, row + mat_aux[i][0], col + mat_aux[i][1], tab[row + mat_aux[i][0]][col + mat_aux[i][1]]);
			}
		}
		matriz.TAB[row][col] = PROPIA_PIEZA;


		// ¿Enrroque?
		if (a->getColor() == BLANCA && Juego::playerA_enroque_permitido) {
			// ¿Enrroque corto?
			if (tab[7][5].getForma() == NO_PIEZA && tab[7][6].getForma() == NO_PIEZA && tab[7][7].getForma() == TORRE) {
				matriz.TAB[7][6] = ENROQUE_C;
			}

			// ¿Enrroque largo?
			if (tab[7][1].getForma() == NO_PIEZA && tab[7][2].getForma() == NO_PIEZA && tab[7][3].getForma() == NO_PIEZA && tab[7][0].getForma() == TORRE) {
				matriz.TAB[7][2] = ENROQUE_L;
			}
		}

		if (a->getColor() == NEGRA && Juego::playerB_enroque_permitido) {
			// ¿Enrroque corto?
			if (tab[0][5].getForma() == NO_PIEZA && tab[0][6].getForma() == NO_PIEZA && tab[0][7].getForma() == TORRE) {
				matriz.TAB[0][6] = ENROQUE_C;
			}

			// ¿Enrroque largo?
			if (tab[0][1].getForma() == NO_PIEZA && tab[0][2].getForma() == NO_PIEZA && tab[0][3].getForma() == NO_PIEZA && tab[0][0].getForma() == TORRE) {
				matriz.TAB[0][2] = ENROQUE_L;
			}
		}


		// Analizar si está clavada:
		cout << mov_print(matriz);
		if (analisis_mov == 0) {
			analisis_mov = 1;
			aux_detectar_jaques_a_la_descubierta(matriz, tab, row, col);
			analisis_mov = 0;
		}


	}


	return matriz;
}

lista_movimientos Juego::get_mov_permitidos_l(tablero_t tab, int row_o, int col_o)
{
	tablero_info_t movimientos = this->get_mov_permitidos(&tab[row_o][col_o], tab);
	lista_movimientos resultado;
	for (int col_f = 0; col_f < COL_SIZE; col_f++) {
		for (int row_f = 0; row_f < ROW_SIZE; row_f++) {
			if(movimientos.TAB[row_f][col_f] > 0)
				resultado.push_back({ movimientos.TAB[row_f][col_f], row_o, col_o, row_f, col_f});
		}
	}
	return resultado;
}

void Juego::aux_detectar_jaques_a_la_descubierta(tablero_info_t& matriz, pieza_t** tab, int row, int col)
{
	for (int i = 0; i < ROW_SIZE; i++) {
		for (int j = 0; j < COL_SIZE; j++) {
			if (matriz.TAB[i][j] == PERMITIDO || matriz.TAB[i][j] == COMER_PIEZA) {

				// Crear tablero auxiliar:
				pieza_t** aux = new pieza_t * [ROW_SIZE];
				for (int i = 0; i < ROW_SIZE; i++) {
					*(aux + i) = new pieza_t[COL_SIZE];
				}
				for (int i = 0; i < ROW_SIZE; i++) {
					for (int j = 0; j < COL_SIZE; j++) {
						aux[i][j] = tab[i][j];
					}
				}

				// Suponer movimiento y ver si hay jaque:
				aux[i][j] = tab[row][col];
				aux[row][col] = pieza_t(NO_PIEZA, NO_COLOR);

				if (jaque_player(tab[row][col].getColor(), aux)) {
					matriz.TAB[i][j] = NO_PERMITIDO;
				}
				cout << mov_print(matriz);

				for (int i = 0; i < ROW_SIZE; i++) {
					delete[] aux[i];
				}
				delete[] aux;
			}
		}
	}
}

bool Juego::haz_movimiento(int row_o, int col_o, int row_f, int col_f)
{

	// Llamar al método mov_permitidos, para verificar el permiso
	tablero_info_t mat = get_mov_permitidos(&(tab[row_o][col_o]), tab);

	if (mat.TAB[row_f][col_f] != NO_PERMITIDO && mat.TAB[row_f][col_f] != PROPIA_PIEZA) {

		// Historial para tablas por repetición
		anade_movimiento_historial(tab);


		// Notación del movimiento (version larga)
		mov.clear();
		if (mat.TAB[row_f][col_f] != ENROQUE_C && mat.TAB[row_f][col_f] != ENROQUE_L) {
			mov << tab[row_o][col_o].pieza_to_char() << col_to_char(col_o) << row_to_char(row_o) << (mat.TAB[row_f][col_f] == COMER_PIEZA ? 'x' : ' ') << col_to_char(col_f) << row_to_char(row_f);
		}
		else if (mat.TAB[row_f][col_f] == ENROQUE_C) {
			mov << "0-0";
		}
		else if (mat.TAB[row_f][col_f] == ENROQUE_L) {
			mov << "0-0-0";
		}

	}


	// Realiza movimiento si permitido
	if (mat.TAB[row_f][col_f] == PERMITIDO || mat.TAB[row_f][col_f] == COMER_PIEZA) {
		pieza_t aux = this->tab[row_o][col_o];

		// Actualizar datos de las reglas:
		if (aux.getForma() == REY && aux.getColor() == BLANCA) {
			Juego::playerA_enroque_permitido = 1;
		}
		if (aux.getForma() == REY && aux.getColor() == NEGRA) {
			Juego::playerB_enroque_permitido = 1;
		}

		this->tab[row_o][col_o] = pieza_t(NO_PIEZA, NO_COLOR);
		this->tab[row_f][col_f] = aux;
		return true;
	}


	// Realizar enrroque:
	if (mat.TAB[row_o][col_o] == ENROQUE_C && this->tab[row_o][col_o].getForma() == BLANCA) {
		this->tab[7][4] = pieza_t(NO_PIEZA, NO_COLOR);
		this->tab[7][7] = pieza_t(NO_PIEZA, NO_COLOR);
		this->tab[7][5] = pieza_t(TORRE, BLANCA);
		this->tab[7][6] = pieza_t(REY, BLANCA);
		Juego::playerA_enroque_permitido = 0;
		return true;
	}
	if (mat.TAB[row_o][col_o] == ENROQUE_L && this->tab[row_o][col_o].getForma() == BLANCA) {
		this->tab[7][4] = pieza_t(NO_PIEZA, NO_COLOR);
		this->tab[7][0] = pieza_t(NO_PIEZA, NO_COLOR);
		this->tab[7][3] = pieza_t(TORRE, BLANCA);
		this->tab[7][2] = pieza_t(REY, BLANCA);
		Juego::playerA_enroque_permitido = 0;
		return true;
	}
	if (mat.TAB[row_o][col_o] == ENROQUE_C && this->tab[row_o][col_o].getForma() == NEGRA) {
		this->tab[0][4] = pieza_t(NO_PIEZA, NO_COLOR);
		this->tab[0][7] = pieza_t(NO_PIEZA, NO_COLOR);
		this->tab[0][5] = pieza_t(TORRE, NEGRA);
		this->tab[0][6] = pieza_t(REY, NEGRA);
		Juego::playerB_enroque_permitido = 0;
		return true;
	}
	if (mat.TAB[row_o][col_o] == ENROQUE_L && this->tab[row_o][col_o].getForma() == NEGRA) {
		this->tab[0][4] = pieza_t(NO_PIEZA, NO_COLOR);
		this->tab[0][0] = pieza_t(NO_PIEZA, NO_COLOR);
		this->tab[0][3] = pieza_t(TORRE, NEGRA);
		this->tab[0][2] = pieza_t(REY, NEGRA);
		Juego::playerB_enroque_permitido = 0;
		return true;
	}



	return false;
}




//-------------------------------------------------
//                  NOTACIÓN
//-------------------------------------------------

ostream& Juego::notacion_ulimo_moviento()
{
	return mov;
}

char Juego::row_to_char(int row)
{
	char aux;
	aux = '8' - row;
	return aux;
}

char Juego::col_to_char(int col)
{
	char aux;
	aux = 'a' + col;
	return aux;
	return 0;
}


//-------------------------------------------------
//                  SECUNDARIO
//-------------------------------------------------


int Juego::score_playerA()
{
	int puntuacion = 0;
	for (int i = 0; i < ROW_SIZE; i++) {
		for (int j = 0; j < COL_SIZE; j++) {
			if (tab[i][j].getColor() == BLANCA) {
				puntuacion += tab[i][j].valor();
			}
		}
	}
	return puntuacion;
}

int Juego::score_playerB()
{
	int puntuacion = 0;
	for (int i = 0; i < ROW_SIZE; i++) {
		for (int j = 0; j < COL_SIZE; j++) {
			if (tab[i][j].getColor() == NEGRA) {
				puntuacion += tab[i][j].valor();
			}
		}
	}
	return puntuacion;
}