#include "chesstime.h"
#include <time.h>

chesstime::chesstime(modo_partida_t mode)
{
	modo = mode;
	switch (modo)
	{
	case RAPIDA:
		leftTotalSecPlaA = RAPIDA_MIN * 60;
		leftTotalSecPlaB = RAPIDA_MIN * 60;
		break;
	case SEMIRAPIDA:
		leftTotalSecPlaA = SEMIRAPIDA_MIN * 60;
		leftTotalSecPlaB = SEMIRAPIDA_MIN * 60;
		break;
	case NORMAL:
		leftTotalSecPlaA = NORMAL_MIN * 60;
		leftTotalSecPlaB = NORMAL_MIN * 60;
		break;
	}

	secLeftPlaA = 0;
	secLeftPlaB = 0;
	minLeftPlaA = 0;
	minLeftPlaB = 0;
	lastAEpoch = 0;
	lastBEpoch = 0;

	isTrunPlayerA = false;
	isTrunPlayerB = false;

	updateTimeValues();
}


void chesstime::updateTimeValues()
{
	uint now = getNowEpochTime();

	if (isTrunPlayerA) {
		if (lastAEpoch != now) {
			leftTotalSecPlaA -= (now - lastAEpoch);
			lastAEpoch = now;
		}
	}

	else if (isTrunPlayerB) {
		if (lastBEpoch != now) {
			leftTotalSecPlaB -= (now - lastBEpoch);
			lastBEpoch = now;
		}
	}

	uint aux;
	uint min;

	// Tiempo jugador A formato normal
	aux = leftTotalSecPlaA;
	min = 0;
	while (aux > 59) {
		aux = aux - 60;
		min++;
	}
	minLeftPlaA = min;
	secLeftPlaA = leftTotalSecPlaA % 60;

	// Tiempo jugador B formato normal
	aux = leftTotalSecPlaB;
	min = 0;
	while (aux > 59) {
		aux = aux - 60;
		min++;
	}
	minLeftPlaB = min;
	secLeftPlaB = leftTotalSecPlaB % 60;

}


bool chesstime::PlaA_end_time()
{
	if ((isTrunPlayerA || isTrunPlayerB) && leftTotalSecPlaA == 0) {
		return true;
	}
	return false;
}

bool chesstime::PlaB_end_time()
{
	if ((isTrunPlayerA || isTrunPlayerB) && leftTotalSecPlaB == 0) {
		return true;
	}
	return false;
}

void chesstime::start()
{
	isTrunPlayerA = true;
	isTrunPlayerB = false;
	lastAEpoch = getNowEpochTime();
}

int chesstime::getSecLeftPlaA()
{
	updateTimeValues();
	return secLeftPlaA;
}

int chesstime::getSecLeftPlaB()
{
	updateTimeValues();
	return secLeftPlaB;
}

int chesstime::getMinLeftPlaA()
{
	updateTimeValues();
	return minLeftPlaA;
}

int chesstime::getMinLeftPlaB()
{
	updateTimeValues();
	return minLeftPlaB;
}

void chesstime::turnPlayerA()
{
	updateTimeValues();
	isTrunPlayerA = true;
	isTrunPlayerB = false;
	lastAEpoch = getNowEpochTime();
	updateTimeValues();
}

void chesstime::turnPlayerB()
{
	updateTimeValues();
	isTrunPlayerA = false;
	isTrunPlayerB = true;
	lastBEpoch = getNowEpochTime();
	updateTimeValues();
}


uint chesstime::getNowEpochTime()
{
	time_t t = time(NULL);
	localtime(&t);
	return t;
}
