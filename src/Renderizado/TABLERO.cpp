#define NULL 0
#include "TABLERO.h"
#include "freeglut.h"
#include "FICHA.h"
#include <math.h>

TABLERO::TABLERO(int n = 1) : lado(n), color_fondo(0, 0, 255)
{
	pel = NULL;

	pel = new FICHA * [lado];

	for (int i = 0; i < lado; i++)
	{
		pel[i] = new FICHA[lado];
	}

	cas = NULL;

	cas = new CASILLA * [lado];

	for (int i = 0; i < lado; i++)
	{
		cas[i] = new CASILLA[lado];
	}

	Lim1.x = -10.0f;
	Lim1.y = -10.0f;

	Lim2.x = -10.0f;
	Lim2.y = 10.0f;
	
	Lim3.x = 10.0f;
	Lim3.y = 10.0f;

	Lim4.x = 10.0f;
	Lim4.y = -10.0f;

	var = (Lim3 - Lim1) / lado;
}

TABLERO::~TABLERO()
{
	for (int i = 0; i < lado; i++)
	{
		delete cas[i];
	}

	delete cas;

	cas = NULL;

	for (int i = 0; i < lado; i++)
	{
		delete pel[i];
	}

	delete pel;

	pel = NULL;
}

void TABLERO::inicializa()
{

	for (int i = 0; i < lado; i++)
	{
		for (int j = 0; j < lado; j++)
		{
			cas[i][j].setLims(Lim1, var, i, j);

			pel[i][j].setPos(Lim1.x + (0.5 + j) * var.x, Lim1.y + (0.5 + i) * var.y);
			if (var.x < var.y)
			{
				pel[i][j].setRad(0.75 * var.x / 2);
			}
			else
			{
				pel[i][j].setRad(0.75 * var.y / 2);
			}
			pel[i][j].setPiezaJugador(FICHA::NOPIEZA, FICHA::NOJUGADOR);
		}
	}

	for (int j = 0; j < lado; j++)
	{
		//JUGADOR_1
		pel[0][j].setPiezaJugador(FICHA::TIPO0, FICHA::JUGADOR1);
		pel[1][j].setPiezaJugador(FICHA::TIPO1, FICHA::JUGADOR1);
		pel[2][j].setPiezaJugador(FICHA::TIPO2, FICHA::JUGADOR1);

		//JUGADOR_2
		pel[lado - 1][j].setPiezaJugador(FICHA::TIPO0, FICHA::JUGADOR2);
		pel[lado - 2][j].setPiezaJugador(FICHA::TIPO1, FICHA::JUGADOR2);
		pel[lado - 3][j].setPiezaJugador(FICHA::TIPO2, FICHA::JUGADOR2);
	}
	
}

void TABLERO::dibuja()
{
	//cuadrado FONDO
	glDisable(GL_LIGHTING);
	glBegin(GL_POLYGON);
	glColor3ub(color_fondo.rojo, color_fondo.verde, color_fondo.azul);
	glVertex3f(-100 , -100, -0.1f);
	glVertex3f(-100 , 100, -0.1f);
	glVertex3f(100, 100, -0.1f);
	glVertex3f(100, -100, -0.1f);
	glEnd();
	glEnable(GL_LIGHTING);

	//Cada pieza

	for (int i = 0; i < lado; i++)
	{
		for (int j = 0; j < lado; j++)
		{
			cas[i][j].dibuja();
			
			pel[i][j].dibuja();
		}
	}

}

void TABLERO::modifica()
{
	pel[0][0].setPiezaJugador(FICHA::TIPO1, FICHA::JUGADOR1);
	pel[lado - 1][lado - 1].setPiezaJugador(FICHA::TIPO2, FICHA::JUGADOR2);
	pel[0][lado - 1].setPiezaJugador(FICHA::TIPO2, FICHA::JUGADOR1);
	pel[lado - 1][0].setPiezaJugador(FICHA::TIPO1, FICHA::JUGADOR2);
}

void TABLERO::mueve()
{
}
