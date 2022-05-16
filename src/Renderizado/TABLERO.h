#include "FICHA.h"
#include "CASILLA.h"
#include "ChessRules.h"
#include "COLOR.h"
#pragma once

class TABLERO
{
public:
	TABLERO();
	~TABLERO();

private:
	CASILLA cas[ROW_SIZE][COL_SIZE];
	VECTOR Lim1, Lim2, Lim3, Lim4;
	VECTOR var;
	COLOR color_fondo;

public:
	void inicializa();
	void dibuja(tablero_t tab);
	void modifica();
	void mueve();
	void pintMovPermitidos(tablero_info_t ti);
	void resetColor();
	pieza_t* seleccionarPiezaRaton(int b, int e, int x, int y);

};

