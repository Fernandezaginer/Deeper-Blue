

#ifndef _CHESSRULES_H_
#define _CHESSRULES_H_

#define ROW_SIZE 8
#define COL_SIZE 8


enum forma_pieza_t { PEON, CABALLO, ALFIL, TORRE, DAMA, REY };
enum color_pieza_t { BLANCA, NEGRA };
enum movimiento_t { PROPIA_PIEZA, NO_PERMITIDO, PERMITIDO, COMER_PIEZA };


struct tablero_t {
	pieza_t** TAB[ROW_SIZE][COL_SIZE];
};

struct tablero_info_t {
	movimiento_t TAB[ROW_SIZE][COL_SIZE];
};


class Juego {
	tablero_t tab;
	int numero_veces_sin_comer;


public:

	bool haz_movimiento(tablero_t&, int fila, int columna);
	void start();
	
	bool tablas();
	bool jaque_mate();


	int score_playerA();
	int score_playerB();

	tablero_t get_tablero();

};


class pieza_t {
	forma_pieza_t forma;
	color_pieza_t color;

public:
	tablero_info_t get_mov_permitidos(pieza_t, tablero_t);
};






#endif

