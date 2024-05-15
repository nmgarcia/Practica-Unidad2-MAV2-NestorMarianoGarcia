#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "SFMLRenderer.h"
#include "Ball.h"
#include <list>

using namespace sf;
using namespace std;

class Game
{
private:
	// Propiedades de la ventana
	int alto;
	int ancho;
	RenderWindow *wnd;
	Color clearColor;

	// Objetos de box2d
	b2World *phyWorld;
	SFMLRenderer *debugRender;

	//tiempo de frame
	float frameTime;
	int fps;

	// Cuerpo de box2d
	b2Body* groundBody;
	b2Body* controlBody;

	vector<Ball> ballList;

public:

	// Constructores, destructores e inicializadores
	Game(int ancho, int alto,std::string titulo);
	void CheckCollitions();
	void CreateEnemy(int x, int y);
	~Game(void);
	void InitPhysics();

	// Main game loop
	void Loop();
	void DrawGame();
	void UpdatePhysics();
	void DoEvents();
	void SetZoom();
};

