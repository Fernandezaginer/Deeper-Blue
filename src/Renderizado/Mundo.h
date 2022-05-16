#include "TABLERO.h"
#include "ChessRules.h"
#pragma once
class Mundo
{
public: 
	void tecla(unsigned char key);
	void inicializa();
	void rotarOjo();
	void mueve();
	void dibuja();
	void raton(int b, int e, int x, int y);

private:
	float x_ojo;
	float y_ojo;
	float z_ojo;

	TABLERO t;
	Juego j;


};
