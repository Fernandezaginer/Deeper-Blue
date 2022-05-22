#include "ListaFiguras.h"

//JUGADOR1
Figura ListaFiguras::PEONJ1("modelos/PEON.obj", "modelos/TexturaPeonBlanco.png", 1.0f, 0, 0, 0);
Figura ListaFiguras::TORREJ1("modelos/TORRE.obj", "modelos/TexturaTorreBlanco.png", 1.0f, 0, 0, 0);
Figura ListaFiguras::ALFILJ1("modelos/ALFIL.obj", "modelos/TexturaAlfilBlanco.png", 1.0f, 0, 0, 0);
Figura ListaFiguras::CABALLOJ1("modelos/CABALLO.obj", "modelos/TexturaCaballoBlanco.png", 1.0f, 0, 0, 0);
Figura ListaFiguras::REYJ1("modelos/REY.obj", "modelos/TexturaReyBlanco.png", 1.0f, 0, 0, 0);
Figura ListaFiguras::REINAJ1("modelos/REINA.obj", "modelos/TexturaReinaBlanco.png", 1.0f, 0, 0, 0);
//JUGADOR2
Figura ListaFiguras::PEONJ2("modelos/PEON.obj", "modelos/TexturaPeonNegro.png", 1.0f, 0, 0, 0);
Figura ListaFiguras::TORREJ2("modelos/TORRE.obj", "modelos/TexturaTorreNegro.png", 1.0f, 0, 0, 0);
Figura ListaFiguras::ALFILJ2("modelos/ALFIL.obj", "modelos/TexturaAlfilNegro.png", 1.0f, 0, 0, 0);
Figura ListaFiguras::CABALLOJ2("modelos/CABALLO.obj", "modelos/TexturaCaballoNegro.png", 1.0f, 0, 0, 0);
Figura ListaFiguras::REYJ2("modelos/REY.obj", "modelos/TexturaReyNegro.png", 1.0f, 0, 0, 0);
Figura ListaFiguras::REINAJ2("modelos/REINA.obj", "modelos/TexturaReinaNegro.png", 1.0f, 0, 0, 0);

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
			else if (tab[i][j].getColor() == NO_COLOR)
			{

			}
			
		}
	}
}



