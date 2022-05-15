
#include "Pieza.h"
#include "ChessRules.h"
#include "chesstime.h"

#include <sstream>
#include <iostream>
using namespace std;


//-------------------------------------------------
//                  HISTORIAL
//-------------------------------------------------

bool Juego::anade_movimiento_historial(tablero_t posicion)
{
	if (numero_mov < NUM_MAX_MOV) {

		// Reserva espacio:
		tablero_t aux;
		aux = new pieza_t * [ROW_SIZE];
		for (int i = 0; i < ROW_SIZE; i++) {
			*(aux + i) = new pieza_t[COL_SIZE];
		}
		
		// Copair el tablero:
		for (int i = 0; i < ROW_SIZE; i++) {
			for (int j = 0; j < COL_SIZE; j++) {
				aux[i][j] = posicion[i][j];
			}
		}
		historial[numero_mov] = aux;
		numero_mov++;
		return true;
	}
	return false;
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
//           INFORMACIÓN DE LA PARTIDA
//-------------------------------------------------

bool Juego::tablas()
{
	return tablas_por_repeticiones_de_posicion() || tablas_por_rey_ahogado();
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
	return (rey_ahogado(BLANCA) && chesstime::isTrunPlayerA) || (rey_ahogado(NEGRA) && chesstime::isTrunPlayerB);
}

bool Juego::jaque_mate()
{
	return jaque_mate_playerA() || jaque_mate_playerB();
}

bool Juego::jaque_mate_playerA()
{
	return rey_jaque_mate(BLANCA);
}

bool Juego::jaque_mate_playerB()
{
	return rey_jaque_mate(NEGRA);
}

bool Juego::jaque_playerA()
{
	return jaque_player(BLANCA, tab) || !(jaque_mate_playerA());
}

bool Juego::jaque_playerB()
{
	return jaque_player(NEGRA, tab) || !(jaque_mate_playerB());
}

bool Juego::playerA_won()
{
	return jaque_mate_playerB() || chesstime::PlaB_end_time();
}

bool Juego::playerB_won()
{
	return jaque_mate_playerA() || chesstime::PlaA_end_time();
}



//-------------------------------------------------
//                  MOVIMIENTOS
//-------------------------------------------------


Juego::Juego(modo_partida_t mode) : chesstime(mode)
{

	// Gestión del tiempo:
	chesstime::start();

	// Informacion del enrroque
	playerA_enroque_permitido = 1;
	playerB_enroque_permitido = 1;

	// Auxiliar:
	analisis_mov = 0;


	// Reserva de memoria tablero
	tab = new pieza_t * [ROW_SIZE];
	for (int i = 0; i < ROW_SIZE; i++) {
		*(tab + i) = new pieza_t[COL_SIZE];
	}

	// Tablas por repeticion de movimiento
	numero_mov = 0;
	historial = new tablero_t[NUM_MAX_MOV];
	for (int i = 0; i < NUM_MAX_MOV; i++) {
		historial[i] = NULL;
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
	tablero_inicio_normal();
	

	// Test unitario enrroque:
	//tab[0][1] = pieza_t(NO_PIEZA, NEGRA);
	//tab[0][2] = pieza_t(NO_PIEZA, NEGRA);
	//tab[0][3] = pieza_t(NO_PIEZA, NEGRA);
	//cout << this->print();
	//tablero_info_t aux = get_mov_permitidos(&(tab[0][4]), tab);
	//cout << mov_print(aux);
	//haz_movimiento(0, 4, 0, 2);
	//cout << this->print();


	// Test unitario comer al paso:
	//cout << this->print();
	//haz_movimiento(6, 4, 4, 4);
	//cout << this->print();
	//haz_movimiento(1, 2, 3, 2);
	//cout << this->print();
	//haz_movimiento(4, 4, 3, 4);
	//cout << this->print();
	//haz_movimiento(1, 3, 3, 3);
	//cout << this->print();
	//haz_movimiento(3, 4, 2, 3);
	//cout << this->print();


	// Test unitario promoción a dama:
	//for (int i = 0; i < ROW_SIZE; i++) {
	//	pieza_t* aux;
	//	aux = *(tab + i);
	//	for (int j = 0; j < COL_SIZE; j++) {
	//		(aux + j)->setColor(NO_COLOR);
	//		(aux + j)->setForma(NO_PIEZA);
	//	}
	//}
	//tab[1][4] = pieza_t(PEON, BLANCA);
	//cout << this->print();
	//haz_movimiento(1, 4, 0, 4);
	//cout << this->print();


	// Test unitario recursividad (piezas clavadas)
	//tab[0][3] = pieza_t(NO_PIEZA, NO_COLOR);
	//tab[0][4] = pieza_t(DAMA, NEGRA);
	//tab[5][3] = pieza_t(TORRE, BLANCA);
	//tab[5][4] = pieza_t(TORRE, BLANCA);
	//tab[1][4] = pieza_t();
	//tab[6][4] = pieza_t();
	//cout << this->print();
	//tablero_info_t aux = get_mov_permitidos(&(tab[5][4]), tab);
	//cout << mov_print(aux);
	//aux = get_mov_permitidos(&(tab[5][3]), tab);
	//cout << mov_print(aux);


	// Test unitario rey ahogado
	//for (int i = 0; i < ROW_SIZE; i++) {
	//	pieza_t* aux;
	//	aux = *(tab + i);
	//	for (int j = 0; j < COL_SIZE; j++) {
	//		(aux + j)->setColor(NO_COLOR);
	//		(aux + j)->setForma(NO_PIEZA);
	//	}
	//}
	//tab[7][7] = pieza_t(REY, BLANCA);
	//tab[5][6] = pieza_t(TORRE, NEGRA);
	//tab[6][5] = pieza_t(TORRE, NEGRA);
	//// tab[4][4] = pieza_t(TORRE, BLANCA);
	//cout << this->print();
	//cout << tablas_por_rey_ahogado() << endl;
	//cout << this->jaque_mate();

	// Test unitario jaque mate
	//for (int i = 0; i < ROW_SIZE; i++) {
	//	pieza_t* aux;
	//	aux = *(tab + i);
	//	for (int j = 0; j < COL_SIZE; j++) {
	//		(aux + j)->setColor(NO_COLOR);
	//		(aux + j)->setForma(NO_PIEZA);
	//	}
	//}
	//tab[4][4] = pieza_t(TORRE, BLANCA);
	//tab[7][7] = pieza_t(REY, BLANCA);
	//tab[6][5] = pieza_t(TORRE, NEGRA);
	//tab[7][5] = pieza_t(TORRE, NEGRA);
	////tab[7][4] = pieza_t(TORRE, BLANCA);
	//tab[2][6] = pieza_t(TORRE, BLANCA);
	//cout << this->print();
	//cout << tablas_por_rey_ahogado() << endl;
	//cout << this->jaque_mate();

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

void Juego::tablero_inicio_peones()
{
	// Negras:
	tab[0][4] = pieza_t(REY, NEGRA);
	for (int i = 0; i < COL_SIZE; i++) {
		tab[1][i] = pieza_t(PEON, NEGRA);
	}

	// Blancas:
	tab[7][4] = pieza_t(REY, BLANCA);
	for (int i = 0; i < COL_SIZE; i++) {
		tab[6][i] = pieza_t(PEON, BLANCA);
	}

}

Juego::~Juego()
{

	// Borrar el tablero
	for (int i = 0; i < ROW_SIZE; i++) {
		delete[] tab[i];
	}
	delete[] tab;

	// Borrar el historial:
	if (numero_mov > 0) {
		for (int i = 0; i < numero_mov; i++) {
			for (int j = 0; j < ROW_SIZE; j++) {
				delete[] historial[i][j];
			}
		}
		delete[] historial;
	}
}

Juego::Juego(Juego& J) : chesstime(chesstime::getModo())
{

	// Informacion del enrroque
	this->playerA_enroque_permitido = J.playerA_enroque_permitido;
	this->playerB_enroque_permitido = J.playerB_enroque_permitido;

	// Auxiliar:
	this->analisis_mov = J.analisis_mov;

	// Reserva de memoria tablero
	this->tab = new pieza_t * [ROW_SIZE];
	for (int i = 0; i < ROW_SIZE; i++) {
		*(this->tab + i) = new pieza_t[COL_SIZE];
	}

	// Copiar el tablero
	for (int i = 0; i < ROW_SIZE; i++) {
		for (int j = 0; j < COL_SIZE; j++) {
			this->tab[i][j] = J.tab[i][j];
		}
	}

	// Historial
	this->historial = new tablero_t[NUM_MAX_MOV];
	for (int i = 0; i < NUM_MAX_MOV; i++) {
		this->historial[i] = NULL;
	}

	if (J.numero_mov > 0) {
		for (int k = 0; k < J.numero_mov; k++) {
			this->historial[k] = J.historial[k];
		}
	}

}

string Juego::print(tablero_t t)
{
	ostringstream o;

	for (int i = 0; i < ROW_SIZE; i++) {
		pieza_t* aux;
		aux = *(t + i);
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
	o << endl;

	return o.str();
}

// Segun dinámica del juego
tablero_info_t Juego::mov_permitidos(pieza_t* a, tablero_t tab)
{	
	tablero_info_t aux;
	for (int i = 0; i < ROW_SIZE; i++) {
		for (int j = 0; j < COL_SIZE; j++) {
			aux.TAB[i][j] = NO_PERMITIDO;
		}
	}

	if (a->getColor() == BLANCA && chesstime::isTrunPlayerA || a->getColor() == NEGRA && chesstime::isTrunPlayerB) {
		aux = get_mov_permitidos(a, tab);
	}

	return aux;
}

// Segun dinámica del juego
bool Juego::movimiento(int row_o, int col_o, int row_f, int col_f)
{
	if (tab[row_o][col_o].getColor() == BLANCA && chesstime::isTrunPlayerA || tab[row_o][col_o].getColor() == NEGRA && chesstime::isTrunPlayerB) {

		bool mov_ok = haz_movimiento(row_o, col_o, row_f, col_f);
		if (chesstime::isTrunPlayerA) {
			turnPlayerB();
		}
		else {
			turnPlayerA();
		}

		return mov_ok;
	}
	return false;
}

// General
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
				matriz.TAB[row - 1][col] = tab[row - 1][col].getForma() == NO_PIEZA ? PERMITIDO : NO_PERMITIDO;
				if (row > 0) {
					matriz.TAB[row - 1][col - 1] = tab[row - 1][col - 1].getForma() != NO_PIEZA ? tab[row - 1][col - 1].getColor() == a->color ? NO_PERMITIDO : COMER_PIEZA : NO_PERMITIDO;
				}
				if (row < ROW_SIZE - 1) {
					matriz.TAB[row - 1][col + 1] = tab[row - 1][col + 1].getForma() != NO_PIEZA ? tab[row - 1][col + 1].getColor() == a->color ? NO_PERMITIDO : COMER_PIEZA : NO_PERMITIDO;
				}
			}
			if (row == 6) {
				matriz.TAB[row - 2][col] = tab[row - 2][col].getForma() == NO_PIEZA && tab[row - 1][col].getForma() == NO_PIEZA ? PERMITIDO : NO_PERMITIDO;
			}
		}
		else if (a->getColor() == NEGRA) {
			matriz.TAB[row][col] = PROPIA_PIEZA;
			matriz.TAB[row][col] = PROPIA_PIEZA;
			if (row + 1 < ROW_SIZE) {
				matriz.TAB[row + 1][col] = tab[row + 1][col].getForma() == NO_PIEZA ? PERMITIDO : NO_PERMITIDO;
				if (col > 0) {
					matriz.TAB[row + 1][col - 1] = tab[row + 1][col - 1].getForma() != NO_PIEZA ? tab[row + 1][col - 1].getColor() == a->color ? NO_PERMITIDO : COMER_PIEZA : NO_PERMITIDO;
				}
				if (col < COL_SIZE - 1) {
					matriz.TAB[row + 1][col + 1] = tab[row + 1][col + 1].getForma() != NO_PIEZA ? tab[row + 1][col + 1].getColor() == a->color ? NO_PERMITIDO : COMER_PIEZA : NO_PERMITIDO;
				}
			}
			if (row == 1) {
				matriz.TAB[row + 2][col] = tab[row + 2][col].getForma() == NO_PIEZA && tab[row + 1][col].getForma() == NO_PIEZA ? PERMITIDO : NO_PERMITIDO;
			}
		}

		aux_detectar_comer_al_paso(matriz, tab[row][col], row, col);
		aux_detectar_promocion(matriz, tab[row][col], row, col);

		// Analizar si está clavada:
		if (analisis_mov == 0) {
			analisis_mov = 1;
			aux_detectar_jaques_a_la_descubierta(matriz, tab, row, col);
			analisis_mov = 0;
		}


	}



	if (a->getForma() == CABALLO) {   // Leo
		/*
		matriz.TAB[row][col] = PROPIA_PIEZA;
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
		*/
	}

	if (a->getForma() == ALFIL) {     // Leo

		/*
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
		*/
	}

	if (a->getForma() == TORRE) {     // Andrés

		// Movimiento en vertical y horizontal
		a->aux_permite_mov_vert_hor(matriz, tab, row, col);


		// Propia pieza
		matriz.TAB[row][col] = PROPIA_PIEZA;

		// Analizar si está clavada:
		if (analisis_mov == 0) {
			analisis_mov = 1;
			aux_detectar_jaques_a_la_descubierta(matriz, tab, row, col);
			analisis_mov = 0;
		}

	}

	if (a->getForma() == DAMA) {      // Andrés

		// Movimiento en vertical y horizontal
		a->aux_permite_mov_vert_hor(matriz, tab, row, col);

		// Movimiento en diagonal
		a->aux_permite_mov_diag(matriz, tab, row, col);


		// Propia pieza
		matriz.TAB[row][col] = PROPIA_PIEZA;



		// Analizar si está clavada:
		if (analisis_mov == 0) {
			analisis_mov = 1;
			aux_detectar_jaques_a_la_descubierta(matriz, tab, row, col);
			analisis_mov = 0;
		}


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
		if (analisis_mov == 0) {
			analisis_mov = 1;
			aux_detectar_jaques_a_la_descubierta(matriz, tab, row, col);
			analisis_mov = 0;
		}

	}


	return matriz;
}

