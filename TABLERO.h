#include "FICHA.h"
#include "CASILLA.h"
#pragma once

class TABLERO
{
public:
	TABLERO(int n);
	~TABLERO();

private:
	FICHA** pel;
	CASILLA** cas;
	int lado;
	VECTOR Lim1, Lim2, Lim3, Lim4;
	VECTOR var;
	COLOR color_fondo;

public:
	void inicializa();
	void dibuja();
	void modifica();
	void mueve();
};

