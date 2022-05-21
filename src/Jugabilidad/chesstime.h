// TEST UNITARIO:
	/*
	chesstime tiempo = chesstime(SEMIRAPIDA);
	std::cout << "Tiempo A: " << tiempo.getMinLeftPlaA() << ":" << tiempo.getSecLeftPlaA() << "  Tiempo B:" << tiempo.getMinLeftPlaB() << ":" << tiempo.getSecLeftPlaB() << std::endl;
	tiempo.start();
	while (true) {

		int out;
		std::cin >> out;
		tiempo.turnPlayerB();
		std::cout << "Tiempo A: " << tiempo.getMinLeftPlaA() << ":" << tiempo.getSecLeftPlaA() << "  Tiempo B:" << tiempo.getMinLeftPlaB() << ":" << tiempo.getSecLeftPlaB() << std::endl;
		std::cin >> out;
		tiempo.turnPlayerA();
		std::cout << "Tiempo A: " << tiempo.getMinLeftPlaA() << ":" << tiempo.getSecLeftPlaA() << "  Tiempo B:" << tiempo.getMinLeftPlaB() << ":" << tiempo.getSecLeftPlaB() << std::endl;
	}
	*/


#ifndef _CHESSTIME_H_
#define _CHESSTIME_H_

enum modo_partida_t { RAPIDA, SEMIRAPIDA, NORMAL };

#define RAPIDA_MIN		10
#define SEMIRAPIDA_MIN	20
#define NORMAL_MIN		30

#define _CRT_SECURE_NO_WARNINGS

typedef unsigned int uint;

class chesstime {

public:  // Servicios

	// Métodos para obtener el tiempo restante de cada jugador
	int getSecLeftPlaA();
	int getSecLeftPlaB();
	int getMinLeftPlaA();
	int getMinLeftPlaB();

	// Métodos para indicar si algún jugador pierde por tiempo
	bool PlaA_end_time();
	bool PlaB_end_time();

	// Iniciar el tiempo de la partida (Empieza PlayerA)
	void start();

	// Constructor de inicio de la partida
	chesstime(modo_partida_t mode);

	bool getIsTurnPlayerA(){ return isTrunPlayerA; }
	bool getIsTurnPlayerB(){ return isTrunPlayerA; }

protected: // No tocar

	// Métodos para indicar de quien es el turno
	void turnPlayerA();
	void turnPlayerB();

	// Turno del jugador
	bool isTrunPlayerA;
	bool isTrunPlayerB;

	modo_partida_t getModo() { return modo; }

private:  // No tocar

	modo_partida_t modo;

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