

// Test unitario:
/*
Juego a;
cout << a.print();
*/

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



class Juego {
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


public:

	// Constructor y destructor:
	Juego();
	~Juego();
	
	string print(); // Temporal

	// Movimientos de las piezas:
	tablero_info_t get_mov_permitidos(pieza_t* a, pieza_t** tab);
	bool haz_movimiento(int row_o, int col_o, int row_f, int col_f);

	// Servicios
	bool tablas_por_repeticiones_de_posicion();
	bool jaque_mate_playerA();
	bool jaque_mate_playerB();

	/*
	void start();
	
	bool tablas();
	bool jaque_mate();

	int score_playerA();
	int score_playerB();

	tablero_t get_tablero();
	*/

};



#endif

