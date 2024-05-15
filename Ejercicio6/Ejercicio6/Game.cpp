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
	sf::RectangleShape groundShape(sf::Vector2f(500.0f, 5.0f));
	groundShape.setFillColor(sf::Color::Red);
	groundShape.setPosition(0.0f, 95.0f);
	wnd->draw(groundShape);

	//"Canon"
	sf::RectangleShape canon(sf::Vector2f(10.0f, 10.0f));
	canon.setPosition(10.0f, 85.0f);
	canon.setFillColor(sf::Color::Blue);
	wnd->draw(canon);

	for (size_t i = 0; i < ballList.size(); ++i) {
		Ball ball = ballList[i];
		ball.UpdateShapePosition();
		wnd->draw(ball.ball);
	}
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
			case Event::MouseButtonPressed:
				if (evt.key.code == Mouse::Button::Left)
				{
					Vector2i mousePos = Mouse::getPosition(*wnd);
					Vector2f worldMousePos = wnd->mapPixelToCoords(mousePos);

					Ball* ball = new Ball(*phyWorld);
					b2Vec2 direction = b2Vec2(worldMousePos.x - ball->ballBody->GetPosition().x, worldMousePos.y - ball->ballBody->GetPosition().y);
					direction.Normalize();
					ball->ballBody->ApplyLinearImpulseToCenter(b2Vec2(direction.x * 200.0f, direction.y * 200.0f), true);
					ballList.push_back(*ball);
				}
				break;		
		}
	}
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

	// Creamos el renderer de debug y le seteamos las banderas para que dibuje TODO
	debugRender = new SFMLRenderer(wnd);
	debugRender->SetFlags(UINT_MAX);
	phyWorld->SetDebugDraw(debugRender);

	//Fisicas del suelo
	b2Body* groundBody = Box2DHelper::CreateRectangularStaticBody(phyWorld, 100.0f, 10.0f);
	groundBody->SetTransform(b2Vec2(50.0f, 100.0f), 0.0f);
	
}

Game::~Game(void)
{ }