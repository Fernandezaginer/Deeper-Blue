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
#include "Mundo.h"

using namespace std;
Interfaz interfaz;


void OnDraw(void); //esta funcion sera llamada para dibujar
void OnTimer(int value); //esta funcion sera llamada cuando transcurra una temporizacion
void OnKeyboardDown(unsigned char key, int x, int y); //cuando se pulse una tecla	
void click(int button, int state, int x, int y);

int main(int argc,char* argv[])
{
	//Inicializar el gestor de ventanas GLUT
	//y crear la ventana
	glutInit(&argc, argv);
	glutInitWindowSize(1920,1080);
	

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("DEEPERBLUE");

	glutFullScreen();

	//habilitar luces y definir perspectiva
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);	
	glMatrixMode(GL_PROJECTION);
	gluPerspective( 40.0, 2000/1200.0f, 0.1, 150);

	//Registrar los callbacks
	glutDisplayFunc(OnDraw);
	glutTimerFunc(25,OnTimer,0);//le decimos que dentro de 25ms llame 1 vez a la funcion OnTimer()
	glutKeyboardFunc(OnKeyboardDown);
	glutMouseFunc(click);
	
	ETSIDI::playMusica("mimusica/GENSHIN.mp3", true);
	interfaz.inicializa();
	//pasarle el control a GLUT,que llamara a los callbacks
	glutMainLoop();	

	return 0;   
}

void OnDraw(void)
{
	//Borrado de la pantalla	
   	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Para definir el punto de vista
	glMatrixMode(GL_MODELVIEW);	
	glLoadIdentity();
	interfaz.dibuja();

	
	//no borrar esta linea ni poner nada despues
	glutSwapBuffers();
}
void OnKeyboardDown(unsigned char key, int x_t, int y_t)
{
	//poner aqui el código de teclado
	interfaz.tecla(key);

	glutPostRedisplay();
}

void OnTimer(int value)
{
//poner aqui el código de animacion
	interfaz.mueve();

	//no borrar estas lineas
	glutTimerFunc(25,OnTimer,0);
	glutPostRedisplay();
}

void click(int button, int state, int x, int y) {
	if (state != controles::estado) {
		if (state == GLUT_UP) {
			controles::fp_estado = true;
		}
		if (state == GLUT_DOWN) {
			controles::fn_estado = true;
		}
	}
	else {
		controles::fp_estado = false;
		controles::fn_estado = false;
	}

	controles::boton = button;
	controles::estado = state;

}