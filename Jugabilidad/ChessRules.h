

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

