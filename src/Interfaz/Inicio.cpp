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

inicio::inicio () {
	this->direct = string();
	this->coor_y = -4.5f;
	this->coor_yr = 8.25f ;
}
void inicio::draw() {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture (this->direct.c_str()).id);
	glDisable(GL_LIGHTING);
	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1);
	glTexCoord2d(1, 1); glVertex3f(17.25, -9.75, 0);
	glTexCoord2d(1, 0); glVertex3f(17.25, 9.75, 0);
	glTexCoord2d(0, 0); glVertex3f(-17.25, 9.75, 0);
	glTexCoord2d(0, 1); glVertex3f(-17.25, -9.75, 0);
	glEnd();
	glEnable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
}
void inicio::carga() {
	if (this->coor_y < 8.25) {
		glBegin(GL_POLYGON);
		glColor3f(0, 0, 0);
		glTexCoord2d(1, 1); glVertex3f(4, this->coor_y, 0);
		glTexCoord2d(1, 0); glVertex3f(4, 8.25, 0);
		glTexCoord2d(0, 0); glVertex3f(-4, 8.25, 0);
		glTexCoord2d(0, 1); glVertex3f(-4, this->coor_y, 0);
		glEnd();
		this->coor_y = this->coor_y + 0.05;
	}
}
