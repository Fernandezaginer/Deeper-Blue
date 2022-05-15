#include "FICHA.h"
#include "freeglut.h"
#include "ListaFiguras.h"

void FICHA::setPos(float x, float y)
{
	posicion.x = x;
	posicion.y = y;
}

void FICHA::setRad(float r)
{
	radio = r;
}

void FICHA::dibuja()
{
	glColor3ub(col.rojo, col.verde, col.azul);
	glTranslatef(posicion.x, posicion.y, 0);
	ListaFiguras::dibuja(pieza, jugador);
	glTranslatef(-posicion.x, -posicion.y, 0);
}

void FICHA::setPiezaJugador(int p = NOPIEZA, int ju = NOJUGADOR)
{
	
	pieza = p;
	jugador = ju;

	switch (jugador)
	{

	case NOJUGADOR:
		col.setColor(255, 255, 255);
		break;

	case JUGADOR1:
		col.setColor(255, 0, 0); //ROJO
		break;

	case JUGADOR2:
		col.setColor(0, 0, 255); //AZUL
		break;

	}

}
