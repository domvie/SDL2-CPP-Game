#include "game.h"
#include <SDL2/SDL.h>
#include "texturemanager.h"
#include "gameobject.h"
#include "map.h"
#include "components.h"
#include "vector2d.h"
#include "collision.h"

//GameObject* player;
//GameObject* enemy;
Map* map;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

std::vector<ColliderComponent*> Game::colliders;

Manager manager;
auto& player(manager.addEntity());
auto& enemy(manager.addEntity());
auto& wall(manager.addEntity());
auto& tile0(manager.addEntity());
auto& tile1(manager.addEntity());
auto& tile2(manager.addEntity());

enum groupLabels : std::size_t
{
    groupMap,
    groupPlayers,
    groupEnemies,
    groupColliders
};

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

    Map::LoadMap("../GameTest/assets/p16x16.map", 16, 16);

    // 0 = water, 1 = dirt, 2 = grass
    /*tile0.addComponent<TileComponent>(200, 200, 32, 32, 0);
    tile1.addComponent<TileComponent>(250,250,32,32, 1);
    tile1.addComponent<ColliderComponent>("dirt");
    tile2.addComponent<TileComponent>(150,150,32,32,2);
    tile2.addComponent<ColliderComponent>("grass");*/

    player.addComponent<TransformComponent>(2);
    player.addComponent<SpriteComponent>("../GameTest/assets/player_anim.png", true);
    player.addComponent<KeyboardController>();
    player.addComponent<ColliderComponent>("player");
    player.addGroup(groupPlayers);

    enemy.addComponent<TransformComponent>();
    enemy.addComponent<SpriteComponent>("../GameTest/assets/GoblinKing_Walk_01.png");

    wall.addComponent<TransformComponent>(300.0f, 300.0f, 300, 20, 1);
    wall.addComponent<SpriteComponent>("../GameTest/assets/dirt.png");
    wall.addComponent<ColliderComponent>("wall");
    wall.addGroup(groupMap);
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
    //player->update();
    //enemy->update();
    manager.refresh();
    manager.update();

    for (auto cc : colliders)
    {

        Collision::AABB(player.getComponent<ColliderComponent>(), *cc);
        //player.getComponent<TransformComponent>().scale = 1;
        //player.getComponent<TransformComponent>().velocity * -1;
        //std::cout << "Wall hit! " << std::endl;

    }
/*    std::cout << player.getComponent<TransformComponent>().position.x << ", " <<
                 player.getComponent<TransformComponent>().position.y << std::endl;
*/

   /* if (player.getComponent<TransformComponent>().position.x > 100)
    {
        player.getComponent<SpriteComponent>().setTex("/media/dominic/data/dominic/Qt/projects/GameTest/assets/GoblinKing_Walk_01.png");
    }*/

}

auto& tiles(manager.getGroup(groupMap));
auto& players(manager.getGroup(groupPlayers));
auto& enemies(manager.getGroup(groupEnemies));
//auto& colliders(manager.getGroup(groupColliders));


void Game::render()
{
    SDL_RenderClear(renderer);
    //map->DrawMap();
    //manager.draw();
    //player->render();
    //enemy->render();
    for (auto& t : tiles)
    {
        t->draw();
    }
    for (auto& p : players)
    {
        p->draw();
    }
    for (auto& e : enemies)
    {
        e->draw();
    }

    SDL_RenderPresent(renderer);
}

void Game::clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "Game cleaned!" << std::endl;
}


void Game::AddTile(int id, int x, int y)
{
    auto& tile(manager.addEntity());
    tile.addComponent<TileComponent>(x, y, 32, 32, id);
    tile.addGroup(groupMap);
}
