#include "ListaFiguras.h"
#include "FICHA.h"

//JUGADOR1
static Figura PEONJ1{ "imagenes/PEON.obj", "imagenes/TexturaPeonNegro.png" };
static Figura TORREJ1{ "imagenes/TORRE.obj", "imagenes/TexturaTorreNegro.png" };
static Figura ALFILJ1{ "imagenes/ALFIL.obj", "imagenes/TexturaAlfilNegro.png" };
static Figura CABALLOJ1{ "imagenes/CABALLO.obj", "imagenes/TexturaCaballoNegro.png" };
static Figura REYJ1{ "imagenes/REY.obj", "imagenes/TexturaReyNegro.png" };
static Figura REINAJ1{ "imagenes/REINA.obj", "imagenes/TexturaReinaNegro.png" };
//JUGADOR2
static Figura PEONJ2{ "imagenes/PEON.obj", "imagenes/TexturaPeonBlanco.png" };
static Figura TORREJ2{ "imagenes/TORRE.obj", "imagenes/TexturaTorreBlanco.png" };
static Figura ALFILJ2{ "imagenes/ALFIL.obj", "imagenes/TexturaAlfilBlanco.png" };
static Figura CABALLOJ2{ "imagenes/CABALLO.obj", "imagenes/TexturaCaballoBlanco.png" };
static Figura REYJ2{ "imagenes/REY.obj", "imagenes/TexturaReyBlanco.png" };
static Figura REINAJ2{ "imagenes/REINA.obj", "imagenes/TexturaReinaBlanco.png" };


void ListaFiguras::dibuja(tablero_t& tab, CASILLA casi[][COL_SIZE])
{
	
	for (int i = 0; i < ROW_SIZE; i++)
	{
		for (int j = 0; j < COL_SIZE; j++)
		{
			glTranslatef(casi[i][j].getCasilla().x, casi[i][j].getCasilla().y, 0.0f);
			glRotatef(90, 1, 0, 0);
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
			glRotatef(-90, 1, 0, 0);
			glTranslatef(-casi[i][j].getCasilla().x, -casi[i][j].getCasilla().y, 0.0f);
			
		}
	}
	

}



