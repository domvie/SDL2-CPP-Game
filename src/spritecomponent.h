#pragma once

#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H
#include "components.h"
#include "texturemanager.h"
#include <SDL2/SDL.h>

class SpriteComponent : public Component
{
private:

    TransformComponent *transform;
    SDL_Texture *texture;

    SDL_Rect srcRect, destRect;
    ~SpriteComponent() override
    {
        SDL_DestroyTexture(texture);
    }
public:

    SpriteComponent() = default;
    SpriteComponent(const char* path)
    {
        setTex(path);
    }

    void setTex(const char* path)
    {
        texture = TextureManager::LoadTexture(path);
    }
    void init() override
    {
        transform = &entity->getComponent<TransformComponent>();

        srcRect.x = srcRect.y = 0;
        srcRect.w = transform->width;
        srcRect.h = transform->height;

    }

    void update() override
    {
        destRect.x = static_cast<int>(transform->position.x);
        destRect.y = static_cast<int>(transform->position.y);
        destRect.w = transform->width * transform->scale;
        destRect.h = transform->height * transform->scale;
    }

    void draw() override
    {
       TextureManager::Draw(texture, srcRect, destRect);
    }

};

#endif // SPRITECOMPONENT_H
