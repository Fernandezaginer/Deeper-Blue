#include "freeglut.h"
#include <math.h>
#include <iostream>
#include <stdlib.h>
#include <ctime>
#include "Controles.h"
#include "ETSIDI.h"
#include "Inicio.h"
#include "Pantalla.h"
#include "Interfaz.h"

using namespace std;

Interfaz::Interfaz() {
	this->x_ojo=0;
	this->y_ojo=0;
	this->z_ojo=0;
	this->estado = -2;
	this->t_0 = time(NULL);
	this->pan = pantalla();
	this->in = inicio();
	this->con = controles();
}

void Interfaz::rotarOjo()
{
	float dist = sqrt(this->x_ojo * this->x_ojo + this->z_ojo * this->z_ojo);
	float ang = atan2(this->z_ojo, this->x_ojo);
	ang += 0.05f;
	x_ojo = dist * cosf(ang);
	z_ojo = dist * sinf(ang);
}
void Interfaz::dibuja()
{

	gluLookAt(this->x_ojo, this->y_ojo, this->z_ojo,  // posicion del ojo
		0.0, this->y_ojo, 0.0,      // hacia que punto mira  (0,0,0) 
		0.0, 1.0, 0.0);      // definimos hacia arriba (eje Y)    
	

	//aqui es donde hay que poner el codigo de dibujo
	this->con.coger_pos();
	this->pan.dibuja();
	

	
	switch (this->estado)
	{
	case -2:
		this->in.direct = "misimagenes/xxx.png";
		if (time(NULL) > static_cast<long long>(this->t_0) + 5) {
			this->estado = -1;
			this->t_0 = time(NULL);
		}
		break;
	case -1:
		this->in.direct = "misimagenes/inicial.png";
		if (time(NULL) > static_cast<long long>(this->t_0) + 4) {
			this->estado = 0;
			this->t_0 = time(NULL);
		}
		break;
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
		if (time(NULL) > static_cast<long long>(this->t_0) + 1) {
			if (this->con.mousePos.y > 650 || this->con.mousePos.y < 606 || this->con.mousePos.x < 646 || this->con.mousePos.x > 863) {
				this->estado = 1;
			}
			if (controles::boton == GLUT_LEFT_BUTTON && controles::estado == GLUT_UP) {
				this->estado = 3;
			}
		}
		break;
	case 3://usuario 1
		this->in.direct = "misimagenes/jug1.png";
		//ETSIDI::setTextColor(1, 1, 0);
		//ETSIDI::setFont("fuentes/Bitwise.ttf", 24);
		//ETSIDI::printxy("texto", 0, 0);
		if (time(NULL) > static_cast<long long>(this->t_0) + 2) {//enter
			this->estado = 4;
			this->t_0 = time(NULL);

			/*
			hacer clase aparte para escribir todo esto --->retocar
			void output(int x, int y, float r, float g, float b, int font, char *string)
			{
				glColor3f( r, g, b );
				glRasterPos2f(x, y);
				int len, i;
				len = (int)strlen(string);
				for (i = 0; i < len; i++) {
				glutBitmapCharacter(font, string[i]);
				}
			}*/
		}
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
			this->estado = 10;
		}
		break;
	case 6://menu+ia
		this->in.direct = "misimagenes/mIA.png";
		if (this->con.mousePos.y > 398 || this->con.mousePos.y < 365 || this->con.mousePos.x < 519 || this->con.mousePos.x > 584) {
			this->estado = 4;
		}
		if (controles::boton == GLUT_LEFT_BUTTON && controles::estado == GLUT_DOWN) {
			this->estado = 12;
		}
		break;
	case 7://menu+registro
		this->in.direct = "misimagenes/mreg.png";
		if (this->con.mousePos.y > 450 || this->con.mousePos.y < 418 || this->con.mousePos.x < 519 || this->con.mousePos.x > 827) {
			this->estado = 4;
		}
		if (controles::boton == GLUT_LEFT_BUTTON && controles::estado == GLUT_DOWN) {
			this->estado = 13;
		}
		break;
	case 8://menu+instrucciones
		this->in.direct = "misimagenes/mins.png";
		if (this->con.mousePos.y > 504 || this->con.mousePos.y < 472 || this->con.mousePos.x < 519 || this->con.mousePos.x > 1004) {
			this->estado = 4;
		}
		if (controles::boton == GLUT_LEFT_BUTTON && controles::estado == GLUT_DOWN) {
			this->estado = 14;
		}
		break;
	case 9://menu+exit
		this->in.direct = "misimagenes/mexit.png";
		if (this->con.mousePos.y > 559 || this->con.mousePos.y < 527 || this->con.mousePos.x < 519 || this->con.mousePos.x > 673) {
			this->estado = 4;
		}
		if (controles::boton == GLUT_LEFT_BUTTON && controles::estado == GLUT_DOWN) {
			this->estado = 21;
		}
		break;
	case 10: //usuario 2
		this->in.direct = "misimagenes/jug2.png";
		if (time(NULL) > static_cast<long long>(this->t_0) + 1) { //cambiar por enter
			this->estado = 11;
			this->t_0 = time(NULL);
		}
		break;
	case 11: // carga de 1v1
		this->in.carga();
		this->in.direct = "misimagenes/c1v1.png";
		if (this->in.coor_y >= 8.25) {
			this->estado = 15;
			this->in.coor_y = -4.5f;
		}
		break;
	case 12: //carga de IA
		this->in.carga();
		this->in.direct = "misimagenes/cIA.png";
		if (this->in.coor_y >= 8.25) {
			this->estado = 16;
			this->in.coor_y = -4.5f;
		}
		break;
	case 13: //carga de registro
		this->in.carga();
		this->in.direct = "misimagenes/creg.png";
		if (this->in.coor_y >= 8.25) {
			this->estado = 19;
			this->in.coor_y = -4.5f;
		}
		break;
	case 14://carga de instrucciones
		this->in.carga();
		this->in.direct = "misimagenes/cins.png";
		if (this->in.coor_y >= 8.25) {
			this->estado = 24;
			this->in.coor_y = -4.5f;
		}
		break;
	case 15://1v1 JUEGO
		//introducir logica del juego
		//if victoria-> CASE 17 
		this->estado = 17;
		//if derrota->CASE 18 this->estado = 18;
		//if tablas->CASE 19 this->estado = 19;
		this->t_0 = time(NULL);
		break;
	case 16: //IA JUEGO
		//introducir logica del juego
		//if victoria-> CASE 17 this->estado = 17;
		//if derrota->CASE 18 
		//this->estado = 18;
		//if tablas->CASE 19 
		this->estado = 19;
		this->t_0 = time(NULL);
		break;
	case 17: //victoria
		this->in.direct = "misimagenes/victoria.png";
		if (time(NULL) > static_cast<long long>(this->t_0) + 10) {
			this->estado = 20;
			this->t_0 = time(NULL);
		}
		break;
	case 18: // derrota
		this->in.direct = "misimagenes/derrota.png";
		if (time(NULL) > static_cast<long long>(this->t_0) + 10) {
			this->estado = 20;
			this->t_0 = time(NULL);
		}
		break;
	case 19: //tablas
		this->in.direct = "misimagenes/tablas.png";
		if (time(NULL) > static_cast<long long>(this->t_0) + 10) {
			this->estado = 20;
			this->t_0 = time(NULL);
		}
		break;

	case 20: //registro
		this->in.direct = "misimagenes/reg.png";
		
		if (time(NULL) > static_cast<long long>(this->t_0) + 10) {
			this->estado = 4;
			this->t_0 = time(NULL);
		}
		break;
	case 21: // exit
		this->in.direct = "misimagenes/exitx.png";
		if (this->con.mousePos.y < 445 && this->con.mousePos.y >404 && this->con.mousePos.x > 717 && this->con.mousePos.x < 770) {
			this->estado = 22;
		}
		if (this->con.mousePos.y < 549 && this->con.mousePos.y >510 && this->con.mousePos.x > 705 && this->con.mousePos.x < 774) {
			this->estado = 23;
		}
		break;
	case 22: //exit si
		this->in.direct = "misimagenes/exitsi.png";
		if (this->con.mousePos.y > 445 || this->con.mousePos.y < 404 || this->con.mousePos.x < 717 || this->con.mousePos.x > 770) {
			this->estado = 21;
		}
		if (controles::boton == GLUT_LEFT_BUTTON && controles::estado == GLUT_DOWN) {
			this->estado = 0;
		}
		break;
	case 23: //exit no 
		this->in.direct = "misimagenes/exitno.png";
		if (this->con.mousePos.y > 549 || this->con.mousePos.y < 510 || this->con.mousePos.x < 705 || this->con.mousePos.x > 774) {
			this->estado = 21;
		}
		if (controles::boton == GLUT_LEFT_BUTTON && controles::estado == GLUT_DOWN) {
			this->estado = 4;
		}
		break;
	case 24: //instrucciones objetivo
		this->in.direct = "misimagenes/i_obj.png";
		if (time(NULL) > static_cast<long long>(this->t_0) + 1) {
			if (this->con.mousePos.y < 716 && this->con.mousePos.y >656 && this->con.mousePos.x > 182 && this->con.mousePos.x < 220) {
				if (controles::boton == GLUT_LEFT_BUTTON && controles::estado == GLUT_DOWN) {
					this->estado = 4;
					this->t_0 = time(NULL);
				}
			}
			if (this->con.mousePos.y < 716 && this->con.mousePos.y >656 && this->con.mousePos.x > 1324 && this->con.mousePos.x < 1366) {
				if (controles::boton == GLUT_LEFT_BUTTON && controles::estado == GLUT_DOWN) {
					this->estado = 25;
					this->t_0 = time(NULL);
				}
			}
		}
		break;
	case 25: //instrucciones + posición inicial del tablero
		this->in.direct = "misimagenes/i_pos.png";
		if (time(NULL) > static_cast<long long>(this->t_0) + 1) {
			if (this->con.mousePos.y < 716 && this->con.mousePos.y >656 && this->con.mousePos.x > 182 && this->con.mousePos.x < 220) {
				if (controles::boton == GLUT_LEFT_BUTTON && controles::estado == GLUT_DOWN) {
					this->estado = 24;
					this->t_0 = time(NULL);
				}
			}
			if (this->con.mousePos.y < 716 && this->con.mousePos.y >656 && this->con.mousePos.x > 1324 && this->con.mousePos.x < 1366) {
				if (controles::boton == GLUT_LEFT_BUTTON && controles::estado == GLUT_DOWN) {
					this->estado = 26;
					this->t_0 = time(NULL);
				}
			}
		}
		break;
	case 26: //instrucciones + peon

		this->in.direct = "misimagenes/i_peon1.png";
		if ( time(NULL) > static_cast<long long>(this->t_0) + 1){
			if (this->con.mousePos.y < 627 && this->con.mousePos.y >335 && this->con.mousePos.x > 396 && this->con.mousePos.x < 728) {
				this->in.direct = "misimagenes/i_peon2.png";
			}
			if (this->con.mousePos.y < 562 && this->con.mousePos.y >481 && this->con.mousePos.x > 783 && this->con.mousePos.x < 1240) {
				this->in.direct = "misimagenes/i_peon3.png";
			}
			if (this->con.mousePos.y < 716 && this->con.mousePos.y >656 && this->con.mousePos.x > 182 && this->con.mousePos.x < 220) {
				if (controles::boton == GLUT_LEFT_BUTTON && controles::estado == GLUT_DOWN) {
					this->estado = 25;
					this->t_0 = time(NULL);
				}
			}
			if (this->con.mousePos.y < 716 && this->con.mousePos.y >656 && this->con.mousePos.x > 1324 && this->con.mousePos.x < 1366) {
				if (controles::boton == GLUT_LEFT_BUTTON && controles::estado == GLUT_DOWN) {
					this->estado = 27;
					this->t_0 = time(NULL);
				}
			}
		}
		break;
	case 27: //instrucciones+ torre
		this->in.direct = "misimagenes/i_torre1.png";
		if (time(NULL) > static_cast<long long>(this->t_0) + 1) {
			if (this->con.mousePos.y < 627 && this->con.mousePos.y >335 && this->con.mousePos.x > 396 && this->con.mousePos.x < 728) {
				this->in.direct = "misimagenes/i_torre2.png";
			}
			if (this->con.mousePos.y < 716 && this->con.mousePos.y >656 && this->con.mousePos.x > 182 && this->con.mousePos.x < 220) {
				if (controles::boton == GLUT_LEFT_BUTTON && controles::estado == GLUT_DOWN) {
					this->estado = 26;
					this->t_0 = time(NULL);
				}
			}
			if (this->con.mousePos.y < 716 && this->con.mousePos.y >656 && this->con.mousePos.x > 1324 && this->con.mousePos.x < 1366) {
				if (controles::boton == GLUT_LEFT_BUTTON && controles::estado == GLUT_DOWN) {
					this->estado = 28;
					this->t_0 = time(NULL);
				}
			}
		}
		break;
	case 28: //instrucciones+caballo
		this->in.direct = "misimagenes/i_caballo1.png";
		if (time(NULL) > static_cast<long long>(this->t_0) + 1) {
			if (this->con.mousePos.y < 627 && this->con.mousePos.y >335 && this->con.mousePos.x > 396 && this->con.mousePos.x < 728) {
				this->in.direct = "misimagenes/i_caballo2.png";
			}
			if (this->con.mousePos.y < 716 && this->con.mousePos.y >656 && this->con.mousePos.x > 182 && this->con.mousePos.x < 220) {
				if (controles::boton == GLUT_LEFT_BUTTON && controles::estado == GLUT_DOWN) {
					this->estado = 27;
					this->t_0 = time(NULL);
				}
			}
			if (this->con.mousePos.y < 716 && this->con.mousePos.y >656 && this->con.mousePos.x > 1324 && this->con.mousePos.x < 1366) {
				if (controles::boton == GLUT_LEFT_BUTTON && controles::estado == GLUT_DOWN) {
					this->estado = 29;
					this->t_0 = time(NULL);
				}
			}
		}
		break;
	case 29: //instrucciones+alfil
		this->in.direct = "misimagenes/i_alfil1.png";
		if (time(NULL) > static_cast<long long>(this->t_0) + 1) {
			if (this->con.mousePos.y < 627 && this->con.mousePos.y >335 && this->con.mousePos.x > 396 && this->con.mousePos.x < 728) {
				this->in.direct = "misimagenes/i_alfil2.png";
			}
			if (this->con.mousePos.y < 716 && this->con.mousePos.y >656 && this->con.mousePos.x > 182 && this->con.mousePos.x < 220) {
				if (controles::boton == GLUT_LEFT_BUTTON && controles::estado == GLUT_DOWN) {
					this->estado = 28;
					this->t_0 = time(NULL);
				}
			}
			if (this->con.mousePos.y < 716 && this->con.mousePos.y >656 && this->con.mousePos.x > 1324 && this->con.mousePos.x < 1366) {
				if (controles::boton == GLUT_LEFT_BUTTON && controles::estado == GLUT_DOWN) {
					this->estado = 30;
					this->t_0 = time(NULL);
				}
			}
		}
		break;
	case 30: //instrucciones+reina
		this->in.direct = "misimagenes/i_reina1.png";
		if (time(NULL) > static_cast<long long>(this->t_0) + 1) {
			if (this->con.mousePos.y < 627 && this->con.mousePos.y >335 && this->con.mousePos.x > 396 && this->con.mousePos.x < 728) {
				this->in.direct = "misimagenes/i_reina2.png";
			}
			if (this->con.mousePos.y < 716 && this->con.mousePos.y >656 && this->con.mousePos.x > 182 && this->con.mousePos.x < 220) {
				if (controles::boton == GLUT_LEFT_BUTTON && controles::estado == GLUT_DOWN) {
					this->estado = 28;
					this->t_0 = time(NULL);
				}
			}
			if (this->con.mousePos.y < 716 && this->con.mousePos.y >656 && this->con.mousePos.x > 1324 && this->con.mousePos.x < 1366) {
				if (controles::boton == GLUT_LEFT_BUTTON && controles::estado == GLUT_DOWN) {
					this->estado = 31;
					this->t_0 = time(NULL);
				}
			}
		}
		break;
	case 31: //instrucciones+rey
		this->in.direct = "misimagenes/i_rey1.png";
		if (time(NULL) > static_cast<long long>(this->t_0) + 1) {
			if (this->con.mousePos.y < 627 && this->con.mousePos.y >335 && this->con.mousePos.x > 396 && this->con.mousePos.x < 728) {
				this->in.direct = "misimagenes/i_rey2.png";
			}
			if (this->con.mousePos.y < 716 && this->con.mousePos.y >656 && this->con.mousePos.x > 182 && this->con.mousePos.x < 220) {
				if (controles::boton == GLUT_LEFT_BUTTON && controles::estado == GLUT_DOWN) {
					this->estado = 30;
					this->t_0 = time(NULL);
				}
			}
			if (this->con.mousePos.y < 716 && this->con.mousePos.y >656 && this->con.mousePos.x > 1324 && this->con.mousePos.x < 1366) {
				if (controles::boton == GLUT_LEFT_BUTTON && controles::estado == GLUT_DOWN) {
					this->estado = 32;
					this->t_0 = time(NULL);
				}
			}
		}
		break;
	case 32: //instrucciones+movimientos especiales
		this->in.direct = "misimagenes/i_mov1.png";
		if (time(NULL) > static_cast<long long>(this->t_0) + 2) {
			this->in.direct = "misimagenes/i_mov1.1.png";
			if (this->con.mousePos.y < 716 && this->con.mousePos.y >656 && this->con.mousePos.x > 182 && this->con.mousePos.x < 220) {
				if (controles::boton == GLUT_LEFT_BUTTON && controles::estado == GLUT_DOWN) {
					this->estado = 31;
					this->t_0 = time(NULL);
				}
			}
			if (this->con.mousePos.y < 716 && this->con.mousePos.y >656 && this->con.mousePos.x > 1324 && this->con.mousePos.x < 1366) {
				if (controles::boton == GLUT_LEFT_BUTTON && controles::estado == GLUT_DOWN) {
					this->estado = 33;
					this->t_0 = time(NULL);
				}
			}
		}
		break;
	case 33: //instrucciones+movimientos especiales
		this->in.direct = "misimagenes/i_mov2.png";
		if (time(NULL) > static_cast<long long>(this->t_0) + 2) {
			this->in.direct = "misimagenes/i_mov2.1.png";
			if (time(NULL) > static_cast<long long>(this->t_0) + 4) {
				this->in.direct = "misimagenes/i_mov2.2.png";
				if (this->con.mousePos.y < 716 && this->con.mousePos.y >656 && this->con.mousePos.x > 182 && this->con.mousePos.x < 220) {
					if (controles::boton == GLUT_LEFT_BUTTON && controles::estado == GLUT_DOWN) {
						this->estado = 32;
						this->t_0 = time(NULL);
					}
				}
				if (this->con.mousePos.y < 716 && this->con.mousePos.y >656 && this->con.mousePos.x > 1324 && this->con.mousePos.x < 1366) {
					if (controles::boton == GLUT_LEFT_BUTTON && controles::estado == GLUT_DOWN) {
						this->estado = 34;
						this->t_0 = time(NULL);
					}
				}
			}
		}
		break;
	case 34: //instrucciones+movimientos especiales
		this->in.direct = "misimagenes/i_mov3.png";
		if (time(NULL) > static_cast<long long>(this->t_0) + 2) {
			this->in.direct = "misimagenes/i_mov3.1.png";
			if (this->con.mousePos.y < 716 && this->con.mousePos.y >656 && this->con.mousePos.x > 182 && this->con.mousePos.x < 220) {
				if (controles::boton == GLUT_LEFT_BUTTON && controles::estado == GLUT_DOWN) {
					this->estado = 33;
					this->t_0 = time(NULL);
				}
			}
			if (this->con.mousePos.y < 716 && this->con.mousePos.y >656 && this->con.mousePos.x > 1324 && this->con.mousePos.x < 1366) {
				if (controles::boton == GLUT_LEFT_BUTTON && controles::estado == GLUT_DOWN) {
					this->estado = 4;
					this->t_0 = time(NULL);
				}
			}
		}
		break;

	}
	this->in.draw();
	//NO BORRAR X EL AMOR DE DIOS
	//std::cout << this->con.mousePos.x << "  "<<this->con.mousePos.y << std::endl;
	//std::cout << controles::boton << "," << controles::estado << std::endl;
}

void Interfaz::mueve()
{
	//
}

void Interfaz::inicializa()
{
	this->x_ojo = 0;
	this->y_ojo = 0;
	this->z_ojo = 30;
}

void Interfaz::tecla(unsigned char key)
{
	//
	//string patata;
	//patata += key;
}