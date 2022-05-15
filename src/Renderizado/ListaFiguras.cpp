#include "ListaFiguras.h"
#include "FICHA.h"

static Figura T0J1{ "imagenes/caballo.obj", "imagenes/TexturaCaballo.png" }; //TIPO0 JUGADOR1
static Figura T1J1{ "imagenes/caballo.obj", "imagenes/TexturaCaballo.png" }; //TIPO1 JUGADOR1
static Figura T2J1{ "imagenes/caballo.obj", "imagenes/TexturaCaballo.png" }; //TIPO2 JUGADOR1
static Figura T0J2{ "imagenes/caballo.obj", "imagenes/TexturaCaballo.png" }; //TIPO0 JUGADOR2
static Figura T1J2{ "imagenes/caballo.obj", "imagenes/TexturaCaballo.png" }; //TIPO1 JUGADOR2
static Figura T2J2{ "imagenes/caballo.obj", "imagenes/TexturaCaballo.png" }; //TIPO2 JUGADOR2

void ListaFiguras::print(int pieza, int jugador)
{
	

	if (jugador == FICHA::JUGADOR1)
	{
		switch (pieza)
		{

		case FICHA::NOPIEZA:
			break;

		case FICHA::TIPO0:
			T0J1.dibuja();
			break;

		case FICHA::TIPO1:
			T1J1.dibuja();
			break;

		case FICHA::TIPO2:
			T2J1.dibuja();
			break;

		}
	}
	else if (jugador == FICHA::JUGADOR2)
	{
		switch (pieza)
		{

		case FICHA::NOPIEZA:
			break;

		case FICHA::TIPO0:
			T0J2.dibuja();
			break;

		case FICHA::TIPO1:
			T1J2.dibuja();
			break;

		case FICHA::TIPO2:
			T2J2.dibuja();
			break;

		}
	}
	else if (jugador == FICHA::NOJUGADOR)
	{

	}
	
}

