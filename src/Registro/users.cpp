#include "users.h"
#include "Chessrules.h"
#include "chesstime.h"
#include "Pieza.h"
#include <thread>
#include <chrono>
using std::this_thread::sleep_for;
using namespace std::chrono_literals;
using namespace std;

//datos por defecto
User::User()
{
	name = "FREE_SLOT"; //nombre default
	score = 0.0f; //puntuación default
}
//añade usuario directamente, es fuertemente preferible el uso de la función usertofile en lugar de esta
void User::adduser()
{
	ifstream fich("registro/users.txt");
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
	ofstream foch("registro/users.txt");
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
		printf("Introduzca su nombre de usuario\n"); //petición de username
		getline(std::cin, name);
		fulluserlist = fulluserlist + name;
	}
	foch << fulluserlist << endl;
	foch.close();
	cout << "exito"; //borrar mas adelante, es por comprobar el final del programa
	actualizeusers();
}
//actualiza los usuarios por el fichero, es fuertemente preferible el uso de la función actUsers en lugar de esta
void User::actualizeusers()
{
	User X, A, B, C, D, E;
	ifstream fich("registro/users.txt");
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
	printf("Introduzca su nombre de usuario\n"); //petición de username
	getline(std::cin, name);  //´getline para sobreescribir el nombre del usurario
} 
//se utiliza el nombre enviado para establecerlo
void User::stablishname(string n)
{
	ifstream fich("registro/users.txt");
	if (!fich.is_open())
	{
		cout << "Error al abrir users.txt\n";
		exit(EXIT_FAILURE);
	}
	string aux, fulluserlist;
	int s = 0, flag = 0;
	while (getline(fich, aux))
	{
		if (aux == name)
		{
			getline(fich, aux);
			fulluserlist = fulluserlist + n + "\n";
			fulluserlist = fulluserlist + aux + "\n";
		}
		else
		{
			fulluserlist = fulluserlist + aux + "\n";
		}
		s++;
	}
	int del = fulluserlist.size();
	fulluserlist[del - 1] = '\0'; //eliminación de un \n muy extraño
	fich.close();
	/////////////////////////////////////////////////
	ofstream foch("registro/users.txt");
	if (!foch)
	{
		cout << "Error al abrir users.txt\n";
		exit(EXIT_FAILURE);
	}
	foch << fulluserlist << endl;
	foch.close();
	name = n;
}
//setter especial para el actusers
void User::stablishnameactu(string n) {
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
void User::stablishscore(int n)
{
	score = n;
	ifstream fich("registro/users.txt");
	if (!fich.is_open())
	{
		cout << "Error al abrir users.txt\n";
		exit(EXIT_FAILURE);
	}
	string aux, fulluserlist = "";
	int s = 0, flag = 0;
	while (getline(fich, aux))
	{
		if (aux == name)
		{
			fulluserlist = fulluserlist + aux + '\n';
			getline(fich, aux);
			fulluserlist = fulluserlist + to_string(n) + '\n';
		}
		else
		{
			fulluserlist = fulluserlist + aux + '\n';
		}
		s++;
	}
	int del = fulluserlist.size();
	fulluserlist[del - 1] = '\0'; //eliminación de un \n muy extraño
	fich.close();
	/////////////////////////////////////////////////
	ofstream foch("registro/users.txt");
	if (!foch)
	{
		cout << "Error al abrir users.txt\n";
		exit(EXIT_FAILURE);
	}
	foch << fulluserlist << endl;
	foch.close();
}
//setter especial para actusers
void User::stablishscoreactu(float n) {
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
		foch << savemove << endl; //impresión del replay
	}
	foch.close();
}
//Leer replay
void User::readreplay(User n) {
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
		Juego replaygame; //creación de partida replay
		replaygame.movimiento(move); //lee el movimiento
		sleep_for(1000ms); //tiempo para apreciar cada movimiento
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
	fullreplaylist[del - 1] = '\0'; //eliminación de un \n muy extraño
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