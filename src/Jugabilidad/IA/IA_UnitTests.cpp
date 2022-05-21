#include "IA_UnitTests.h"
#include <iostream>

/// <summary>
/// Comprueba evaluaci�n de tableros de la IA_dificil en la posici�n inicial
/// </summary>
/// <returns>true si la evaluaci�n es correcta</returns>
bool IA_UnitTests::test_1()
{
	tablero_t tab = IA_UnitTests::generarTablero();
	return IA_dificil::getBoardScore(tab, BLANCA) == 0 && IA_dificil::getBoardScore(tab, NEGRA) == 0;
}

/// <summary>
/// Comprueba evaluaci�n de tableros de la IA_dificil con la dama blanca en una posici�n favorable
/// </summary>
/// <returns>true si la evaluaci�n es correcta</returns>
bool IA_UnitTests::test_2()
{
	tablero_t tab = IA_UnitTests::generarTablero();
	tab[7][3] = pieza_t(NO_PIEZA, BLANCA);
	tab[5][3] = pieza_t(DAMA, BLANCA);
	return IA_dificil::getBoardScore(tab, BLANCA) == 10 && IA_dificil::getBoardScore(tab, NEGRA) == -10;
}

/// <summary>
/// Comprueba evaluaci�n de tableros de la IA_dificil cuando a las piezas blancas les falta un pe�n
/// </summary>
/// <returns>true si la evaluaci�n es correcta</returns>
bool IA_UnitTests::test_3()
{
	tablero_t tab = IA_UnitTests::generarTablero();
	tab[6][3] = pieza_t(NO_PIEZA, BLANCA);
	return IA_dificil::getBoardScore(tab, BLANCA) == -80 && IA_dificil::getBoardScore(tab, NEGRA) == +80;
}

bool IA_UnitTests::test_4()
{
	tablero_t tab = IA_UnitTests::generarTablero();
	Juego partida;
	partida.set_tablero(tab);
	//return IA_dificil::contarMovPosibles(partida, BLANCA) == 16 && IA_dificil::contarMovPosibles(partida, NEGRA) == 16;
	return true;
}






/// <summary>
/// Genera un tablero con la posici�n inicial de las piezas
/// </summary>
/// <returns>Tablero con la posici�n inicial de las piezas</returns>
tablero_t IA_UnitTests::generarTablero()
{
	// Reserva de memoria tablero
	tablero_t tab = new pieza_t * [ROW_SIZE];
	for (int i = 0; i < ROW_SIZE; i++) {
		*(tab + i) = new pieza_t[COL_SIZE];
	}


	// Poner en blanco el tablero:
	for (int i = 0; i < ROW_SIZE; i++) {
		pieza_t* aux;
		aux = *(tab + i);
		for (int j = 0; j < COL_SIZE; j++) {
			(aux + j)->setColor(NO_COLOR);
			(aux + j)->setForma(NO_PIEZA);
		}
	}


	// Posicion inicial de la partida (Para una partida normal de momento)

	// Negras
	tab[0][0] = pieza_t(TORRE, NEGRA);
	tab[0][1] = pieza_t(CABALLO, NEGRA);
	tab[0][2] = pieza_t(ALFIL, NEGRA);
	tab[0][3] = pieza_t(DAMA, NEGRA);
	tab[0][4] = pieza_t(REY, NEGRA);
	tab[0][5] = pieza_t(ALFIL, NEGRA);
	tab[0][6] = pieza_t(CABALLO, NEGRA);
	tab[0][7] = pieza_t(TORRE, NEGRA);
	for (int i = 0; i < COL_SIZE; i++) {
		tab[1][i] = pieza_t(PEON, NEGRA);
	}

	// Blancas
	tab[7][0] = pieza_t(TORRE, BLANCA);
	tab[7][1] = pieza_t(CABALLO, BLANCA);
	tab[7][2] = pieza_t(ALFIL, BLANCA);
	tab[7][3] = pieza_t(DAMA, BLANCA);
	tab[7][4] = pieza_t(REY, BLANCA);
	tab[7][5] = pieza_t(ALFIL, BLANCA);
	tab[7][6] = pieza_t(CABALLO, BLANCA);
	tab[7][7] = pieza_t(TORRE, BLANCA);
	for (int i = 0; i < COL_SIZE; i++) {
		tab[6][i] = pieza_t(PEON, BLANCA);
	}
    return tab;
}

/// <summary>
/// Genera un tablero con la posici�n inicial de las piezas
/// </summary>
/// <returns>Tablero con la posici�n inicial de las piezas</returns>
bool IA_UnitTests::test()
{
    bool (*unitTests[3])(void) = { IA_UnitTests::test_1, IA_UnitTests::test_2, IA_UnitTests::test_3 };
    for (int i = 0; i < 3; i++) {
        //bool resultado = unitTests[i];
        if (unitTests[i]() == false) {
            return false;
        }
    }
    return true;
}