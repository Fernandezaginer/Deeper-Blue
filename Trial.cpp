#include "users.cpp"

int main()
{
	User us1;
	us1.setname(); // poner nombre al usuario us1
	us1.setscore(9.0f); // seteo de la puntuaci�n del usuario 
	printf_s("usuario: %s\nPuntaje: %f", us1.getname().c_str(), us1.getscore()); // impresi�n para corroborar 
	//printf("%s\n",someString.c_str()); � std::cout << YourString << std::endl;
	return 0;
}

