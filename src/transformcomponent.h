#pragma once

#ifndef TRANSFORMCOMPONENTS_HPP
#define TRANSFORMCOMPONENTS_HPP
#include "components.h"
#include "vector2d.h"

class TransformComponent : public Component
{
public:

    Vector2D position;


    TransformComponent()
    {
        position.x = 0.0f;
        position.y = 0.0f;
    }

    TransformComponent(float x, float y)
    {
        position.x = x;
        position.y = y;
    }

    /*int x() { return xpos; }
    int y() { return ypos; }
    void x(int x) { xpos = x; }
    void y(int y) { ypos = y; }
*/
    /*void init() override
    {
        xpos = 0;
        ypos = 0;
    }*/

    void update() override
    {
        /*
        xpos++;
        ypos++;*/
    }

    /*void setPos(int x, int y)
    {
        xpos = x;
        ypos = y;
    }*/

};


#endif // TRANSFORMCOMPONENTS_HPP
