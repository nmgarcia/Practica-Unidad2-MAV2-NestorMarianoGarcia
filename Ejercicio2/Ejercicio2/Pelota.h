#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <Box2D/Box2D.h>

using namespace sf;

class Pelota
{
private:
	// Sprite y su imagen la para representaci�n gr�fica
	Sprite* _sprite;
	Texture* _image;
	RenderWindow* wnd;
	// Body para representaci�n f�sica
	b2Body* _body;
	//...
public:
	Pelota(b2World* _world, RenderWindow* _wnd);
	void ActualizarPosiciones();
	void Dibujar();
};