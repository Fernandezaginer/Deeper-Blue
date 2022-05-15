

// Test unitario:
/*
	Juego a(RAPIDA);
	cout << a.print();

	while (a.getMinLeftPlaA() == 10);
	a.movimiento(6, 4, 4, 4);
	cout << a.print();

	while (a.getMinLeftPlaB() == 10);
	a.movimiento(1, 4, 3, 4);
	cout << a.print();
*/

#include "chesstime.h"
#include "Pieza.h"

#include <sstream>
using namespace std;

#ifndef _CHESSPULES_H_
#define _CHESSPULES_H_


// Puntero a las piezas de la partida
typedef  pieza_t** tablero_t;



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



class Juego : public chesstime {
public:

	// Constructor y destructor:
	Juego(modo_partida_t mode = RAPIDA);
	Juego(Juego& j);
	~Juego();

	Juego& operator = (Juego J) { return J; }


	// Movimientos de las piezas:
	tablero_info_t mov_permitidos(pieza_t* a, tablero_t tab);
	bool movimiento(int row_o, int col_o, int row_f, int col_f);
	ostream& notacion_ulimo_moviento();
	tablero_t getTablero() { return tab; }
	

	// Servicios
	bool tablas();
	bool tablas_por_repeticiones_de_posicion();
	bool tablas_por_rey_ahogado();
	bool jaque_playerA();
	bool jaque_playerB();
	bool jaque_mate_playerA();   // Blancas en jaque mate
	bool jaque_mate_playerB();   // Negras en jaque mate
	bool playerA_won();			// Blancas ganan por tiempo o por jaque mate
	bool playerB_won();			// Negras ganan por tiempo o por jaque mate

	int score_playerA();
	int score_playerB();

	// Servivios heredados de chestime.h:
	/*
	// Métodos para obtener el tiempo restante de cada jugador
	int getSecLeftPlaA();
	int getSecLeftPlaB();
	int getMinLeftPlaA();
	int getMinLeftPlaB();

	// Métodos para indicar si algún jugador pierde por tiempo
	bool PlaA_end_time();
	bool PlaB_end_time();
	*/

	// Debug:
	string print() { return print(this->tab); }
	string print(tablero_t t);

private:
	tablero_t tab;

	// Movimiento piezas:
	bool analisis_mov;
	tablero_info_t get_mov_permitidos(pieza_t* a, tablero_t tab);
	bool haz_movimiento(int row_o, int col_o, int row_f, int col_f);
	void aux_detectar_jaques_a_la_descubierta(tablero_info_t& matriz, pieza_t** tab, int row, int col);

	// Informacion del enroque
	bool playerA_enroque_permitido;
	bool playerB_enroque_permitido;

	// Historial de las partidas:
	tablero_t* historial;
	//bool jaque_a[NUM_MAX_MOV];
	//bool jaque_b[NUM_MAX_MOV];
	int numero_mov;
	bool anade_movimiento_historial(tablero_t posicion);
	bool tableros_iguales(tablero_t* t1, tablero_t* t2);

	// Jaques, mates y ahogados:
	bool rey_ahogado(color_pieza_t color);
	bool rey_jaque_mate(color_pieza_t color);
	bool jaque_player(color_pieza_t color, tablero_t mat);

	// Notacion del movimietno
	ostringstream mov;
	char row_to_char(int row);
	char col_to_char(int col);

	// Reglas espieciales peón: comer al paso y promoción
 	void aux_detectar_comer_al_paso(tablero_info_t& matriz, pieza_t peon, int row, int col);
	void aux_detectar_promocion(tablero_info_t& matriz, pieza_t peon, int row, int col);

	// Auxiliar:
	void tablero_inicio_normal();
	void tablero_inicio_peones();

	bool jaque_mate();

};



#endif

