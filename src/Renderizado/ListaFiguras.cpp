#include "ListaFiguras.h"
#include "FICHA.h"

static Figura PEONJ1{ "imagenes/PEONJ1.obj", "imagenes/TexturaCaballo.png" };
static Figura TORREJ1{ "imagenes/TORREJ1.obj", "imagenes/TexturaCaballo.png" };
static Figura ALFILJ1{ "imagenes/ALFILJ1.obj", "imagenes/TexturaCaballo.png" };
static Figura CABALLOJ1{ "imagenes/CABALLOJ1.obj", "imagenes/TexturaCaballo.png" };
static Figura REYJ1{ "imagenes/REYJ1.obj", "imagenes/TexturaCaballo.png" };
static Figura REINAJ1{ "imagenes/REINAJ1.obj", "imagenes/TexturaCaballo.png" };
static Figura PEONJ2{ "imagenes/PEONJ2.obj", "imagenes/TexturaCaballo.png" };
static Figura TORREJ2{ "imagenes/TORREJ2.obj", "imagenes/TexturaCaballo.png" };
static Figura ALFILJ2{ "imagenes/ALFILJ2.obj", "imagenes/TexturaCaballo.png" };
static Figura CABALLOJ2{ "imagenes/CABALLOJ2.obj", "imagenes/TexturaCaballo.png" };
static Figura REYJ2{ "imagenes/REYJ2.obj", "imagenes/TexturaCaballo.png" };
static Figura REINAJ2{ "imagenes/REINAJ2.obj", "imagenes/TexturaCaballo.png" };


void ListaFiguras::dibuja(tablero_t& tab, CASILLA** casi)
{
	
	for (int i = 0; i < ROW_SIZE; i++)
	{
		for (int j = 0; j < COL_SIZE; j++)
		{
			glTranslatef(casi[i][j].getCasilla().x, casi[i][j].getCasilla().y, 0.0f);
			if (tab[i][j].getColor() == BLANCA)
			{
				switch (tab[i][j].getForma())
				{

				case NO_PIEZA:
					break;

				case PEON:
					PEONJ1.dibuja();
					break;

				case CABALLO:
					CABALLOJ1.dibuja();
					break;

				case ALFIL:
					ALFILJ1.dibuja();
					break;
				case TORRE:
					TORREJ1.dibuja();
					break;
				case DAMA:
					REINAJ1.dibuja();
					break;
				case REY:
					REYJ1.dibuja();
					break;

				}
			}
			else if (tab[i][j].getColor() == NEGRA)
			{
				switch (tab[i][j].getForma())
				{

				case NO_PIEZA:
					break;

				case PEON:
					PEONJ2.dibuja();
					break;

				case CABALLO:
					CABALLOJ2.dibuja();
					break;

				case ALFIL:
					ALFILJ2.dibuja();
					break;
				case TORRE:
					TORREJ2.dibuja();
					break;
				case DAMA:
					REINAJ2.dibuja();
					break;
				case REY:
					REYJ2.dibuja();
					break;

				}
			}
			else if (tab[i][j].getColor() == FICHA::NOJUGADOR)
			{

			}
			glTranslatef(-casi[i][j].getCasilla().x, -casi[i][j].getCasilla().y, 0.0f);
		}
	}
	

}



