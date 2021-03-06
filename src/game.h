#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <iostream>
#include <SDL2/SDL_image.h>
#include <vector>

class ColliderComponent;

class Game
{
public:
    Game();
    ~Game();

    void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
    void handleEvents();
    void update();
    void render();
    void clean();
    bool running() { return isRunning; }

    static void AddTile(int srcX, int srcY, int xpos, int ypos);
    static SDL_Renderer *renderer;
    static SDL_Event event;
    static std::vector<ColliderComponent*> colliders;
    static bool isRunning;
    static SDL_Rect camera;


private:
    int cnt = 0;
    SDL_Window *window;
};

#endif // GAME_H
