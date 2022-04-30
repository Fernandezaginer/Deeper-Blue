

// Test unitario:
/*
#include "users.cpp"

int main()
{
	User us1;
	us1.setname(); // poner nombre al usuario us1
	us1.setscore(9.0f); // seteo de la puntuación del usuario 
	printf_s("usuario: %s\nPuntaje: %f", us1.getname().c_str(), us1.getscore()); // impresión para corroborar 
	//printf("%s\n",someString.c_str()); ò std::cout << YourString << std::endl;
	return 0;
}
*/

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
