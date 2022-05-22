#pragma once

#include <cstdlib>
#include <ctime>
#include <vector>

#include "ChessRules.h"
#include "Pieza.h"

struct fruto {
	movimiento mov;
	Juego partida;
	float score;
	vector<fruto> hijos;
};
typedef vector<fruto> arbol;

class IA_base {
protected:
	color_pieza_t color;
public:
	IA_base(color_pieza_t col = NEGRA) : color(col) {}

	virtual bool hacerMovimiento(Juego partida);
};


class IA_facil : public IA_base{
private:
public:
	friend class IA_UnitTests;
	IA_facil(color_pieza_t col = NEGRA) : IA_base(col) {}

	bool hacerMovimiento(Juego& partida);
};

class IA_dificil : public IA_base {
private:
	int _dificultad;
	static movimiento evaluarArbol(arbol tree);
	static float evaluarRama(fruto fruta);
	static arbol getArbol(Juego partida, color_pieza_t player, int depth);
	static void crearRama(fruto& fruta, Juego partida, color_pieza_t player, int depth_left);
	static int getScore(Juego partida, color_pieza_t player);
	static int getBoardScore(tablero_t partida, color_pieza_t player);
public:
	friend class IA_UnitTests;
	IA_dificil(color_pieza_t col = NEGRA, int dificultad = 4) : IA_base(col), _dificultad(dificultad) {}

	//M�todos
	bool hacerMovimiento(Juego& partida);

	//Look up tables
	const static int individualsTable[7][ROW_SIZE][COL_SIZE];
	const static int valorPiezas[7];
};
