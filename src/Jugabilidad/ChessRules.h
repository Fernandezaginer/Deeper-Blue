
#include "chesstime.h"
#include "Pieza.h"

#include <vector>


#include <sstream>
using namespace std;

#ifndef _CHESSPULES_H_
#define _CHESSPULES_H_


// Puntero a las piezas de la partida
typedef  pieza_t** tablero_t;


// Estructuras IA
enum casillas_t { a1 = 0, b1, c1, d1, e1, f1, g1, h1, a2, b2, c2, d2, e2, f2, g2, h2, a3, b3, c3, d3, e3, f3, g3, h3, a4, b4, c4, d4, e4, f4, g4, h4, a5, b5, c5, d5, e5, f5, g5, h5, a6, b6, c6, d6, e6, f6, g6, h6, a7, b7, c7, d7, e7, f7, g7, h7, a8, b8, c8, d8, e8, f8, g8, h8 };
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




class Juego : public chesstime
{

public:

	// Constructor y destructor:
	Juego(modo_partida_t mode = RAPIDA);

	Juego(const Juego& j);

	~Juego();

	Juego& operator = (Juego J) { return J; }


	// Movimientos de las piezas:
	tablero_info_t mov_permitidos(pieza_t* a, tablero_t tab);
	bool movimiento(int row_o, int col_o, int row_f, int col_f);
	bool movimiento(string mov);
	string notacion_ulimo_moviento();
	string notacion_partida();
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


	// Servicios heredados de chestime.h:

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
	friend class IA_dificil;
	friend class IA_facil;
	friend class IA_UnitTests;
	tablero_t tab;

	// Movimiento piezas:
	bool analisis_mov;
	tablero_info_t get_mov_permitidos(pieza_t* a, tablero_t tab);

	lista_movimientos get_mov_permitidos_l(tablero_t tab, int row_o, int col_o);

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
	bool tableros_iguales(tablero_t t1, tablero_t t2);

	// Jaques, mates y ahogados:
	bool rey_ahogado(color_pieza_t color);
	bool rey_jaque_mate(color_pieza_t color);
	bool jaque_player(color_pieza_t color, tablero_t mat);

	// Notacion del movimietno
	ostringstream mov;
	ostringstream mov_partida;
	char row_to_char(int row);
	char col_to_char(int col);
	int char_to_row(char row);
	int char_to_col(char col);


	// Reglas espieciales peón: comer al paso y promoción
	void aux_detectar_comer_al_paso(tablero_info_t& matriz, pieza_t peon, int row, int col);
	void aux_detectar_promocion(tablero_info_t& matriz, pieza_t peon, int row, int col);

	// Auxiliar:
	void tablero_inicio_normal();
	void tablero_inicio_peones();

	bool jaque_mate();

	tablero_t get_tablero() { return this->tab; }
	void set_tablero(tablero_t tablero) { this->tab = tablero; }

};

#endif


// TESTS UNITARIOS
/*

#include <iostream>
#include "chesstime.h";
#include "ChessRules.h";

#include <thread>
#include <chrono>
using std::this_thread::sleep_for;
using namespace std::chrono_literals;


int main(void)
{

	// Test unitario (ejemplo del mate del tonto)
	Juego a(RAPIDA);

	int secuencia = 0;
	while (!a.jaque_mate_playerA() && !a.jaque_mate_playerB() && !a.tablas()) {

		sleep_for(1000ms);
		secuencia++;


		// MATE DEL TONTO:
		//switch (secuencia)
		//{
		//case 1:
		//    a.movimiento(6, 6, 4, 6);
		//    //a.movimiento(static_cast<string>("Pg2 g4"));
		//    cout << a.print();
		//    break;
		//case 5:
		//    //a.movimiento(1, 4, 3, 4);
		//    a.movimiento(static_cast<string>("Pe7 e5"));
		//    cout << a.print();
		//    break;
		//case 10:
		//    //a.movimiento(6, 5, 5, 5);
		//    a.movimiento(static_cast<string>("Pf2 f3"));
		//    cout << a.print();
		//    break;
		//case 15:
		//    //a.movimiento(0, 3, 4, 7);
		//    a.movimiento(static_cast<string>("Pd8 h4"));
		//    cout << a.print();
		//    break;
		//default:
		//    break;
		//}


		// MATE DEL PASTOR:
		switch (secuencia)
		{
		case 1:
			a.movimiento(static_cast<string>("Pe2 e4"));
			cout << a.print();
			break;
		case 5:
			//a.movimiento(1, 4, 3, 4);
			a.movimiento(static_cast<string>("Pe7 e5"));
			cout << a.print();
			break;
		case 10:
			//a.movimiento(6, 5, 5, 5);
			a.movimiento(static_cast<string>("Af1 c4"));
			cout << a.print();
			break;
		case 15:
			//a.movimiento(0, 3, 4, 7);
			a.movimiento(static_cast<string>("Cb8 c6"));
			cout << a.print();
			break;
		case 20:
			//a.movimiento(0, 3, 4, 7);
			a.movimiento(static_cast<string>("Dd1 f3"));
			cout << a.print();
			break;
		case 25:
			//a.movimiento(0, 3, 4, 7);
			a.movimiento(static_cast<string>("Cc6 a5"));
			cout << a.print();
			break;
		case 30:
			//a.movimiento(0, 3, 4, 7);
			a.movimiento(static_cast<string>("Df3 f7"));
			cout << a.print();
			break;
		default:
			break;
		}


		// Print tiempo:
		cout << a.getMinLeftPlaA() << ":" << a.getSecLeftPlaA() << " " << a.getMinLeftPlaB() << ":" << a.getSecLeftPlaB() << " " << a.jaque_mate_playerA() << std::endl;

	}

	// Fin de la  partida
	cout << "Fin de la partida" << endl << endl;
	cout << a.notacion_partida();



	//tablero_t aux = a.getTablero();
	//tablero_info_t info = a.mov_permitidos(&(aux[6][0]), aux);

	//movimiento_t mov = info.TAB[5][0];
	//mov = info.TAB[4][0];
	//mov = info.TAB[4][5];

	//cout << a.print();
	//a.movimiento(6, 0, 5, 4);
	//cout << a.print();

	return 0;
}


*/
