#include "VECTOR.h"
#include "COLOR.h"

#pragma once
class CASILLA
{
public:
	CASILLA() {}
	~CASILLA() {}

private:
	VECTOR pos;
	VECTOR Lim1, Lim2, Lim3, Lim4;
	COLOR col;

public:
	void setLims(VECTOR posInicial, VECTOR variacion, int fila, int columna);
	void dibuja();


};