// General
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
			mov << tab[row_o][col_o].pieza_to_char() << col_to_char(col_o) << row_to_char(row_o) << (mat.TAB[row_f][col_f] == (COMER_PIEZA || COMER_AL_PASO_L || COMER_AL_PASO_R) ? 'x' : ' ') << col_to_char(col_f) << row_to_char(row_f);
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
	if (mat.TAB[row_f][col_f] == ENROQUE_C && this->tab[row_o][col_o].getColor() == BLANCA) {
		this->tab[7][4] = pieza_t(NO_PIEZA, NO_COLOR);
		this->tab[7][7] = pieza_t(NO_PIEZA, NO_COLOR);
		this->tab[7][5] = pieza_t(TORRE, BLANCA);
		this->tab[7][6] = pieza_t(REY, BLANCA);
		Juego::playerA_enroque_permitido = 0;
		return true;
	}
	if (mat.TAB[row_f][col_f] == ENROQUE_L && this->tab[row_o][col_o].getColor() == BLANCA) {
		this->tab[7][4] = pieza_t(NO_PIEZA, NO_COLOR);
		this->tab[7][0] = pieza_t(NO_PIEZA, NO_COLOR);
		this->tab[7][3] = pieza_t(TORRE, BLANCA);
		this->tab[7][2] = pieza_t(REY, BLANCA);
		Juego::playerA_enroque_permitido = 0;
		return true;
	}
	if (mat.TAB[row_f][col_f] == ENROQUE_C && this->tab[row_o][col_o].getColor() == NEGRA) {
		this->tab[0][4] = pieza_t(NO_PIEZA, NO_COLOR);
		this->tab[0][7] = pieza_t(NO_PIEZA, NO_COLOR);
		this->tab[0][5] = pieza_t(TORRE, NEGRA);
		this->tab[0][6] = pieza_t(REY, NEGRA);
		Juego::playerB_enroque_permitido = 0;
		return true;
	}
	if (mat.TAB[row_f][col_f] == ENROQUE_L && this->tab[row_o][col_o].getColor() == NEGRA) {
		this->tab[0][4] = pieza_t(NO_PIEZA, NO_COLOR);
		this->tab[0][0] = pieza_t(NO_PIEZA, NO_COLOR);
		this->tab[0][3] = pieza_t(TORRE, NEGRA);
		this->tab[0][2] = pieza_t(REY, NEGRA);
		Juego::playerB_enroque_permitido = 0;
		return true;
	}

	// comer al paso:
	if (mat.TAB[row_f][col_f] == COMER_AL_PASO_L) {
		
		// Comer el peón contrario
		this->tab[row_o][col_o - 1] = pieza_t();

		// Avanzar el peon:
		this->tab[row_f][col_f] = this->tab[row_o][col_o];
		this->tab[row_o][col_o] = pieza_t();

		return true;
	}

	if (mat.TAB[row_f][col_f] == COMER_AL_PASO_R) {
		
		// Comer el peón contrario
		this->tab[row_o][col_o + 1] = pieza_t();

		// Avanzar el peon:
		this->tab[row_f][col_f] = this->tab[row_o][col_o];
		this->tab[row_o][col_o] = pieza_t();

		return true;
	}

	// Promoción del peón
	if (mat.TAB[row_f][col_f] == PROMOCION) {
		tab[row_f][col_f] = pieza_t(DAMA, tab[row_o][col_o].getColor());
		tab[row_o][col_o] = pieza_t();
		return true;
	}


	return false;
}


