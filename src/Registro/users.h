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
	float score; //puntuación del usuario
public:
	User();
	void setname(); //setter del nombre de usuario por scanf
	void stablishname(string n);//setter del nombre de usuario por string enviada
	std::string getname(); //getter del nombre de usuario
	void setscore(); //setter del score del usuario por scanf
	void stablishscore(float n);//setter del score del usuario por float enviado
	float getscore(); //getter de la puntuación del usuario
	void adduser(); //gestión para añadir user personalizado al fichero
	void actualizeusers(); //actualización de los usuarios en la clase por el fichero
	void createreplay(User b);//crea la replay
	void readreplay(User b);//lee la replay buscada y la envía a la función mover ficha
	void deletereplay(User b);//elimina replay
};