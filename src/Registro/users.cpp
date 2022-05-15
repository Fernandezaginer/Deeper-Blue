#include "users.h"
using namespace std;
//datos por defecto
User::User()
{
	name = "FREE_SLOT"; //nombre default
	score = 0.0f; //puntuaci�n default
}
//a�ade usuario directamente, es fuertemente preferible el uso de la funci�n usertofile en lugar de esta
void User::adduser()
{
	ifstream fich("users.txt");
	if (!fich.is_open())
	{
		cout << "Error al abrir users.txt\n";
		exit(EXIT_FAILURE);
	}
	int s = 0;
	string aux, fulluserlist;
	while (getline(fich, aux)) 
	{
		if (s < 5)
			fulluserlist = fulluserlist + aux + "\n";
		else
			fulluserlist = fulluserlist + aux;
		s++;
	}
	fich.close();
	/////////////////////////////////////////////////
	ofstream foch("users.txt");
	if (!foch)
	{
		cout << "Error al abrir users.txt\n";
		exit(EXIT_FAILURE);
	}
	if (s >= 6)
	{
		printf("Superada la cantidad de usuarios\n");
	}
	else
	{
		printf("Introduzca su nombre de usuario\n"); //petici�n de username
		getline(std::cin, name);
		fulluserlist = fulluserlist + name;
	}
	foch << fulluserlist << endl;
	foch.close();
	cout << "exito"; //borrar mas adelante, es por comprobar el final del programa
	actualizeusers();
}
//actualiza los usuarios por el fichero, es fuertemente preferible el uso de la funci�n actUsers en lugar de esta
void User::actualizeusers()
{
	User X, A, B, C, D, E;
	ifstream fich("users.txt");
	if (!fich.is_open())
	{
		cout << "Error al abrir users.txt\n";
		exit(EXIT_FAILURE);
	}
	string aux, list[7];
	int i = 0;
	while (getline(fich, aux)) 
	{
		list[i] = aux;
		i++;
	}
	X.name = list[0];
	A.name = list[1];
	B.name = list[2];
	C.name = list[3];
	D.name = list[4];
	E.name = list[5];
	printf_s("usuarios: %s\n%s\n%s\n%s\n%s\n%s\n", X.getname().c_str(), A.getname().c_str(), B.getname().c_str(), C.getname().c_str(), D.getname().c_str(), E.getname().c_str());
	fich.close();
}
//pide un nombre y lo establece
void User::setname()
{
	printf("Introduzca su nombre de usuario\n"); //petici�n de username
	getline(std::cin, name);  //�getline para sobreescribir el nombre del usurario
} 
//se utiliza el nombre enviado para establecerlo
void User::stablishname(string n)
{
	name = n;
}
//devuelve el nombre
string User::getname()
{
	return (name); //regresa nombre de usuario
}
//pide un puntaje y lo establece
void User::setscore()
{
	printf("Introduzca el puntaje que desea:\n");
	scanf_s("%f", &score);
}
//se utiliza el puntaje enviado para establecerlo
void User::stablishscore(float n)
{
	score = n;
}
//devuelve el puntaje
float User::getscore()
{
	return (score); //regresa el puntaje
}
//Crear replay
void User::createreplay(User n, string savemove) {
	ifstream fich("replay.txt");
	if (!fich.is_open())
	{
		cout << "Error al abrir replay.txt\n";
		exit(EXIT_FAILURE);
	}
	string aux, fullreplaylist;
	int s = 0;
	while (getline(fich, aux))
	{
			fullreplaylist = fullreplaylist + aux + "\n";
	}
	fich.close();
	////////////////////////////
	ofstream foch("replay.txt");
	if (!foch)
	{
		cout << "Error al abrir replay.txt\n";
		exit(EXIT_FAILURE);
	}
	else
	{
		fullreplaylist = fullreplaylist + savemove;
		foch << savemove << endl; //impresi�n del replay
	}
	foch.close();
}
//Leer replay
string User::readreplay(User n) {
	ifstream fich("replay.txt");
	if (!fich.is_open())
	{
		cout << "Error al abrir replay.txt\n";
		exit(EXIT_FAILURE);
	}
	string move, pool;
	pool = name + " vs " + n.name;
	getline(fich, move);
	while (move != pool)
	{
		getline(fich, move);
	}
	while (move != "FIN")
	{
		return(move);
	}
	fich.close();
}
//eliminar replay (solo elimina la mas reciente)
void User::deletereplay(User n){
	ifstream fich("replay.txt");
	if (!fich.is_open())
	{
		cout << "Error al abrir replay.txt\n";
		exit(EXIT_FAILURE);
	}
	string move, pool, fullreplaylist;
	pool = name + " vs " + n.name;
	getline(fich, move);
	fullreplaylist = move + "\n";
	while (move != pool)
	{
		getline(fich, move);
		fullreplaylist = fullreplaylist + move + "\n";
	}
	while (move != "FIN")
	{
		getline(fich, move);
	}
	getline(fich, move);
	while (getline(fich, move))
	{
		fullreplaylist = fullreplaylist + move + "\n";
	}
	int del = fullreplaylist.size();
	fullreplaylist[del - 1] = '\0'; //eliminaci�n de un \n muy extra�o
	fich.close();
	/////////////////////////////////////////////////
	ofstream foch("replay.txt");
	if (!foch)
	{
		cout << "Error al abrir replay.txt\n";
		exit(EXIT_FAILURE);
	}
	foch << fullreplaylist << endl;
	foch.close();
}