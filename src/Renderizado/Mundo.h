#include "TABLERO.h"
#include "ChessRules.h"
#include "Controles.h"
#include "IA/IA.h"

#pragma once
class Mundo
{
public: 
	void tecla(unsigned char key);
	void inicializa();
	void rotarOjo();
	void mueve();
	void dibuja();
	void raton(int b, int e, int x, int y);
	bool playerA_won() { return this->j.playerA_won(); }
	bool playerB_won() { return this->j.playerB_won(); }
	bool tablas() { return this->j.tablas(); }

	int score_playerA() { return this->j.score_playerA(); }
	int score_playerB() { return this->j.score_playerB(); }

	string notacion_partida() { return this->j.notacion_partida(); }

	bool isVsIA;

	Juego j;
private:
	float x_ojo;
	float y_ojo;
	float z_ojo;

	TABLERO t;
	IA_dificil IA;

	controles con;
};
