#pragma once
class pantalla {
public:
	float ancho;
	float alto;
	float limite1x;
	float limite1y;
	
	unsigned char rojo;
	unsigned char verde;
	unsigned char azul;

	pantalla();
	void dibuja();
	void setcolor(unsigned char r, unsigned char v, unsigned char a);
	
};
