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

    _window = SDL_CreateWindow("SDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600,
                                          SDL_WINDOW_SHOWN);
    if (!_window) {
        SDL_Log("SDL_Init:%d",SDL_GetError());
        return false;
    }

    // 最后一个参数为flag位，这里只用了SDL_RENDERER_ACCELERATED来使用硬件加速，
    // 假如想使用之前提到过的垂直同步也可以在这里用按位或运算符带上SDL_RENDERER_PRESENTVSYNC。
    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    CreateTexture();


    isRunning = true;
    return true;
}

void Game::CreateTexture() {
    int w = 256;
    int h = 256;

    _texture = SDL_CreateTexture(_renderer, SDL_PIXELFORMAT_RGBA32,
                                 SDL_TEXTUREACCESS_STREAMING, w,h);

    // 准备一幅800*600的红色RGB图像数据
    unsigned char *rgb(new unsigned char[w * h * 4]);        // 乘以4是因为像素格式已指定为ARGB888，单个像素点占4字节

    // 为上述图像数据赋值
    for (int j = 0; j < h; j++)
    {
        int lineR = j * w * 4;                                          // 每一行R分量的起始位置
        for (int i = 0; i < w * 4; i += 4)
        {
            rgb[lineR + i] = 128;                                                   // R
            rgb[lineR + i + 1] = 128;                                               // G
            rgb[lineR + i + 2] = 128;                                             // B
            rgb[lineR + i + 3] = 0;                                               // A
        }
    }

    // 5. 将内存中的RGB数据写入材质
    SDL_UpdateTexture(_texture, NULL, rgb, w * 4);


    //rect为NULL时更新整个texture
//    SDL_UpdateTexture(_texture, NULL, )
}

void Game::Shutdown() {
    SDL_Log("quit");
    SDL_DestroyRenderer(_renderer);
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
    SDL_Delay(10);
}

void Game::Draw() {
// 设置渲染器颜色（蓝）
    SDL_SetRenderDrawColor(_renderer, 0, 0, 255, 255);

    // 清除缓冲区
    SDL_RenderClear(_renderer);

//    //绘制其他东西的代码要写在SDL_RenderClear()语句和SDL_RenderPresent()语句之间

    DrawTexture(_texture);

    // 交换缓冲区
    SDL_RenderPresent(_renderer);
}

void Game::DrawTexture(SDL_Texture* texture, int posX, int posY) {
    // 截取原图片（这里是完整截取）
    int w,h;
    SDL_QueryTexture(texture, NULL, NULL, &w, &h);
//    SDL_Rect imageRect{ 0, 0, 256, 256 };
// 图片目的地
    SDL_Rect dstRect{ posX, posY, w, h };
// 将截取好的图片拷贝并填充至目的地的长方形中
//
    SDL_RenderCopy(_renderer, texture, NULL, &dstRect);
}

Game::Game() {

}
