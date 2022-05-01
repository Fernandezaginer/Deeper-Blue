#include "TABLERO.h"
#pragma once
class Mundo
{
public: 
	Mundo(int n = 1) : t(n), cuadradolados(n), x_ojo(0), y_ojo(0), z_ojo(0) {}
	void tecla(unsigned char key);
	void inicializa();
	void rotarOjo();
	void mueve();
	void dibuja();

private:
	float x_ojo;
	float y_ojo;
	float z_ojo;

	TABLERO t;
	int cuadradolados;

};
