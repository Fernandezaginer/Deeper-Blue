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
	std::string getname(); //getter del nombre de usuario
	void setscore(); //setter del score del usuario por scanf
	void stablishscore(float n);//setter del score del usuario por float enviado
	float getscore(); //getter de la puntuaci�n del usuario
	void adduser(); //gesti�n para a�adir user personalizado al fichero
	void actualizeusers(); //actualizaci�n de los usuarios en la clase por el fichero
	void createreplay(User b);//crea la replay
	void readreplay(User b);//lee la replay buscada y la env�a a la funci�n mover ficha
	void deletereplay(User b);//elimina replay
};