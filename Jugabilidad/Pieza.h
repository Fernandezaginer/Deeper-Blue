

#ifndef _PIEZA_H_
#define _PIEZA_H_

#define ROW_SIZE 8
#define COL_SIZE 8
#define NULL 0


// Información de la pieza
enum forma_pieza_t { NO_PIEZA, PEON, CABALLO, ALFIL, TORRE, DAMA, REY };
enum color_pieza_t { NO_COLOR, BLANCA, NEGRA };
enum movimiento_t { PROPIA_PIEZA = -1, NO_PERMITIDO, PERMITIDO, COMER_PIEZA };

// Extructura que indica los movimientos permitidos
typedef struct {
	movimiento_t TAB[ROW_SIZE][COL_SIZE];
}tablero_info_t;



class pieza_t {
	forma_pieza_t forma;
	color_pieza_t color;
public:

	pieza_t() : forma(NO_PIEZA), color(NO_COLOR) {};
	pieza_t(forma_pieza_t forma, color_pieza_t color) : forma(forma), color(color) {};

	forma_pieza_t getForma() { return forma; };
	color_pieza_t getColor() { return color; };
	void setForma(forma_pieza_t a) { forma = a; };
	void setColor(color_pieza_t a) { color = a; };

	tablero_info_t get_mov_permitidos(pieza_t a, pieza_t** tab);
};





#endif


