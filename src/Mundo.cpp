#include "freeglut.h"
#include <math.h>
#include <iostream>
#include <stdlib.h>
#include <ctime>
#include "Controles.h"
#include "ETSIDI.h"
#include "Inicio.h"
#include "Pantalla.h"
#include "Mundo.h"

using namespace std;

Mundo::Mundo() {
	this->x_ojo=0;
	this->y_ojo=0;
	this->z_ojo=0;
	this->estado = 0;
	this->t_0 = time(NULL);
	this->pan = pantalla();
	this->in = inicio();
	this->con = controles();
}

void Mundo::rotarOjo()
{
	float dist = sqrt(this->x_ojo * this->x_ojo + this->z_ojo * this->z_ojo);
	float ang = atan2(this->z_ojo, this->x_ojo);
	ang += 0.05f;
	x_ojo = dist * cosf(ang);
	z_ojo = dist * sinf(ang);
}
void Mundo::dibuja()
{

	gluLookAt(this->x_ojo, this->y_ojo, this->z_ojo,  // posicion del ojo
		0.0, this->y_ojo, 0.0,      // hacia que punto mira  (0,0,0) 
		0.0, 1.0, 0.0);      // definimos hacia arriba (eje Y)    
	

	//aqui es donde hay que poner el codigo de dibujo
	this->con.coger_pos();
	this->pan.dibuja();
	switch (this->estado)
	{
	case 0: // pantalla de inicio sin el start
		this->in.direct = "misimagenes/iniciox.png";
		
		if (time(NULL) > static_cast<long long>(this->t_0) + 2) {
			this->estado = 1;
			this->t_0 = time(NULL);
		}
		break;
	case 1: // inicio+start blanco
		this->in.direct = "misimagenes/inicio.png";
		if (this->con.mousePos.y < 650 && this->con.mousePos.y > 606 && this->con.mousePos.x > 646 && this->con.mousePos.x < 863) {
			this->estado = 2;
		}
		break;
	case 2:// inicio+start rosa 
		this->in.direct = "misimagenes/inicior.png";
		if (this->con.mousePos.y > 650 || this->con.mousePos.y < 606 || this->con.mousePos.x < 646 || this->con.mousePos.x > 863) {
			this->estado = 1;
		}
		if (controles::boton == GLUT_LEFT_BUTTON && controles::estado == GLUT_UP) {
			this->estado = 3;
		}
		break;
	case 3://usuarios
		//this->in.direct = "misimagenes/jugadores.png";
		this->estado = 4;
		//introducir if para cuando haya dos jugadores introducidos proceda a case 10 == carga 1v1
		//this->estado = 10;
		break;
	case 4://menu
		this->in.direct = "misimagenes/menu.png";
		if (this->con.mousePos.y < 343 && this->con.mousePos.y >307 && this->con.mousePos.x > 523 && this->con.mousePos.x < 626) {
			this->estado = 5;
		}
		if (this->con.mousePos.y < 398 && this->con.mousePos.y > 365 && this->con.mousePos.x > 519 && this->con.mousePos.x < 584) {
			this->estado = 6;
		}
		if (this->con.mousePos.y < 450 && this->con.mousePos.y > 418 && this->con.mousePos.x > 519 && this->con.mousePos.x < 827) {
			this->estado = 7;
		}
		if (this->con.mousePos.y < 504 && this->con.mousePos.y > 472 && this->con.mousePos.x > 519 && this->con.mousePos.x < 1004) {
			this->estado = 8;
		}
		if (this->con.mousePos.y < 559 && this->con.mousePos.y > 527 && this->con.mousePos.x > 519 && this->con.mousePos.x < 673) {
			this->estado = 9;
		}
		break;
	case 5: //menu+1v1
		this->in.direct = "misimagenes/m1v1.png";
		if (this->con.mousePos.y > 343 || this->con.mousePos.y < 307 || this->con.mousePos.x < 523 || this->con.mousePos.x > 626) {
			this->estado = 4;
		}
		if (controles::boton == GLUT_LEFT_BUTTON && controles::estado == GLUT_DOWN) {
			this->estado = 10; //CAMBIAR AL 3 CUANDO JAVI SE DIGNE A HACER SU PARTE BIEN
		}
		break;
	case 6://menu+ia
		this->in.direct = "misimagenes/mIA.png";
		if (this->con.mousePos.y > 398 || this->con.mousePos.y < 365 || this->con.mousePos.x > 519 || this->con.mousePos.x > 584) {
			this->estado = 4;
		}
		if (controles::boton == GLUT_LEFT_BUTTON && controles::estado == GLUT_DOWN) {
			this->estado = 11;
		}
		break;
	case 7://menu+registro
		this->in.direct = "misimagenes/mreg.png";
		if (this->con.mousePos.y > 450 || this->con.mousePos.y < 418 || this->con.mousePos.x < 519 || this->con.mousePos.x > 827) {
			this->estado = 4;
		}
		if (controles::boton == GLUT_LEFT_BUTTON && controles::estado == GLUT_DOWN) {
			this->estado = 12;
		}
		break;
	case 8://menu+instrucciones
		this->in.direct = "misimagenes/mins.png";
		if (this->con.mousePos.y > 504 || this->con.mousePos.y < 472 || this->con.mousePos.x < 519 || this->con.mousePos.x > 1004) {
			this->estado = 4;
		}
		if (controles::boton == GLUT_LEFT_BUTTON && controles::estado == GLUT_DOWN) {
			this->estado = 13;
		}
		break;
	case 9://menu+exit
		this->in.direct = "misimagenes/mexit.png";
		if (this->con.mousePos.y > 559 || this->con.mousePos.y < 527 || this->con.mousePos.x < 519 || this->con.mousePos.x > 673) {
			this->estado = 4;
		}
		if (controles::boton == GLUT_LEFT_BUTTON && controles::estado == GLUT_DOWN) {
			this->estado = 19;
		}
		break;
	case 10: // carga de 1v1
		this->in.carga();
		this->in.direct = "misimagenes/c1v1.png";
		if (this->in.coor_y >= 8.25) {
			this->estado = 14;
			this->in.coor_y = -4.5f;
		}
		break;
	case 11: //carga de IA
		this->in.carga();
		this->in.direct = "misimagenes/cIA.png";
		if (this->in.coor_y >= 8.25) {
			this->estado = 15;
			this->in.coor_y = -4.5f;
		}
		break;
	case 12: //carga de registro
		this->in.carga();
		this->in.direct = "misimagenes/creg.png";
		if (this->in.coor_y >= 8.25) {
			this->estado = 18;
			this->in.coor_y = -4.5f;
		}
		break;
	case 13://carga de instrucciones
		this->in.carga();
		this->in.direct = "misimagenes/cins.png";
		if (this->in.coor_y>=8.25) {
			this->estado = 22;
			this->in.coor_y = -4.5f;
		}
		break;
	case 14://1v1 JUEGO
		//introducir logica del juego
		//if victoria-> CASE 23 
		this->estado = 16;
		//if derrota->CASE 24 this->estado = 17;
		break;
	case 15: //IA JUEGO
		//introducir logica del juego
		//if victoria-> CASE 23 this->estado = 16;
		//if derrota->CASE 24 
		this->estado = 17;
		break;
	case 16: //victoria
		this->in.direct = "misimagenes/victoria.png";
		if (time(NULL) > static_cast<long long>(this->t_0) + 5) {
			this->estado = 18;
			this->t_0 = time(NULL);
		}
		break;
	case 17: // derrota
		this->in.direct = "misimagenes/derrota.png";
		if (time(NULL) > static_cast<long long>(this->t_0) + 5) {
			this->estado = 18;
			this->t_0 = time(NULL);
		}
		break;
	case 18: //registro
		//this->in.direct = "misimagenes/.png";
		//METER PLANO NEGRO PARA Q VAYA APARECIENDO LAS LETRAS
		if (time(NULL) > static_cast<long long>(this->t_0) + 5) {
			this->estado = 4;
			this->t_0 = time(NULL);
		}
		break;
	case 19: // exit
		this->in.direct = "misimagenes/exitx.png";
		if (this->con.mousePos.y < 445 && this->con.mousePos.y >404 && this->con.mousePos.x > 717 && this->con.mousePos.x < 770) {
			this->estado = 20;
		}
		if (this->con.mousePos.y < 549 && this->con.mousePos.y >510 && this->con.mousePos.x > 705 && this->con.mousePos.x < 774) {
			this->estado = 21;
		}
		break;
	case 20: //exit si
		this->in.direct = "misimagenes/exitsi.png";
		if (this->con.mousePos.y > 445 || this->con.mousePos.y < 404 || this->con.mousePos.x < 717 || this->con.mousePos.x > 770) {
			this->estado = 19;
		}
		if (controles::boton == GLUT_LEFT_BUTTON && controles::estado == GLUT_DOWN) {
			this->estado = 0;
		}
		break;
	case 21: //exit no 
		this->in.direct = "misimagenes/exitno.png";
		if (this->con.mousePos.y > 549 || this->con.mousePos.y < 510 || this->con.mousePos.x < 705 || this->con.mousePos.x > 774) {
			this->estado = 19;
		}
		if (controles::boton == GLUT_LEFT_BUTTON && controles::estado == GLUT_DOWN) {
			this->estado = 4;
		}
		break;
	case 22: //instrucciones
		this->in.direct = "misimagenes/instrucciones.png";
		if (this->con.mousePos.y < 663 && this->con.mousePos.y >622 && this->con.mousePos.x > 1302 && this->con.mousePos.x < 1325) {
			if (controles::boton == GLUT_LEFT_BUTTON && controles::estado == GLUT_DOWN) {
				this->estado = 23;
			}
		}
		break;
	case 23: //instrucciones + peon
		this->in.direct = "misimagenes/ipeon.png";
		if (this->con.mousePos.y < 663 && this->con.mousePos.y >622 && this->con.mousePos.x > 201 && this->con.mousePos.x < 225) {
			if (controles::boton == GLUT_LEFT_BUTTON && controles::estado == GLUT_DOWN) {
				this->estado = 22;
			}
		}
		if (this->con.mousePos.y < 663 && this->con.mousePos.y >622 && this->con.mousePos.x > 1302 && this->con.mousePos.x < 1325) {
			if (controles::boton == GLUT_LEFT_BUTTON && controles::estado == GLUT_DOWN) {
				this->estado = 24;
			}
		}
		break;
	case 24: //instrucciones+ torre
		this->in.direct = "misimagenes/itorre.png";
		if (this->con.mousePos.y < 663 && this->con.mousePos.y >622 && this->con.mousePos.x > 201 && this->con.mousePos.x < 225) {
			if (controles::boton == GLUT_LEFT_BUTTON && controles::estado == GLUT_DOWN) {
				this->estado = 23;
			}
		}
		if (this->con.mousePos.y < 663 && this->con.mousePos.y >622 && this->con.mousePos.x > 1302 && this->con.mousePos.x < 1325) {
			if (controles::boton == GLUT_LEFT_BUTTON && controles::estado == GLUT_DOWN) {
				this->estado = 25;
			}
		}
		break;
	case 25: //instrucciones+caballo
		this->in.direct = "misimagenes/icaballo.png";
		if (this->con.mousePos.y < 663 && this->con.mousePos.y >622 && this->con.mousePos.x > 201 && this->con.mousePos.x < 225) {
			if (controles::boton == GLUT_LEFT_BUTTON && controles::estado == GLUT_DOWN) {
				this->estado = 24;
			}
		}
		if (this->con.mousePos.y < 663 && this->con.mousePos.y >622 && this->con.mousePos.x > 1302 && this->con.mousePos.x < 1325) {
			if (controles::boton == GLUT_LEFT_BUTTON && controles::estado == GLUT_DOWN) {
				this->estado = 26;
			}
		}
		break;
	case 26: //instrucciones+alfil
		this->in.direct = "misimagenes/ialfil.png";
		if (this->con.mousePos.y < 663 && this->con.mousePos.y >622 && this->con.mousePos.x > 201 && this->con.mousePos.x < 225) {
			if (controles::boton == GLUT_LEFT_BUTTON && controles::estado == GLUT_DOWN) {
				this->estado = 25;
			}
		}
		if (this->con.mousePos.y < 663 && this->con.mousePos.y >622 && this->con.mousePos.x > 1302 && this->con.mousePos.x < 1325) {
			if (controles::boton == GLUT_LEFT_BUTTON && controles::estado == GLUT_DOWN) {
				this->estado = 27;
			}
		}
		break;
	case 27: //instrucciones+reina
		this->in.direct = "misimagenes/ireina.png";
		if (this->con.mousePos.y < 663 && this->con.mousePos.y >622 && this->con.mousePos.x > 201 && this->con.mousePos.x < 225) {
			if (controles::boton == GLUT_LEFT_BUTTON && controles::estado == GLUT_DOWN) {
				this->estado = 26;
			}
		}
		if (this->con.mousePos.y < 663 && this->con.mousePos.y >622 && this->con.mousePos.x > 1302 && this->con.mousePos.x < 1325) {
			if (controles::boton == GLUT_LEFT_BUTTON && controles::estado == GLUT_DOWN) {
				this->estado = 28;
			}
		}
		break;
	case 28: //instrucciones+rey
		this->in.direct = "misimagenes/irey.png";
		if (this->con.mousePos.y < 663 && this->con.mousePos.y >622 && this->con.mousePos.x > 201 && this->con.mousePos.x < 225) {
			if (controles::boton == GLUT_LEFT_BUTTON && controles::estado == GLUT_DOWN) {
				this->estado = 27;
			}
		}
		if (this->con.mousePos.y < 663 && this->con.mousePos.y >622 && this->con.mousePos.x > 1302 && this->con.mousePos.x < 1325) {
			if (controles::boton == GLUT_LEFT_BUTTON && controles::estado == GLUT_DOWN) {
				this->estado = 4;
			}
		}
		break;
	}
	this->in.draw();
	//NO BORRAR X EL AMOR DE DIOS
	//std::cout << this->con.mousePos.y << std::endl;
	//std::cout << controles::boton << "," << controles::estado << std::endl;
}

void Mundo::mueve()
{
	//
}

void Mundo::inicializa()
{
	this->x_ojo = 0;
	this->y_ojo = 0;
	this->z_ojo = 30;
}

void Mundo::tecla(unsigned char key)
{
	//
}