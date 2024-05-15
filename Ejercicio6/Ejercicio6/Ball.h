#pragma once
#include "Box2DHelper.h"
#include <SFML\Graphics.hpp>

using namespace sf;
class Ball: public Box2DHelper {

public:
    CircleShape ball;
    b2Body* ballBody;
    Ball(b2World& pyworld);
    void UpdateShapePosition();
};

