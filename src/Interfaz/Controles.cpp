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

int controles::boton = 0;
int controles::estado = 0;

controles::controles() {
	this->mousePos = POINT();
	this->anchop = 35;
	this->altop = 20;
	
	this->ay = 0.0f;
	this->az = 0.0f;
	
}
void controles::coger_pos() {

	int mid_x = this->anchop / 2;
	int mid_y = this->altop / 2;
	GetCursorPos(&this->mousePos);
	
	if ((mousePos.x == mid_x) && (mousePos.y == mid_y))return;

	//SetCursorPos(mid_x,mid_y); ->si quiero dejarles el cursor en su sitio
	this->ay = (float)(mid_x - mousePos.x)/1000;
	this->az = (float)(mid_y - mousePos.y) / 1000;

}


