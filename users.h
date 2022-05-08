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
	float score; //puntuaci�n del usuario
public:
	User();
	void setname(string ); //setter del nombre de usuario
	std::string getname(); //getter del nombre de usuario
	void setscore(float); //setter del score del usuario
	float getscore(); //getter de la puntuaci�n del usuario
	void adduser(); //gesti�n para a�adir user personalizado al fichero
	void actualizeusers(); //actualizaci�n de los usuarios en la clase por el fichero
};
