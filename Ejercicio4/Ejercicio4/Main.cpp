#include "Game.h"
#include <tchar.h>

using namespace sf;

int _tmain(int argc, _TCHAR* argv[])
{
	Game *Juego;
	Juego = new Game(800, 600, "Ejercicio 1 - Unidad 2 - MAVII");
	Juego->Loop();

	return 0;
}