

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
	int numero_turnos_sin_comer;

public:

	Juego();
	~Juego();
	
	string print(); // Temporal

	// A futuro:
	/*
	bool haz_movimiento(tablero_t&, int fila, int columna);
	void start();
	
	bool tablas();
	bool jaque_mate();

	int score_playerA();
	int score_playerB();

	tablero_t get_tablero();
	*/
};



#endif

