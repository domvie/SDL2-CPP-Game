#pragma once

#ifndef TRANSFORMCOMPONENTS_HPP
#define TRANSFORMCOMPONENTS_HPP
#include "components.h"
#include "vector2d.h"

class TransformComponent : public Component
{
public:

    Vector2D position;
    Vector2D velocity;

    int speed = 3;

    int height = 32;
    int width = 32;
    int scale = 1;

    TransformComponent()
    {
        position.Zero();
    }

    TransformComponent(float x, float y)
    {
        position.Zero();
    }

    TransformComponent(int sc)
    {
        position.x = 350;
        position.y = 270;
        scale = sc;
    }
    TransformComponent(float x, float y, int h, int w, int sc)
    {
        position.x = x;
        position.y = y;
        height = h;
        width = w;
        scale = sc;
    }

    void init() override
    {
        velocity.Zero();
    }

    void update() override
    {
        position.x += velocity.x * speed;
        position.y += velocity.y * speed;
    }

};


#endif // TRANSFORMCOMPONENTS_HPP
