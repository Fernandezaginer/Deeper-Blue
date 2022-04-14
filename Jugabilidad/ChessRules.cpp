
#include "Pieza.h"
#include "ChessRules.h"

#include <sstream>
#include <iostream>
using namespace std;



Juego::Juego()
{

	// Inicializacion de atributos
	numero_turnos_sin_comer = 0;


	// Reserva de memoria
	tab = new pieza_t* [ROW_SIZE];
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
	tab[7][3] = pieza_t(DAMA, BLANCA);
	tab[7][4] = pieza_t(REY, BLANCA);
	tab[7][5] = pieza_t(ALFIL, BLANCA);
	tab[7][6] = pieza_t(CABALLO, BLANCA);
	tab[7][7] = pieza_t(TORRE, BLANCA);
	for (int i = 0; i < COL_SIZE; i++) {
		tab[6][i] = pieza_t(PEON, BLANCA);
	}


	// Test unitarios movimientos de piezas:
	/*
	int aux_i = 2;
	int aux_j = 5;

	tab[3][4] = pieza_t(PEON, BLANCA);
	tab[3][0] = pieza_t(PEON, BLANCA);
	tab[aux_i][aux_j] = pieza_t(REY, NEGRA);

	auto m = tab[aux_i][aux_j].get_mov_permitidos(tab);
	cout << mov_print(m);
	*/
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
		aux = *(tab + i);
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
