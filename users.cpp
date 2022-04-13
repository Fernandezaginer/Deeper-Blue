#include "users.h"
using namespace std;

User::User()
{
	name = "default"; //nombre default
	score = 0.0f; //puntuación default
}

void User::setname()
{
	printf("Introduzca su nombre de usuario\n"); //petición de username
	getline(std::cin, name);  //´getline para sobreescribir el nombre del usurario
}

string User::getname()
{
	return (name); //regresa nombre de usuario
}

void User::setscore(float newscore)
{
	score = newscore; // establece el nuevo puntaje
}
float User::getscore()
{
	return (score); //regresa el puntaje
}