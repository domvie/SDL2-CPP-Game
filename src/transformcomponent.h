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
        position.x = 0.0f;
        position.y = 0.0f;
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

    /*int x() { return xpos; }
    int y() { return ypos; }
    void x(int x) { xpos = x; }
    void y(int y) { ypos = y; }
*/
    void init() override
    {
        velocity.Zero();
    }

    void update() override
    {
        position.x += velocity.x * speed;
        position.y += velocity.y * speed;
    }

    /*void setPos(int x, int y)
    {
        xpos = x;
        ypos = y;
    }*/

};


#endif // TRANSFORMCOMPONENTS_HPP
