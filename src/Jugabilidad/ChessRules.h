// Test unitario:
/*
Juego a;
cout << a.print();
*/

#include "Pieza.h"
#include <sstream>
#include <vector>
using namespace std;

#ifndef _CHESSPULES_H_
#define _CHESSPULES_H_


// Puntero a las piezas de la partida
typedef  pieza_t** tablero_t;

enum casillas_t { a1 = 0, b1, c1, d1, e1, f1, g1, h1, a2, b2, c2, d2, e2, f2, g2, h2, a3, b3, c3, d3, e3, f3, g3, h3, a4, b4, c4, d4, e4, f4, g4, h4, a5, b5, c5, d5, e5, f5, g5, h5, a6, b6, c6, d6, e6, f6, g6, h6, a7, b7, c7, d7, e7, f7, g7, h7, a8, b8, c8, d8, e8, f8, g8, h8};
struct movimiento {
	movimiento_t mov;
	int row_o;
	int col_o;
	int row_f;
	int col_f;
};

typedef vector<movimiento> lista_movimientos;


// CRITERIO DEL TABLERO:

/*
T C A D R A C T  // Piezas negras
P P P P P P P P
- - - - - - - -
- - - - - - - -
- - - - - - - -
P P P P P P P P
T C A D R A C T  // Piezas blancas
*/

// Primera dimensión = Filas
// Segunda dimensión = Columnas
// EJ: El rey blanco está en [7][4]



class Juego {


public:
	friend class IA_dificil;
	// Constructor y destructor:
	Juego();
	~Juego();

	string print(); // Temporal

	// Movimientos de las piezas:
	tablero_info_t get_mov_permitidos(pieza_t* a, tablero_t tab);
	lista_movimientos get_mov_permitidos_l(tablero_t tab, int row_o, int col_o);
	bool haz_movimiento(int row_o, int col_o, int row_f, int col_f);
	ostream& notacion_ulimo_moviento();

	// Servicios
	bool tablas();
	bool jaque_mate();
	bool tablas_por_repeticiones_de_posicion();
	bool tablas_por_rey_ahogado();
	bool jaque_playerA();
	bool jaque_playerB();
	bool jaque_mate_playerA();
	bool jaque_mate_playerB();

	int score_playerA();
	int score_playerB();

	tablero_t get_tablero() { return this->tab; }
	void set_tablero(tablero_t tablero) { this->tab = tablero; }
private:
	tablero_t tab;

	// Informacion del enrroque
	bool playerA_enroque_permitido;
	bool playerB_enroque_permitido;

	// Tablas por repeticion de movimiento:
	tablero_t* historial;
	int numero_mov;
	bool anade_movimiento_historial(tablero_t posicion);
	bool tableros_iguales(tablero_t* t1, tablero_t* t2);

	// Tablas por rey ahogado
	bool tablas_por_rey_ahogado(color_pieza_t color);
	bool jaque_player(color_pieza_t color, tablero_t mat);
	bool jaque_mate_player(color_pieza_t color, tablero_t mat);

	// Auxiliar movimiento:
	void aux_detectar_jaques_a_la_descubierta(tablero_info_t& matriz, pieza_t** tab, int row, int col);
	bool analisis_mov;

	// Notacion del movimietno
	ostringstream mov;
	char row_to_char(int row);
	char col_to_char(int col);

	// Temporal:
	void tablero_inicio_normal();

};




#endif