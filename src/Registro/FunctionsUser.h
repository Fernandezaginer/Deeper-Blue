#pragma once
#include "users.h"
#include <vector>
using namespace std;

//actualiza usuarios del fichero al obejeto
vector<User> actUsers() {
	User X, A, B, C, D, E;

	vector<User> usuarios;
	ifstream fich("registro/users.txt");
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
	i--;
	if (i > 0)
	{
		X.stablishnameactu(listuser[0]);
		X.stablishscoreactu(stof(listuser[1]));
		usuarios.push_back(X);
	}
	if (i > 2)
	{
		A.stablishnameactu(listuser[2]);
		A.stablishscoreactu(stof(listuser[3]));
		usuarios.push_back(A);
	}
	if (i > 4)
	{
		B.stablishnameactu(listuser[4]);
		B.stablishscoreactu(stof(listuser[5]));
		usuarios.push_back(B);
	}
	if (i > 6)
	{
		C.stablishnameactu(listuser[6]);
		C.stablishscoreactu(stof(listuser[7]));
		usuarios.push_back(C);
	}
	if (i > 8)
	{
		D.stablishnameactu(listuser[8]);
		D.stablishscoreactu(stof(listuser[9]));
		usuarios.push_back(D);
	}
	if (i > 10)
	{
		E.stablishnameactu(listuser[10]);
		E.stablishscoreactu(stof(listuser[11]));
		usuarios.push_back(E);
	}
	fich.close();
	/*printf_s("usuarios\n");
	printf_s("%s\n %f\n", X.getname().c_str(), X.getscore());
	printf_s("%s\n %f\n", A.getname().c_str(), A.getscore());
	printf_s("%s\n %f\n", B.getname().c_str(), B.getscore());
	printf_s("%s\n %f\n", C.getname().c_str(), C.getscore());
	printf_s("%s\n %f\n", D.getname().c_str(), D.getscore());
	printf_s("%s\n %f\n", E.getname().c_str(), E.getscore());*/

	return usuarios;
}
//añade usuario al fichero
User usertofile(string usuario)
{
	ifstream fich("registro/users.txt");
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
	ofstream foch("registro/users.txt");
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
		//string usuario;
		printf("Introduzca su nombre de usuario\n"); //petición de username
		//getline(std::cin, usuario);
		fulluserlist = fulluserlist + usuario + "\n0"; // 0 default de score
	}
	foch << fulluserlist << endl;
	foch.close();
	//cout << "exito\n"; //borrar mas adelante, es por comprobar el final del programa
	return actUsers().back(); //actualización de los usuarios
}
//elimina usuario del fichero
void deleteuser()
{
	ifstream fich("registro/users.txt");
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
	ofstream foch("registro/users.txt");
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