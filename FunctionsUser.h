#pragma once
#include "users.h"
using namespace std;

void actUsers() {
	User X, A, B, C, D, E;
	ifstream fich("users.txt");
	if (!fich.is_open())
	{
		cout << "Error al abrir users.txt\n";
		exit(EXIT_FAILURE);
	}
	string aux, list[6];
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
	printf_s("usuarios:\n%s\n%s\n%s\n%s\n%s\n%s\n", X.getname().c_str(), A.getname().c_str(), B.getname().c_str(), C.getname().c_str(), D.getname().c_str(), E.getname().c_str());
	fich.close();
}

void usertofile()
{
	ifstream fich("users.txt");
	if (!fich.is_open())
	{
		cout << "Error al abrir users.txt\n";
		exit(EXIT_FAILURE);
	}
	string aux, fulluserlist;
	int s = 0;
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
		string usuario;
		printf("Introduzca su nombre de usuario\n"); //petición de username
		getline(std::cin, usuario);
		fulluserlist = fulluserlist + usuario;
	}
	foch << fulluserlist << endl;
	foch.close();
	//cout << "exito\n"; //borrar mas adelante, es por comprobar el final del programa
	actUsers(); //actualización de los usuarios
}

void deleteuser()
{
	ifstream fich("users.txt");
	if (!fich.is_open())
	{
		cout << "Error al abrir users.txt\n";
		exit(EXIT_FAILURE);
	}
	printf_s("¿Que usuario desea eliminar?\n");
	string aux, fulluserlist, duser;
	getline(std::cin, duser);
	int s = 0;
	while (getline(fich, aux))
	{
		if (duser == aux)
			continue;
		fulluserlist = fulluserlist + aux + "\n";
		s++;
	}
	int puto = fulluserlist.size();
	fulluserlist[puto - 1] = '\0'; //eliminación de un \n muy extraño
	fich.close();
	/////////////////////////////////////////////////
	ofstream foch("users.txt");
	if (!foch)
	{
		cout << "Error al abrir users.txt\n";
		exit(EXIT_FAILURE);
	}
	foch << fulluserlist << endl;
	foch.close();
	cout << "exito al eliminar el usuario\n"; //borrar mas adelante, es por comprobar el final del programa
	cout << "nuevos usuarios:\n";
	actUsers(); //actualización de los usuarios
}