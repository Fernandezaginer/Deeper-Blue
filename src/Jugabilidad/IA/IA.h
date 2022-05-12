#include <cstdlib>
#include <ctime>

#include "ChessRules.h"
#include "Pieza.h"

class IA_facil {
private:
	Juego partida;
	color_pieza_t color;
public:
	bool hacerMovimiento();
};

class IA_dificil {
private:
	Juego partida;
	color_pieza_t color;
public:
	bool hacerMovimiento();

	const static int pawntable[ROW_SIZE][COL_SIZE];
	const static int knightstable[ROW_SIZE][COL_SIZE];
	const static int bishopstable[ROW_SIZE][COL_SIZE];
	const static int rookstable[ROW_SIZE][COL_SIZE];
	const static int queenstable[ROW_SIZE][COL_SIZE];
	const static int kingstable[ROW_SIZE][COL_SIZE];
};