#include "Ball.h"

Ball::Ball(b2World& pyworld) {
    ball.setRadius(3);
    ball.setOrigin(3, 3);
    ball.setFillColor(sf::Color::Blue);

    ballBody = Box2DHelper::CreateCircularDynamicBody(&pyworld, 3, 0.2, 0.8, 0.3);
    ballBody->SetTransform(b2Vec2(15, 85), 0);
}

void Ball::UpdateShapePosition() {
    b2Vec2 position = ballBody->GetPosition();
    ball.setPosition(position.x, position.y);
}