//-------------------------------------------------
//              REGLAS ESPECIALES
//-------------------------------------------------


void Juego::aux_detectar_comer_al_paso(tablero_info_t& matriz, pieza_t peon, int row, int col)
{

	int row_ini;
	int row_peo[2];
	int desp_row;

	if (peon.getColor() == BLANCA) {
		row_ini = 1;
		row_peo[0] = 2;
		row_peo[1] = 3;
		desp_row = -1;
	}
	else {
		row_ini = 6;
		row_peo[0] = 5;
		row_peo[1] = 4;
		desp_row = 1;
	}

	if (numero_mov >=4) {

		tablero_t t_o = historial[numero_mov - 1];
		tablero_t t_1 = tab;

		tablero_t peones_adv = new pieza_t * [ROW_SIZE];
		for (int i = 0; i < ROW_SIZE; i++) {
			*(peones_adv + i) = new pieza_t[COL_SIZE];
		}
		for (int i = 0; i < ROW_SIZE; i++) {
			for (int j = 0; j < COL_SIZE; j++) {
				peones_adv[i][j] = *(new pieza_t());
			}
		}

		// Peones en posición inicial:
		for (int j = 0; j < COL_SIZE; j++) {
			if (t_o[row_ini][j].getForma() == PEON && t_o[row_ini][j].getColor() ==  (peon.getColor() == BLANCA ? NEGRA : BLANCA) ) {
				peones_adv[row_ini][j] = t_o[row_ini][j];
			}
		}


		// Peones que cambiaron su posición inicial
		for (int j = 0; j < COL_SIZE; j++) {
			if (peones_adv[row_ini][j] == t_1[row_ini][j]) {
				peones_adv[row_ini][j] = *(new pieza_t());
			}
			else if(t_1[row_peo[0]][j].getForma() == PEON) {
				peones_adv[row_ini][j] = t_1[row_ini][j];
				peones_adv[row_peo[0]][j] = t_o[row_ini][j];
			}
			else if (t_1[row_peo[1]][j].getForma() == PEON) {
				peones_adv[row_ini][j] = t_1[row_ini][j];
				peones_adv[row_peo[1]][j] = t_o[row_ini][j];
			}
		}


		// Ver si el peon es adyacente a los opuestos
		bool adyacente_der = 0;
		bool adyacente_izq = 0;
		for (int i : row_peo) {
			
			// A la derecha
			if (col < 7) {
				if (peones_adv[i][col + 1].getForma() == PEON && row == i) {
					adyacente_der = 1;
				}
			}

			// A la izquiera
			if (col > 0) {
				if (peones_adv[i][col - 1].getForma() == PEON && row == i) {
					adyacente_izq = 1;
				}
			}

		}

		if (adyacente_der) {
			matriz.TAB[row + desp_row][col + 1] = COMER_AL_PASO_R;
		}

		if (adyacente_izq) {
			matriz.TAB[row + desp_row][col - 1] = COMER_AL_PASO_L;
		}


	}

}

