#pragma once
#ifndef TILECOMPONENT_H
#define TILECOMPONENT_H

#include "ecs.h"
#include "transformcomponent.h"
#include <SDL2/SDL.h>

class TileComponent : public Component
{
public:
    /*TransformComponent *transform;
    SpriteComponent *sprite;

    SDL_Rect tileRect;
    int tileID;
    char* path;*/

    SDL_Texture* texture;
    SDL_Rect srcRect, destRect;
    Vector2D position;

    TileComponent() = default;

    ~TileComponent() override
    {
        SDL_DestroyTexture(texture);
    }
    TileComponent(int srcX, int srcY, int xpos, int ypos, const char* path)
    {
        texture = TextureManager::LoadTexture(path);

        position.x = xpos;
        position.y = ypos;

        srcRect.x = srcX;
        srcRect.y = srcY;
        srcRect.w = srcRect.h = 32;

        destRect.x = xpos;
        destRect.y = ypos;
        destRect.w = destRect.h = 64;
    }

    void update() override
    {
        destRect.x = position.x; // - Game::camera.x;
        destRect.y = position.y; // - Game::camera.y;
    }

    void draw() override
    {
        TextureManager::Draw(texture, srcRect, destRect, SDL_FLIP_NONE);
    }

    /*TileComponent(int x, int y, int w, int h, int id)
    {
        tileRect.x = x;
        tileRect.y = y;
        tileRect.w = w;
        tileRect.h = h;
        tileID = id;

        switch(tileID)
        {
        case 0:
            path = "../GameTest/assets/water.png";
            break;
        case 1:
            path = "../GameTest/assets/dirt.png";
            break;
        case 2:
            path = "../GameTest/assets/grass.png";
            break;
        default:
            break;
        }
    }

    void init() override
    {
        entity->addComponent<TransformComponent>((float)tileRect.x, (float)tileRect.y, tileRect.w, tileRect.h, 1);
        transform = &entity->getComponent<TransformComponent>();

        entity->addComponent<SpriteComponent>(path);
        sprite = &entity->getComponent<SpriteComponent>();
    }*/
};

#endif // TILECOMPONENT_H
