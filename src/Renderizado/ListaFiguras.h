#include "Figura.h"
#include "ChessRules.h"
#include "CASILLA.h"
#pragma once




class ListaFiguras
{
	//JUGADOR1

public:
	static void dibuja(tablero_t& tab, CASILLA  casi[][COL_SIZE]);

	static Figura PEONJ1;
	static Figura TORREJ1;
	static Figura CABALLOJ1;
	static Figura ALFILJ1;
	static Figura REYJ1;
	static Figura REINAJ1;

	static Figura PEONJ2;
	static Figura TORREJ2;
	static Figura CABALLOJ2;
	static Figura ALFILJ2;
	static Figura REYJ2;
	static Figura REINAJ2;
};

