#include "Game.h"
#include "Box2DHelper.h"
#include <iostream>

using namespace sf;

Game::Game(int ancho, int alto, std::string titulo)
{
	wnd = new RenderWindow(VideoMode(ancho, alto), titulo);
	wnd->setVisible(true);
	fps = 60;
	wnd->setFramerateLimit(fps);
	frameTime = 1.0f / fps;
	SetZoom();
	InitPhysics();
}

void Game::Loop()
{
	while(wnd->isOpen())
	{
		wnd->clear(clearColor);
		DoEvents();
		CheckCollitions();
		UpdatePhysics();
		DrawGame();
		wnd->display();
	}
}

void Game::UpdatePhysics()
{
	phyWorld->Step(frameTime, 8, 8);
	phyWorld->ClearForces();
	phyWorld->DebugDraw();
}

void Game::DrawGame()
{ 
	// Dibujamos el suelo
	sf::RectangleShape groundShape(sf::Vector2f(500, 5));
	groundShape.setFillColor(sf::Color::Red);
	groundShape.setPosition(0, 95);
	wnd->draw(groundShape);

	// Dibujamos el cuerpo de control (rectangulo)
	sf::RectangleShape controlShape(Vector2f(10,10));
	controlShape.setFillColor(sf::Color::Magenta);
	controlShape.setPosition(controlBody->GetPosition().x - 5, controlBody->GetPosition().y - 5);
	wnd->draw(controlShape);
}

void Game::DoEvents()
{
	Event evt;
	while(wnd->pollEvent(evt))
	{
		switch(evt.type)
		{
			case Event::Closed:
				wnd->close();
				break;
		}
	}

	// Movemos el cuerpo
	controlBody->SetAwake(true);
	if (Keyboard::isKeyPressed(Keyboard::Left))
		controlBody->ApplyForceToCenter(b2Vec2(-1000.0f, 0), true);
	if (Keyboard::isKeyPressed(Keyboard::Right))
		controlBody->ApplyForceToCenter(b2Vec2(1000.0f, 0), true);
}

void Game::CheckCollitions()
{
	// Veremos mas adelante
}

// Definimos el area del mundo que veremos en nuestro juego
// Box2D tiene problemas para simular magnitudes muy grandes
void Game::SetZoom()
{
	View camara;
	// Posicion del view
	camara.setSize(100.0f, 100.0f); //Aqui podemos ver que no es la misma relacion de aspecto por lo que podriamos hacer 100*600/800 para obtener una relacion de aspecto igual a la del window
	camara.setCenter(50.0f, 50.0f);
	wnd->setView(camara); //asignamos la camara
}

void Game::InitPhysics()
{
	// Inicializamos el mundo con la gravedad por defecto
	phyWorld = new b2World(b2Vec2(0.0f, 9.8f));

	//MyContactListener* l= new MyContactListener();
	//phyWorld->SetContactListener(l);
	// Creamos el renderer de debug y le seteamos las banderas para que dibuje TODO
	debugRender = new SFMLRenderer(wnd);
	debugRender->SetFlags(UINT_MAX);
	phyWorld->SetDebugDraw(debugRender);

	// Creamos un piso y paredes
	b2Body* groundBody = Box2DHelper::CreateRectangularStaticBody(phyWorld, 100, 10);
	groundBody->SetTransform(b2Vec2(50.0f, 100.0f), 0.0f);

	
	controlBody= Box2DHelper::CreateRectangularDynamicBody(phyWorld, 10, 10, 0.8f, 0.5f, 0.3f);
	controlBody->SetTransform(b2Vec2(50.0f, 50.0f), 0.0f);
	groundBody->GetFixtureList()->SetFriction(0.5);//Agregamos rozamiento
}

Game::~Game(void)
{ }