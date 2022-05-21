#include "CASILLA.h"
#include "freeglut.h"

void CASILLA::setLims(VECTOR posInicial, VECTOR variacion, int fila, int columna)
{
	Lim1.x = posInicial.x + columna * variacion.x;
	Lim1.y = posInicial.y + fila * variacion.y;

	Lim2.x = posInicial.x + columna * variacion.x;
	Lim2.y = posInicial.y + (fila + 1) * variacion.y;

	Lim3.x = posInicial.x + (columna + 1) * variacion.x;
	Lim3.y = posInicial.y + (fila + 1) * variacion.y;

	Lim4.x = Lim3.x = posInicial.x + (columna + 1) * variacion.x;
	Lim4.y = Lim1.y = posInicial.y + fila * variacion.y;

	if (fila % 2 != columna % 2)
	{
		col.setColor(255, 255, 255);
	}
	else
	{
		col.setColor(0, 0, 0);
	}
}

void CASILLA::dibuja()
{
	glDisable(GL_LIGHTING);
	glBegin(GL_POLYGON);
	glColor3ub(col.rojo, col.verde, col.azul);
	glVertex3f(Lim1.x, Lim1.y, 0);
	glVertex3f(Lim2.x, Lim2.y, 0);
	glVertex3f(Lim3.x, Lim3.y, 0);
	glVertex3f(Lim4.x, Lim4.y, 0);
	glEnd();
	glEnable(GL_LIGHTING);
}

void CASILLA::resetColor(int i, int j)
{
	if (i % 2 != j % 2)
	{
		col.setColor(255, 255, 255);
	}
	else
	{
		col.setColor(0, 0, 0);
	}
}

void CASILLA::setColor(COLOR c)
{
	col = c;
}

VECTOR CASILLA::getCasilla()
{
	VECTOR c;
	c.x = (Lim1.x + Lim2.x + Lim3.x + Lim4.x) / 4;
	c.y = (Lim1.y + Lim2.y + Lim3.y + Lim4.y) / 4;
	return c;
}
