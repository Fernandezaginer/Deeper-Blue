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
bool controles::fp_estado = false;
bool controles::fn_estado = false;
unsigned char controles::key = NULL;

controles::controles() {
	this->mousePos = POINT();
	
	this->ay = 0.0f;
	this->az = 0.0f;	
}
void controles::coger_pos() {
	int screen_pos_x = glutGet((GLenum)GLUT_WINDOW_X);
	int screen_pos_y = glutGet((GLenum)GLUT_WINDOW_Y);

	GetCursorPos(&this->mousePos);

	this->ay = mousePos.x;
	this->az = mousePos.y;

	this->ay = this->ay - screen_pos_x;
	this->az = this->az - screen_pos_y;

	this->ay = this->ay * (1600.0/(float)glutGet(GLUT_WINDOW_WIDTH));
	this->az = (this->az * (900.0/(float)glutGet(GLUT_WINDOW_HEIGHT))) - 50;

	std::cout << "(" << glutGet(GLUT_SCREEN_WIDTH) << ", " << glutGet(GLUT_SCREEN_HEIGHT) << ")" << "\t" << "(" << this->mousePos.x << ", " << this->mousePos.y << ")" << "\t" << "(" << this->ay << ", " << this->az << ")" << endl;

	this->mousePos.x = ay;
	this->mousePos.y = az;
}

bool controles::read_fp()
{
	if (controles::fp_estado == true) {
		controles::fp_estado = false;
		return true;
	}
	return false;
}

bool controles::read_fn()
{
	if (controles::fn_estado == true) {
		controles::fn_estado = false;
		return true;
	}
	return false;
}

unsigned char controles::read_key()
{
	unsigned char aux = controles::key;
	controles::key = NULL;
	return aux;
}
