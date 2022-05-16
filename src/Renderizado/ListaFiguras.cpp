#include "ListaFiguras.h"
#include "FICHA.h"

//JUGADOR1
static Figura PEONJ1("imagenes/PEON.obj", "imagenes/TexturaPeonBlanco.png", 1.0f, 0, 0, 0);
static Figura TORREJ1("imagenes/TORRE.obj", "imagenes/TexturaTorreBlanco.png", 1.0f, 0, 0, 0);
static Figura ALFILJ1("imagenes/ALFIL.obj", "imagenes/TexturaAlfilBlanco.png", 1.0f, 0, 0, 0);
static Figura CABALLOJ1("imagenes/CABALLO.obj", "imagenes/TexturaCaballoBlanco.png", 1.0f, 0, 0, 0);
static Figura REYJ1("imagenes/REY.obj", "imagenes/TexturaReyBlanco.png", 1.0f, 0, 0, 0);
static Figura REINAJ1("imagenes/REINA.obj", "imagenes/TexturaReinaBlanco.png", 1.0f, 0, 0, 0);
//JUGADOR2
static Figura PEONJ2("imagenes/PEON.obj", "imagenes/TexturaPeonNegro.png", 1.0f, 0, 0, 0);
static Figura TORREJ2("imagenes/TORRE.obj", "imagenes/TexturaTorreNegro.png", 1.0f, 0, 0, 0);
static Figura ALFILJ2("imagenes/ALFIL.obj", "imagenes/TexturaAlfilNegro.png", 1.0f, 0, 0, 0);
static Figura CABALLOJ2("imagenes/CABALLO.obj", "imagenes/TexturaCaballoNegro.png", 1.0f, 0, 0, 0);
static Figura REYJ2("imagenes/REY.obj", "imagenes/TexturaReyNegro.png", 1.0f, 0, 0, 0);
static Figura REINAJ2("imagenes/REINA.obj", "imagenes/TexturaReinaNegro.png", 1.0f, 0, 0, 0);

void ListaFiguras::dibuja(tablero_t& tab, CASILLA casi[][COL_SIZE])
{
	

	for (int i = 0; i < ROW_SIZE; i++)
	{
		for (int j = 0; j < COL_SIZE; j++)
		{
	

			if (tab[i][j].getColor() == BLANCA)
			{
				switch (tab[i][j].getForma())
				{

				case NO_PIEZA:
					break;

				case PEON:
					PEONJ1.setPos(casi[i][j].getCasilla().x, casi[i][j].getCasilla().y, 0.0f);
					PEONJ1.dibuja();
					break;

				case CABALLO:
					CABALLOJ1.setPos(casi[i][j].getCasilla().x, casi[i][j].getCasilla().y, 0.0f);
					CABALLOJ1.dibuja();
					break;

				case ALFIL:
					ALFILJ1.setPos(casi[i][j].getCasilla().x, casi[i][j].getCasilla().y, 0.0f);
					ALFILJ1.dibuja();
					break;
				case TORRE:
					TORREJ1.setPos(casi[i][j].getCasilla().x, casi[i][j].getCasilla().y, 0.0f);
					TORREJ1.dibuja();
					break;
				case DAMA:
					REINAJ1.setPos(casi[i][j].getCasilla().x, casi[i][j].getCasilla().y, 0.0f);
					REINAJ1.dibuja();
					break;
				case REY:
					REYJ1.setPos(casi[i][j].getCasilla().x, casi[i][j].getCasilla().y, 0.0f);
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
					PEONJ2.setPos(casi[i][j].getCasilla().x, casi[i][j].getCasilla().y, 0.0f);
					PEONJ2.dibuja();
					break;

				case CABALLO:
					CABALLOJ2.setPos(casi[i][j].getCasilla().x, casi[i][j].getCasilla().y, 0.0f);
					CABALLOJ2.dibuja();
					break;

				case ALFIL:
					ALFILJ2.setPos(casi[i][j].getCasilla().x, casi[i][j].getCasilla().y, 0.0f);
					ALFILJ2.dibuja();
					break;
				case TORRE:
					TORREJ2.setPos(casi[i][j].getCasilla().x, casi[i][j].getCasilla().y, 0.0f);
					TORREJ2.dibuja();
					break;
				case DAMA:
					REINAJ2.setPos(casi[i][j].getCasilla().x, casi[i][j].getCasilla().y, 0.0f);
					REINAJ2.dibuja();
					break;
				case REY:
					REYJ2.setPos(casi[i][j].getCasilla().x, casi[i][j].getCasilla().y, 0.0f);
					REYJ2.dibuja();
					break;

				}
			}
			else if (tab[i][j].getColor() == FICHA::NOJUGADOR)
			{

			}
			
		}
	}
	

}



