#define NULL 0
#include "TABLERO.h"
#include "freeglut.h"
#include "FICHA.h"
#include <math.h>
#include "ListaFiguras.h"

TABLERO::TABLERO() : color_fondo(0, 0, 255)
{

	cas = NULL;

	cas = new CASILLA * [ROW_SIZE];

	for (int i = 0; i < ROW_SIZE; i++)
	{
		cas[i] = new CASILLA[COL_SIZE];
	}

	Lim1.x = -10.0f;
	Lim1.y = -10.0f;

	Lim2.x = -10.0f;
	Lim2.y = 10.0f;
	
	Lim3.x = 10.0f;
	Lim3.y = 10.0f;

	Lim4.x = 10.0f;
	Lim4.y = -10.0f;

	var = (Lim3 - Lim1) / ROW_SIZE;
}

TABLERO::~TABLERO()
{
	for (int i = 0; i < ROW_SIZE; i++)
	{
		delete cas[i];
	}

	delete cas;

	cas = NULL;

	
}

void TABLERO::inicializa()
{

	for (int i = 0; i < ROW_SIZE; i++)
	{
		for (int j = 0; j < COL_SIZE; j++)
		{
			cas[i][j].setLims(Lim1, var, i, j);
		}

	}
	
}

void TABLERO::dibuja(tablero_t tab)
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

	ListaFiguras::dibuja(tab, cas);

	//Cada Casilla

	for (int i = 0; i < ROW_SIZE; i++)
	{
		for (int j = 0; j < COL_SIZE; j++)
		{
			cas[i][j].dibuja();
			
			
		}
	}

}

void TABLERO::modifica()
{
	
}

void TABLERO::mueve()
{
}

void TABLERO::pintMovPermitidos(tablero_info_t ti)
{
	COLOR PP(128, 0, 128); //Propia pieza
	COLOR NP(255, 0, 0); //No permitido
	COLOR PE(0, 255, 0); //Permitido
	COLOR CP(0, 0, 255); //Comer pieza
	COLOR EC(255, 255, 0); //Enroque C
	COLOR EL(255, 0, 255); //ENROQUE L
	COLOR PR(0, 255, 255); //PROMOCION
	COLOR CL(128, 128, 0); //Comer al paso L
	COLOR CR(0, 128, 128); //Comer al paso R

	for (int i = 0; i < ROW_SIZE; i++)
	{
		for (int j = 0; j < COL_SIZE; j++)
		{
			switch (ti.TAB[i][j])
			{
			case PROPIA_PIEZA:
				cas[i][j].setColor(PP);
				break;
			case NO_PERMITIDO:
				cas[i][j].setColor(NP);
				break;
			case PERMITIDO:
				cas[i][j].setColor(PE);
				break;
			case COMER_PIEZA:
				cas[i][j].setColor(CP);
				break;
			case ENROQUE_C:
				cas[i][j].setColor(EC);
				break;
			case ENROQUE_L:
				cas[i][j].setColor(EL);
				break;
			case PROMOCION:
				cas[i][j].setColor(PR);
				break;
			case COMER_AL_PASO_L:
				cas[i][j].setColor(CL);
				break;
			case COMER_AL_PASO_R:
				cas[i][j].setColor(CR);
				break;
			default:
				cas[i][j].resetColor(i, j);

			}
		}

	}
}

void TABLERO::resetColor()
{
	for (int i = 0; i < ROW_SIZE; i++)
		for (int j = 0; j < ROW_SIZE; j++)
			cas[i][j].resetColor(i, j);
}

pieza_t* TABLERO::seleccionarPiezaRaton(int b, int e, int x, int y)
{
	return nullptr;
}


