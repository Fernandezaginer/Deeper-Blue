#pragma once
#include <sstream>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

class User{
public:
	std::string name; //nombre del usuario
	float score; //puntuación del usuario
public:
	User();
	void setname(string ); //setter del nombre de usuario
	std::string getname(); //getter del nombre de usuario
	void setscore(float); //setter del score del usuario
	float getscore(); //getter de la puntuación del usuario
	void adduser(); //gestión para añadir user personalizado al fichero
	void actualizeusers(); //actualización de los usuarios en la clase por el fichero
};
