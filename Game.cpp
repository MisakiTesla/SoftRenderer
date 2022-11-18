//
// Created by slei on 2022/11/18.
//

#include <SDL.h>
#include <string>
#include "Game.h"
Game::Game():
        window(nullptr),
        isRunning(true)
{

}

bool Game::Initialize()
{
    // SDL库初始化
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        SDL_Log("SDL库初始化失败: %s", SDL_GetError());
        return false;
    }

    // 窗口初始化
    window = SDL_CreateWindow("Dungeon", 400, 200, 600, 480, 0);
    if (!window)
    {
        SDL_Log("窗口初始化失败: %s", SDL_GetError());
        return false;
    }

    return true;
}

void Game::Loop()
{
    while (isRunning)
    {
        Uint64 start = SDL_GetPerformanceCounter();

        Event();
        Update();
        Draw();

        Uint64 end = SDL_GetPerformanceCounter();
        deltaTime = (end - start) / (float)SDL_GetPerformanceFrequency();

    }
}

void Game::Shutdown()
{
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Game::Event()
{
    SDL_Event event;
    // 如果事件队列中有未处理的事件，按顺序处理
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            // 退出事件，按下窗口的叉
            case SDL_QUIT:
                isRunning = false;
                break;
            default:
                break;
        }
    }
}

void Game::Update()
{
    SDL_Log(std::to_string(deltaTime).c_str());

}

void Game::Draw()
{
}