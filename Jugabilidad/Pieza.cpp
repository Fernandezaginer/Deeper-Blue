
#include "Pieza.h"

tablero_info_t pieza_t::get_mov_permitidos(pieza_t a, pieza_t** tab)
{

	// Inicializar matriz de movimientos permitidos:
	tablero_info_t matriz;
	for (int i = 0; i < ROW_SIZE; i++) {
		for (int j = 0; j < COL_SIZE; i++) {
			matriz.TAB[i][j] = NO_PERMITIDO;
		}
	}


	if (a.getForma() == PEON) {       // Leo
		
	}

	if (a.getForma() == CABALLO) {   // Leo

	}

	if (a.getForma() == ALFIL) {     // Leo

	}

	if (a.getForma() == TORRE) {     // Andr�s

	}

	if (a.getForma() == DAMA) {      // Andr�s

	}

	if (a.getForma() == REY) {      // Andr�s

	}


	return matriz;
}