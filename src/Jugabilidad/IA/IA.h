#pragma once

#include <cstdlib>
#include <ctime>

#include "ChessRules.h"
#include "Pieza.h"

class IA_base {
protected:
	color_pieza_t color;
public:
	IA_base(color_pieza_t col = NEGRA) : color(col) {}

	virtual bool hacerMovimiento(Juego partida);
};


class IA_facil : public IA_base{
private:
	//Juego partida;
	//color_pieza_t color;
public:
	friend class IA_UnitTests;
	IA_facil(color_pieza_t col = NEGRA) : IA_base(col) {}

	bool hacerMovimiento(Juego partida);
};

class IA_dificil : public IA_base {
private:
	//Juego partida;
	//color_pieza_t color;

	static int getScore(Juego partida, color_pieza_t player);
	static int getBoardScore(tablero_t partida, color_pieza_t player);
public:
	friend class IA_UnitTests;
	IA_dificil(color_pieza_t col = NEGRA) : IA_base(col) {}

	//Métodos
	bool hacerMovimiento(Juego partida);

	//Look up tables
	const static int individualsTable[7][ROW_SIZE][COL_SIZE];
	const static int valorPiezas[7];
};