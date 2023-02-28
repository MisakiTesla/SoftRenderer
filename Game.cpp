//
// Created by 61923 on 2023/2/28.
//

#include <SDL_log.h>
#include <SDL.h>
#include "Game.h"
void Game::Loop()
{
    while (isRunning)
    {
        Event();
        Update();
        Draw();
    }
}

bool Game::Initialize() {
    //初始化
    if(SDL_Init(SDL_INIT_VIDEO) != 0){

        SDL_Log("SDL_Init:%d",SDL_GetError());
        return false;
    }

    SDL_Window *window = SDL_CreateWindow("SDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600,
                                          SDL_WINDOW_SHOWN);
    if (!window) {
        SDL_Log("SDL_Init:%d",SDL_GetError());
        return false;
    }

    isRunning = true;
    return true;
}

void Game::Shutdown() {
    SDL_Log("quit");
    SDL_DestroyWindow(_window);
    SDL_Quit();
}

void Game::Event() {
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

void Game::Update() {

}

void Game::Draw() {

}

Game::Game() {

}
