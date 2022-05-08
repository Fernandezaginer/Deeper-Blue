#include "users.h"
#include "FunctionsUser.h"
using namespace std;

int main()
{
	/*
	User us1;
	us1.setname(); // poner nombre al usuario us1
	us1.setscore(9.0f); // seteo de la puntuación del usuario 
	printf_s("usuario: %s\nPuntaje: %f", us1.getname().c_str(), us1.getscore()); // impresión para corroborar 
	//printf("%s\n",someString.c_str()); ò std::cout << YourString << std::endl;
	*/
	deleteuser();
	usertofile();
	return 0;
}

