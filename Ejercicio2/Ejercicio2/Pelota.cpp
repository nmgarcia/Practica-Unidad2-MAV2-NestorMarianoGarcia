#include "Pelota.h"

Pelota::Pelota(b2World* _world, RenderWindow* _wnd)
{
	// Guardamos puntero a ventana para dibujar luego
	wnd = _wnd;
	_image = new Texture();
	_image->loadFromFile("pelota.jpg");
	// Cargamos el sprite
	_sprite = new Sprite(*_image);

	// Definimos el body y lo creamos
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(100.0f, 0.0f);
	_body = _world->CreateBody(&bodyDef);

	// Creamos su figura de colisión
	// en este caso suponemos que la figura de
	// colision es una caja cuadrada
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(20.0f, 20.0f);

	// Creamos el fixture, le seteamos
	// la figura de colision
	// y agregamos el fixture al body
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 10.0f;
	fixtureDef.friction = 0.3f;
	fixtureDef.restitution = 1.0f;
	_body->CreateFixture(&fixtureDef);
}

// Metodo que posiciona el sprites
// segun la posicion del body
void Pelota::ActualizarPosiciones()
{
	b2Vec2 pos = _body->GetPosition();
	_sprite->setPosition(pos.x, pos.y);
}

// Metodo que dibuja el sprite
void Pelota::Dibujar()
{
	wnd->draw(*_sprite);
}
