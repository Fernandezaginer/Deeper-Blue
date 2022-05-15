#pragma once
#include "freeglut.h"
#include <math.h>
#include <iostream>
#include <stdlib.h>
#include <ctime>
#include "Controles.h"
#include "ETSIDI.h"
#include "Inicio.h"
#include "Pantalla.h"
#include "Interfaz.h"

using namespace std;


class Interfaz
{
private:
	float x_ojo;
	float y_ojo;
	float z_ojo;
	
	pantalla pan;
	inicio in;
	controles con;
public:
	long long t_0 = time(NULL);
	int estado;
	Interfaz();
	void tecla(unsigned char key);
	void inicializa();
	void rotarOjo();
	void mueve();
	void dibuja();


};
