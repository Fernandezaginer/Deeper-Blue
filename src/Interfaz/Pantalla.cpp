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

pantalla::pantalla() {
	this->ancho = 35;
	this->alto = 20;
	this->rojo = 255;
	this->verde = 255;
	this->azul = 255;
	this->limite1x = ancho / 2;
	this->limite1y = alto / 2;

}
void pantalla::dibuja() {
	glDisable(GL_LIGHTING);
	glColor3ub(this->rojo, this->verde, this->azul);
	glBegin(GL_LINES);
	glVertex3d(-this->limite1x, this->limite1y, 0);
	glVertex3d(this->limite1x, this->limite1y, 0);
	glEnd();
	glEnable(GL_LIGHTING);

	glDisable(GL_LIGHTING);
	glColor3ub(this->rojo, this->verde, this->azul);
	glBegin(GL_LINES);
	glVertex3d(this->limite1x, this->limite1y, 0);
	glVertex3d(this->limite1x, -this->limite1y, 0);
	glEnd();
	glEnable(GL_LIGHTING);

	glDisable(GL_LIGHTING);
	glColor3ub(this->rojo, this->verde, this->azul);
	glBegin(GL_LINES);
	glVertex3d(this->limite1x, -this->limite1y, 0);
	glVertex3d(-this->limite1x, -this->limite1y, 0);
	glEnd();
	glEnable(GL_LIGHTING);

	glDisable(GL_LIGHTING);
	glColor3ub(this->rojo, this->verde, this->azul);
	glBegin(GL_LINES);
	glVertex3d(-this->limite1x, -this->limite1y, 0);
	glVertex3d(-this->limite1x, this->limite1y, 0);
	glEnd();
	glEnable(GL_LIGHTING);

	//bordes internos
	glDisable(GL_LIGHTING);
	glColor3ub(0, this->verde, this->azul);
	glBegin(GL_LINES);
	glVertex3d(-this->limite1x+0.25, this->limite1y-0.25, 0);
	glVertex3d(this->limite1x-0.25,this->limite1y-0.25, 0);
	glEnd();
	glEnable(GL_LIGHTING);

	glDisable(GL_LIGHTING);
	glColor3ub(0, this->verde, this->azul);
	glBegin(GL_LINES);
	glVertex3d(this->limite1x - 0.25, this->limite1y-0.25, 0);
	glVertex3d(this->limite1x-0.25 , -this->limite1y+0.25, 0);
	glEnd();
	glEnable(GL_LIGHTING);

	glDisable(GL_LIGHTING);
	glColor3ub(0, this->verde, this->azul);
	glBegin(GL_LINES);
	glVertex3d(this->limite1x-0.25, -this->limite1y+0.25, 0);
	glVertex3d(-this->limite1x+0.25, -this->limite1y+0.25, 0);
	glEnd();
	glEnable(GL_LIGHTING);

	glDisable(GL_LIGHTING);
	glColor3ub(0, this->verde, this->azul);
	glBegin(GL_LINES);
	glVertex3d(-this->limite1x+0.25, -this->limite1y+0.25, 0);
	glVertex3d(-this->limite1x+0.25, this->limite1y-0.25, 0);
	glEnd();
	glEnable(GL_LIGHTING);
	//
	
}
void pantalla::setcolor(unsigned char r, unsigned char v, unsigned char a) {
	this->rojo = r;
	this->verde = v;
	this->azul = a;
}
