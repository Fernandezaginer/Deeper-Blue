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

controles::controles() {
	this->mousePos = POINT();
	this->anchop = 35;
	this->altop = 20;
	
	this->ay = 0.0f;
	this->az = 0.0f;	
}
void controles::coger_pos() {
	int screen_pos_x = glutGet((GLenum)GLUT_WINDOW_X);
	int screen_pos_y = glutGet((GLenum)GLUT_WINDOW_Y);

	int mid_x = this->anchop / 2;
	int mid_y = this->altop / 2;
	GetCursorPos(&this->mousePos);
	
	if ((mousePos.x == mid_x) && (mousePos.y == mid_y))return;

	//SetCursorPos(mid_x,mid_y); ->si quiero dejarles el cursor en su sitio
	//this->ay = (float)(mid_x - mousePos.x)/1000;
	//this->az = (float)(mid_y - mousePos.y) / 1000;

	this->ay = mousePos.x;
	this->az = mousePos.y;

	this->ay = this->ay - screen_pos_x;
	this->az = this->az - screen_pos_y;

	this->ay = this->ay *((float)glutGet(GLUT_SCREEN_WIDTH)/ (float)glutGet(GLUT_WINDOW_WIDTH))*(1600.0/1920.0);
	this->az = (this->az * ((float)glutGet(GLUT_SCREEN_HEIGHT) / (float)glutGet(GLUT_WINDOW_HEIGHT)) * (900.0/1080.0)) - 50;

	this->mousePos.x = ay;
	this->mousePos.y = az;


	//std::cout << "(" << this->mousePos.x << ", " << this->mousePos.y << ")" << "\t"<< "(" << this->ay << ", " << this->az << ")" <<endl;
}