void Juego::aux_detectar_promocion(tablero_info_t& matriz, pieza_t peon, int row, int col)
{
	int row_promocion;
	if (peon.getColor() == BLANCA) {
		row_promocion = 0;		
	}
	else {
		row_promocion = 7;
	}

	for (int j = 0; j < COL_SIZE; j++) {
		if (matriz.TAB[row_promocion][j] != NO_PERMITIDO) {
			matriz.TAB[row_promocion][j] = PROMOCION;
		}
	}
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

				for (int i = 0; i < ROW_SIZE; i++) {
					delete[] aux[i];
				}
				delete[] aux;
			}
		}
	}
}

bool Juego::rey_ahogado(color_pieza_t color)
{

	int num_mov_perm = 0;

	// Analizar si alguna pieza puede mover:
	for (int i = 0; i < ROW_SIZE; i++) {
		for (int j = 0; j < ROW_SIZE; j++) {

			if (tab[i][j].getColor() == color) {
				tablero_info_t aux = get_mov_permitidos(&(tab[i][j]), tab);

				for (int ii = 0; ii < ROW_SIZE; ii++) {
					for (int jj = 0; jj < COL_SIZE; jj++) {
						if (aux.TAB[ii][jj] != PROPIA_PIEZA && aux.TAB[ii][jj] != NO_PERMITIDO) {
							num_mov_perm++;
						}
					}
				}

			}
		}
	}

	return (num_mov_perm <= 0) && !jaque_player(color, tab);
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

bool Juego::rey_jaque_mate(color_pieza_t color)
{

	int num_mov_perm = 0;

	// Analizar si alguna pieza puede mover:
	for (int i = 0; i < ROW_SIZE; i++) {
		for (int j = 0; j < ROW_SIZE; j++) {

			if (tab[i][j].getColor() == color) {
				tablero_info_t aux = get_mov_permitidos(&(tab[i][j]), tab);

				for (int ii = 0; ii < ROW_SIZE; ii++) {
					for (int jj = 0; jj < COL_SIZE; jj++) {
						if (aux.TAB[ii][jj] != PROPIA_PIEZA && aux.TAB[ii][jj] != NO_PERMITIDO) {
							num_mov_perm++;
						}
					}
				}

			}
		}
	}

	return (num_mov_perm <= 0) && jaque_player(color, tab);
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
