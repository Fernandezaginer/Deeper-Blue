
#include <sstream>
using namespace std;

#ifndef _PIEZA_H_
#define _PIEZA_H_

#define NULL 0
#define ROW_SIZE 8
#define COL_SIZE 8
#define NUM_MAX_MOV 300
#define NUM_POS_TABLAS 3


// Información de la pieza
enum forma_pieza_t { NO_PIEZA, PEON, CABALLO, ALFIL, TORRE, DAMA, REY };
enum color_pieza_t { NO_COLOR, BLANCA, NEGRA };
enum movimiento_t { PROPIA_PIEZA = -1, NO_PERMITIDO, PERMITIDO, COMER_PIEZA, ENROQUE_C, ENROQUE_L, PROMOCION, COMER_AL_PASO_L, COMER_AL_PASO_R};

// Extructura que indica los movimientos permitidos
typedef struct {
	movimiento_t TAB[ROW_SIZE][COL_SIZE];
}tablero_info_t;
string mov_print(tablero_info_t t); // Pruebas



class pieza_t {
private:

	// Atributos
	forma_pieza_t forma;
	color_pieza_t color;

	// Métodos auxiliares:
	bool aux_detectar_comer_y_propias_piezas(tablero_info_t& matriz, int i, int j, pieza_t casilla);
	void aux_permite_mov_vert_hor(tablero_info_t& matriz, pieza_t** tab, int row, int col);
	void aux_permite_mov_diag(tablero_info_t& matriz, pieza_t** tab, int row, int col);


public:

	// Constructores:
	pieza_t() : forma(NO_PIEZA), color(NO_COLOR) {};
	pieza_t(forma_pieza_t forma, color_pieza_t color) : forma(forma), color(color) {};

	// Setters y getters:
	forma_pieza_t getForma() { return forma; };
	color_pieza_t getColor() { return color; };
	void setForma(forma_pieza_t a) { forma = a; };
	void setColor(color_pieza_t a) { color = a; };

	// Servicios:
	friend bool operator == (pieza_t lhs, pieza_t rhs);
	char pieza_to_char();
	int valor();

	friend class Juego;

};



#endif


