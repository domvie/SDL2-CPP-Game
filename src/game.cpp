#include "game.h"
#include <SDL2/SDL.h>
#include "texturemanager.h"
#include "components.h"
#include "vector2d.h"
#include "collision.h"

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;
SDL_Rect Game::camera = {0,0,800,640};

std::vector<ColliderComponent*> Game::colliders;

bool Game::isRunning = false;

Manager manager;
auto& player(manager.addEntity());
auto& wall(manager.addEntity());
auto& block(manager.addEntity());
auto& wall2(manager.addEntity());

Game::Game()
{

}

Game::~Game()
{

}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
    int flags = 0;
    if(fullscreen == true)
    {
        flags = SDL_WINDOW_FULLSCREEN_DESKTOP;
    }
    if(SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        std::cout << "Subsystems initialized!" << std::endl;
        window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);

        if(window)
        {
            std::cout << "Window created!" << std::endl;
        }

        renderer = SDL_CreateRenderer(window, -1, 0);
        if(renderer)
        {
            SDL_SetRenderDrawColor(renderer, 255,255,255,255);

            std::cout << "Renderer created!" << std::endl;
        }

        isRunning = true;
    }
    else {
        isRunning = false;
    }

    player.addComponent<TransformComponent>(350,270,37,50,2);
    player.addComponent<SpriteComponent>("../GameTest/assets/adventurer.png", true);
    player.addComponent<KeyboardController>();
    player.addComponent<ColliderComponent>("player");

    wall.addComponent<TransformComponent>(300.0f, 300.0f, 300, 20, 1);
    wall.addComponent<SpriteComponent>("../GameTest/assets/dirt.png");
    wall.addComponent<ColliderComponent>("wall");

    block.addComponent<TransformComponent>(100.0f, 100.0f, 200, 200, 1);
    block.addComponent<SpriteComponent>("../GameTest/assets/dirt.png");
    block.addComponent<ColliderComponent>("block");

    wall2.addComponent<TransformComponent>(500.0f, 200.0f, 20, 300, 1);
    wall2.addComponent<SpriteComponent>("../GameTest/assets/dirt.png");
    wall2.addComponent<ColliderComponent>("wall2");
}

void Game::handleEvents()
{
    SDL_PollEvent(&event);
    switch(event.type)
    {
        case SDL_QUIT:
            isRunning = false;
        break;
    }
}

void Game::update()
{
    manager.refresh();
    manager.update();

    for (auto cc : colliders)
    {

        if(Collision::AABB(player.getComponent<ColliderComponent>(), *cc))
        {
            player.getComponent<TransformComponent>().velocity * -1;
        }

    }
}

void Game::render()
{
    SDL_RenderClear(renderer);
    manager.draw();
    SDL_RenderPresent(renderer);
}

void Game::clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "Game cleaned!" << std::endl;
}




