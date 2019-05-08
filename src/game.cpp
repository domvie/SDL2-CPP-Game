#include "game.h"
#include <SDL2/SDL.h>
#include "texturemanager.h"
#include "gameobject.h"
#include "map.h"
#include "components.h"
#include "vector2d.h"

//GameObject* player;
//GameObject* enemy;
Map* map;

SDL_Renderer* Game::renderer = nullptr;

Manager manager;
auto& player(manager.addEntity());
auto& enemy(manager.addEntity());

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

    //player = new GameObject("../GameTest/assets/adventurer-idle-00.png", 0, 0);
    //enemy = new GameObject("../GameTest/assets/GoblinKing_Walk_01.png", 50, 50);
    map = new Map();

    player.addComponent<TransformComponent>();
    player.addComponent<SpriteComponent>("../GameTest/assets/adventurer-idle-00.png");
    enemy.addComponent<TransformComponent>();
    enemy.addComponent<SpriteComponent>("../GameTest/assets/GoblinKing_Walk_01.png");
}

void Game::handleEvents()
{
    SDL_Event event;
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
    //player->update();
    //enemy->update();
    manager.refresh();
    manager.update();
    player.getComponent<TransformComponent>().position.Add(Vector2D(2,0));
    std::cout << player.getComponent<TransformComponent>().position.x << ", " <<
                 player.getComponent<TransformComponent>().position.y << std::endl;


    if (player.getComponent<TransformComponent>().position.x > 100)
    {
        player.getComponent<SpriteComponent>().setTex("/media/dominic/data/dominic/Qt/projects/GameTest/assets/GoblinKing_Walk_01.png");
    }

}

void Game::render()
{
    SDL_RenderClear(renderer);
    map->DrawMap();
    manager.draw();
    //player->render();
    //enemy->render();
    SDL_RenderPresent(renderer);
}

void Game::clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "Game cleaned!" << std::endl;
}
