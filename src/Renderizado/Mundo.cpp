#include "Mundo.h"
#include "freeglut.h"
#include <math.h>
#include <iostream>
#include <Windows.h>
#include "ETSIDI.h"
#include <thread>
#include <chrono>


void Mundo::rotarOjo()
{
	float dist=sqrt(x_ojo*x_ojo+z_ojo*z_ojo);
	float ang=atan2(z_ojo,x_ojo);
	ang+=0.05f;
	x_ojo=dist*cos(ang);
	z_ojo=dist*sin(ang);
}
void Mundo::dibuja()
{
	gluLookAt(x_ojo, y_ojo, z_ojo,  // posicion del ojo
			0.0, 0, 0.0,      // hacia que punto mira  (0,0,0) 
			0.0, 1.0, 0.0);      // definimos hacia arriba (eje Y)    

	//aqui es donde hay que poner el codigo de dibujo
	//dibujo del suelo

	t.dibuja(j.getTablero());
		
	/////////////////////////////////////////////
	//BLANCAS

	glPushMatrix();
	glTranslatef(-12.0, 8.0, 5.0);
	glColor3ub(255, 255, 255);
	glScalef(0.004f, 0.004f, 1);
	const char str[] = "Blancas";
	for (int i = 0; i < strlen(str); i++) {
		glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, str[i]);
	}
	glPopMatrix();
	

	glPushMatrix();
	//TIEMPO BLANCAS
	glTranslatef(-12.0, 7.0, 5.0);
	glColor3ub(255, 255, 255);
	glScalef(0.004f, 0.004f, 1);
	char str2[3];
	sprintf(str2, "%d", j.getMinLeftPlaA());
	for (int i = 0; i < strlen(str2); i++) {
		glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, str2[i]); //Minutos
	}

	glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, ':'); //Separacion

	char str3[3];
	if (j.getSecLeftPlaA() < 10) {
		str3[0] = '0';
		str3[1] = '0' + j.getSecLeftPlaA();
		str3[2] = '\0';
	}
	else {
		sprintf(str3, "%d", j.getSecLeftPlaA());
	}
	for (int i = 0; i < strlen(str3); i++) {
		glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, str3[i]); //Segundos
	}

	glPopMatrix();

	//////////////////////////////////////////
	//NEGRAS

	glPushMatrix();
	glTranslatef(9.0, -7.0, 5.0);
	glColor3ub(255, 255, 255);
	glScalef(0.004f, 0.004f, 1);
	const char str4[] = "Negras";
	for (int i = 0; i < strlen(str4); i++) {
		glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, str4[i]);
	}
	glPopMatrix();


	glPushMatrix();
	//TIEMPO NEGRAS
	glTranslatef(9.0, -8.0, 5.0);
	glColor3ub(255, 255, 255);
	glScalef(0.004f, 0.004f, 1);
	char str5[3];
	sprintf(str5, "%d", j.getMinLeftPlaB());
	for (int i = 0; i < strlen(str5); i++) {
		glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, str5[i]); //Minutos
	}

	glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, ':'); //Separacion

	char str6[3];
	if (j.getSecLeftPlaB() < 10) {
		str6[0] = '0';
		str6[1] = '0' + j.getSecLeftPlaB();
		str6[2] = '\0';
	}
	else {
		sprintf(str6, "%d", j.getSecLeftPlaB());
	}
	for (int i = 0; i < strlen(str6); i++) {
		glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, str6[i]); //Segundos
	}

	glPopMatrix();
}


void Mundo::mueve()
{
	t.mueve();
	static int origen_f, origen_c, final_f, final_c;
	
	//t.resetColor();

	this->con.coger_pos();
	//std::cout << "(" << this->con.mousePos.x << ", " << this->con.mousePos.y << ")" << endl;

	int c = ROW_SIZE * trunc((float)this->con.mousePos.x - 535.0f) / (1063.0f - 535.0f);
	int f = COL_SIZE - COL_SIZE * trunc((float)this->con.mousePos.y - 151.0f) / (631.0f - 151.0f);

	//std::cout << controles::fp_estado << std::endl;

	if (controles::boton == GLUT_LEFT_BUTTON && controles::read_fp() == true)
	{
		if (f < ROW_SIZE && f >= 0 && c < COL_SIZE && c >= 0)
		{
			j.movimiento(origen_f, origen_c, f, c);

			pieza_t* selec = &j.getTablero()[f][c];
			t.pintMovPermitidos(j.mov_permitidos(selec, j.getTablero()));
			origen_f = f;
			origen_c = c;
		}
	}
	if (this->isVsIA && this->j.getIsTurnPlayerB()) {
		IA.hacerMovimiento(this->j);
	}
}

void Mundo::inicializa()
{
	x_ojo=0;
	y_ojo=0;
	z_ojo=20;

	t.inicializa();

	this->isVsIA = false;
}

void Mundo::tecla(unsigned char key)
{
}

void Mundo::raton(int b, int e, int x, int y) //Boton-estado-posicionx-posiciony
{
	
}