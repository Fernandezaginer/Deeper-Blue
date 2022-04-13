#pragma once
#include <sstream>
#include <iostream>
#include <string>

class User{
public: 
	std::string name; //nombre del usuario
	float score; //puntuación del usuario
public:
	inline User();
	inline void setname(); //setter del nombre de usuario
	inline std::string getname(); //getter del nombre de usuario
	inline void setscore(float); //setter del score del usuario
	inline float getscore(); //getter de la puntuación del usuario
};
