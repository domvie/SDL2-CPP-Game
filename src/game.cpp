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
SDL_Rect Game::camera = {0,0,800,640};

std::vector<ColliderComponent*> Game::colliders;

bool Game::isRunning = false;

Manager manager;
auto& player(manager.addEntity());
auto& enemy(manager.addEntity());
auto& wall(manager.addEntity());
auto& block(manager.addEntity());
auto& wall2(manager.addEntity());

auto& tile0(manager.addEntity());
auto& tile1(manager.addEntity());
auto& tile2(manager.addEntity());

const char* mapfile = "../GameTest/assets/terrain_ss.png";


/*enum groupLabels : std::size_t
{
    groupMap,
    groupPlayers,
    groupEnemies,
    groupColliders
};

auto& tiles(manager.getGroup(groupMap));
auto& players(manager.getGroup(groupPlayers));
auto& enemies(manager.getGroup(groupEnemies));
auto& colliders(manager.getGroup(groupColliders));
*/

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
    //map = new Map();

    //Map::LoadMap("../GameTest/assets/map.map", 25, 20);

    // 0 = water, 1 = dirt, 2 = grass
    /*tile0.addComponent<TileComponent>(200, 200, 32, 32, 0);
    tile1.addComponent<TileComponent>(250,250,32,32, 1);
    tile1.addComponent<ColliderComponent>("dirt");
    tile2.addComponent<TileComponent>(150,150,32,32,2);
    tile2.addComponent<ColliderComponent>("grass");*/

    player.addComponent<TransformComponent>(350,270,37,50,2);
    player.addComponent<SpriteComponent>("../GameTest/assets/adventurer.png", true);
    player.addComponent<KeyboardController>();
    player.addComponent<ColliderComponent>("player");
    //player.addGroup(groupPlayers);

    //enemy.addComponent<TransformComponent>();
    //enemy.addComponent<SpriteComponent>("../GameTest/assets/GoblinKing_Walk_01.png");

    wall.addComponent<TransformComponent>(300.0f, 300.0f, 300, 20, 1);
    block.addComponent<TransformComponent>(100.0f, 100.0f, 200, 200, 1);
    wall2.addComponent<TransformComponent>(500.0f, 200.0f, 20, 300, 1);

    wall.addComponent<SpriteComponent>("../GameTest/assets/dirt.png");
    wall.addComponent<ColliderComponent>("wall");
    block.addComponent<SpriteComponent>("../GameTest/assets/dirt.png");
    block.addComponent<ColliderComponent>("block");
    wall2.addComponent<SpriteComponent>("../GameTest/assets/dirt.png");
    wall2.addComponent<ColliderComponent>("wall2");

    //wall.addGroup(groupMap);
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

    //camera.x = player.getComponent<TransformComponent>().position.x - 400;
    //camera.y = player.getComponent<TransformComponent>().position.y - 320;

    /*if(camera.x < 0)
        camera.x = 0;
    if(camera.y < 0)
        camera.y = 0;
    if(camera.x > camera.w)
        camera.x = camera.w;
    if(camera.y > camera.h)
        camera.y = camera.h;*/

    Vector2D pVelocity = player.getComponent<TransformComponent>().velocity;
    int pSpeed = player.getComponent<TransformComponent>().speed;

    for (auto cc : colliders)
    {

        if(Collision::AABB(player.getComponent<ColliderComponent>(), *cc))
        {
            //player.getComponent<TransformComponent>().scale = 1;
            player.getComponent<TransformComponent>().velocity * -1;
            //std::cout << "Wall hit! " << std::endl;
        }


    }

   /* for (auto t : tiles)
    {
        t->getComponent<TileComponent>().destRect.x += -(pVelocity.x * pSpeed);
        t->getComponent<TileComponent>().destRect.y += -(pVelocity.y * pSpeed);
    }*/
/*    std::cout << player.getComponent<TransformComponent>().position.x << ", " <<
                 player.getComponent<TransformComponent>().position.y << std::endl;
*/

   /* if (player.getComponent<TransformComponent>().position.x > 100)
    {
        player.getComponent<SpriteComponent>().setTex("/media/dominic/data/dominic/Qt/projects/GameTest/assets/GoblinKing_Walk_01.png");
    }*/

}





void Game::render()
{
    SDL_RenderClear(renderer);
    //map->DrawMap();
    manager.draw();
    //player->render();
    //enemy->render();
    /*for (auto& t : tiles)
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
    }*/

    SDL_RenderPresent(renderer);
}

void Game::clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "Game cleaned!" << std::endl;
}


void Game::AddTile(int srcX, int srcY, int xpos, int ypos)
{
    auto& tile(manager.addEntity());
    tile.addComponent<TileComponent>(srcX, srcY, xpos, ypos, mapfile);
    //tile.addGroup(groupMap);
}
