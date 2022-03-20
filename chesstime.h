

#ifndef _CHESSTIME_H_
#define _CHESSTIME_H_

enum modo_partida_t {RAPIDA, SEMIRAPIDA, NORMAL};

#define RAPIDA_MIN		10
#define SEMIRAPIDA_MIN	20
#define NORMAL_MIN		30

#define _CRT_SECURE_NO_WARNINGS

typedef unsigned int uint;

class chesstime {

public:  // Servicios

	// Constructor de inicio de la partida
	chesstime(modo_partida_t mode);

	// Iniciar el tiempo de la partida (Empieza PlayerA)
	void start();

	// Métodos para obtener el tiempo restante de cada jugador
	int getSecLeftPlaA();
	int getSecLeftPlaB();
	int getMinLeftPlaA();
	int getMinLeftPlaB();

	// Métodos para indicar de quien es el turno
	void turnPlayerA();
	void turnPlayerB();

	// Métodos para indicar si algún jugador pierde por tiempo
	bool PlaA_end_time();
	bool PlaB_end_time();

private:  // No tocar

	modo_partida_t modo;

	bool isTrunPlayerA;
	bool isTrunPlayerB;

	uint leftTotalSecPlaA;
	uint leftTotalSecPlaB;

	uint secLeftPlaA;
	uint secLeftPlaB;
	uint minLeftPlaA;
	uint minLeftPlaB;

	uint lastAEpoch;
	uint lastBEpoch;

	uint getNowEpochTime();
	void updateTimeValues();
};

#endif


