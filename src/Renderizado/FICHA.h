#include "VECTOR.h"
#include "COLOR.h"

#pragma once
class FICHA
{
public:
	FICHA() :pieza(NOPIEZA), jugador(NOJUGADOR), radio(0) {};
	~FICHA() {}

	enum pieza_n { NOPIEZA = -1, TIPO0, TIPO1, TIPO2 };
	enum jugador_n { NOJUGADOR = -1, JUGADOR1, JUGADOR2 };

private:
	int pieza;
	int jugador;
	VECTOR posicion;
	float radio;
	COLOR col;



public:
	void setPos(float x, float y);
	void setRad(float r);
	void dibuja();
	void setPiezaJugador(int p, int ju);

};

