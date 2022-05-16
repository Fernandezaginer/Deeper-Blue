#pragma once
#include <sstream>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

class User{
private:
	std::string name; //nombre del usuario
	float score; //puntuaci�n del usuario
public:
	User();
	void setname(); //setter del nombre de usuario por scanf
	void stablishname(string n);//setter del nombre de usuario por string enviada
	std::string getname(); //getter directo del nombre de usuario
	void setscore(); //setter del score del usuario por scanf
	void stablishscore(float n);//setter del score del usuario por float enviado
	float getscore(); //getter directo de la puntuaci�n del usuario
	void adduser(); //gesti�n para a�adir user personalizado al fichero
	void actualizeusers(); //actualizaci�n de los usuarios en la clase por el fichero
	void createreplay(User b, string savemove);//crea la replay
	void readreplay(User b);//lee la replay buscada y la env�a el string del movimiento de ficha
	void deletereplay(User b);//elimina replay
};