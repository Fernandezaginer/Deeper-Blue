#pragma once
#include "users.h"
using namespace std;
//actualiza usuarios del fichero al obejeto
void actUsers() {
	User X, A, B, C, D, E;
	ifstream fich("users.txt");
	if (!fich.is_open())
	{
		cout << "Error al abrir users.txt\n";
		exit(EXIT_FAILURE);
	}
	string aux, listuser[12];
	int i = 0;
	while (getline(fich, aux))
	{
		listuser[i] = aux;
		i++;
	}
	if (i > 0)
	{
		X.stablishname(listuser[0]);
		X.stablishscore(stof(listuser[1]));
	}
	if (i > 2)
	{
		A.stablishname(listuser[2]);
		A.stablishscore(stof(listuser[3]));
	}
	if (i > 4)
	{
		B.stablishname(listuser[4]);
		B.stablishscore(stof(listuser[5]));
	}
	if (i > 6)
	{
		C.stablishname(listuser[6]);
		C.stablishscore(stof(listuser[7]));
	}
	if (i > 8)
	{
		D.stablishname(listuser[8]);
		D.stablishscore(stof(listuser[9]));
	}
	if (i > 10)
	{
		E.stablishname(listuser[10]);
		E.stablishscore(stof(listuser[11]));
	}
	fich.close();
	printf_s("usuarios\n");
	printf_s("%s\n %f\n", X.getname().c_str(), X.getscore());
	printf_s("%s\n %f\n", A.getname().c_str(), A.getscore());
	printf_s("%s\n %f\n", B.getname().c_str(), B.getscore());
	printf_s("%s\n %f\n", C.getname().c_str(), C.getscore());
	printf_s("%s\n %f\n", D.getname().c_str(), D.getscore());
	printf_s("%s\n %f\n", E.getname().c_str(), E.getscore());
}
//añade usuario al fichero
void usertofile()
{
	ifstream fich("users.txt");
	if (!fich.is_open())
	{
		cout << "Error al abrir users.txt\n";
		exit(EXIT_FAILURE);
	}
	string aux, fulluserlist;
	float score;
	int s = 0;
	while (getline(fich, aux))
	{

		if (s < 11)
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
	if (s >= 12)
	{
		printf("Superada la cantidad de usuarios\n");
	}
	else
	{
		string usuario;
		printf("Introduzca su nombre de usuario\n"); //petición de username
		getline(std::cin, usuario);
		fulluserlist = fulluserlist + usuario + "\n0"; // 0 default de score
	}
	foch << fulluserlist << endl;
	foch.close();
	//cout << "exito\n"; //borrar mas adelante, es por comprobar el final del programa
	actUsers(); //actualización de los usuarios
}
//elimina usuario del fichero
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
	int s = 0, flag = 0;
	while (getline(fich, aux))
	{
		if (duser == aux)
		{
			flag = 1;
			continue;
		}
		if (flag == 1)
		{
			flag = 0;
			continue;
		}
		fulluserlist = fulluserlist + aux + "\n";
		s++;
	}
	int del = fulluserlist.size();
	fulluserlist[del - 1] = '\0'; //eliminación de un \n muy extraño
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