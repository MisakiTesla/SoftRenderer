﻿//
// Created by 61923 on 2023/2/28.
//

using namespace std;
#include <SDL_log.h>
#include <SDL.h>
#include <cmath>
#include <algorithm>
#include "Game.h"
#include "Timer.h"

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

    width = 256;
    height = 256;

    CreateTexture(width, height);
    fpsUpdateInterval = 1.0f;
    fpsUpdateTimer = 0;


    isRunning = true;
    return true;
}

void Game::CreateTexture(int w, int h) {

    _texture = SDL_CreateTexture(_renderer, SDL_PIXELFORMAT_RGBA32,
                                 SDL_TEXTUREACCESS_STREAMING, w,h);
//
//    // 准备一幅800*600的红色RGB图像数据
//    unsigned char *rgb(new unsigned char[w * h * 4]);        // 乘以4是因为像素格式已指定为ARGB888，单个像素点占4字节
//
//    // 为上述图像数据赋值
//    for (int j = 0; j < h; j++)
//    {
//        int lineR = j * w * 4;                                          // 每一行R分量的起始位置
//        for (int i = 0; i < w * 4; i += 4)
//        {
//            rgb[lineR + i] = 128;                                                   // R
//            rgb[lineR + i + 1] = 128;                                               // G
//            rgb[lineR + i + 2] = 128;                                             // B
//            rgb[lineR + i + 3] = 0;                                               // A
//        }
//    }
//    // 5. 将内存中的RGB数据写入材质
//    SDL_UpdateTexture(_texture, NULL, rgb, w * 4);


    // 准备一幅800*600的红色RGB图像数据
    _pixels = new Color[w * h];        // 乘以4是因为像素格式已指定为ARGB888，单个像素点占4字节

    double uPerPixel = 256 / (double)w;
    double vPerPixel = 256 / (double)h;
    // 为上述图像数据赋值
    for (int j = 0; j < h; j++)
    {
        int lineR = j * w ;                                          // 每一行R分量的起始位置
        for (int i = 0; i < w; i++)
        {
            _pixels[lineR + i].r = i * uPerPixel;                                                   // R
            _pixels[lineR + i].g = j * vPerPixel;                                               // G
            _pixels[lineR + i].b = 0;                                             // B
            _pixels[lineR + i].a = 0;                                               // A
        }
    }

    // 5. 将内存中的RGB数据写入texture
    SDL_UpdateTexture(_texture, NULL, _pixels, w * 4);

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

    int mousePosX,mousePosY;
    SDL_GetMouseState(&mousePosX, &mousePosY);

    // 如果事件队列中有未处理的事件，按顺序处理
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            // 退出事件，按下窗口的叉
            case SDL_QUIT:
                isRunning = false;
                break;
            case SDL_MOUSEMOTION:		// 鼠标移动
//                SDL_Log("鼠标位置:%d,%d", mousePosX, mousePosY);

//                SetColor(mousePosX, mousePosY, COLOR_WHITE);

                SDL_UpdateTexture(_texture, NULL, _pixels, width * 4);
                break;
            case SDL_MOUSEBUTTONDOWN:	// 鼠标按键按下
                SDL_Log("鼠标按键按下:%d,%d", mousePosX, mousePosY);
                if(lastFrameMouseX == 0)
                {
                    SDL_Log("lastFrameMouseX == NULL");
                }
                //画线
                if(mousePosX < width && mousePosY < height)
                {
                    if(mousePosX != lastFrameMouseX && mousePosY != lastFrameMouseY)
                    {
                        DrawLine(lastFrameMouseX,lastFrameMouseY,
                                 mousePosX,mousePosY,COLOR_RED);
                    }
                }
                {//case里面定义变量要用{}括起来
                    //画三角形
                    Vector2Int p1{mousePosX - 5,mousePosY - 5};
                    Vector2Int p2{mousePosX + 5,mousePosY - 5};
                    Vector2Int p3{mousePosX,mousePosY + 5};
                    DrawTriangle(p1,p2,p3,COLOR_WHITE);

                }


                lastFrameMouseX = mousePosX;
                lastFrameMouseY = mousePosY;

                break;
            case SDL_MOUSEBUTTONUP:        // 鼠标按键松开
                break;
            default:
                break;
        }



    }
}



void Game::Update() {
    // 计算新的增量时间
    Timer::deltaTime = (SDL_GetTicks() - Timer::frameCount) / 1000.0f;

    fpsUpdateTimer += Timer::deltaTime;
    if(fpsUpdateTimer > fpsUpdateInterval)
    {
        fpsUpdateTimer -= fpsUpdateInterval;
        SDL_Log("当前帧：%d", Timer::frameCount);
        SDL_Log("当前FPS：%f", 1.0f/Timer::deltaTime);

    }
    // 计算新的一帧开始时所经过的总时间
    Timer::frameCount = SDL_GetTicks();


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

void Game::SetColor(int x, int y, Color color) {
    _pixels[y * width + x] = color;
}

//Bresenham’s Line Drawing Algorithm
void Game::DrawLine(int startX, int startY, int endX, int endY, Color color) {

    //判断斜率>1, >1时 沿Y方向遍历
    bool steep = false;
    if (std::abs(startX - endX) < std::abs(startY - endY)) { // if the line is steep, we transpose the image
        steep = true;
    }

    if(steep)
    {
        //y坐标从小到大绘制，
        if (startY > endY) { // make it left−to−right
            std::swap(startX, endX);
            std::swap(startY, endY);
        }

        int dx = endX-startX;
        int dy = endY-startY;

        //每Y像素上的X增加量×dy×2,将所有delta和offset都×dx以消去分母，避免浮点运算
//        float deltaYPerPixel = dy/(float)dx;
        float deltaXPerPixelMultiDyMulti2 = std::abs(dx) * 2;
        float offsetMultiDyMulti2 = 0;//offset×2, 将 offset > 0.5 优化为 2*offset > 1;

        //x移动方向
        int moveDirX = endX > startX ? 1 : -1;

        int x = startX;
        for (int y=startY; y<=endY; y++) {

            SetColor(x, y, color);
            offsetMultiDyMulti2 += deltaXPerPixelMultiDyMulti2;
            if(offsetMultiDyMulti2 > dy)
            {
                //移动y坐标
                x += moveDirX;
                offsetMultiDyMulti2 -= dy*2;
            }
        }
    }
    else
    {
        //x坐标从小到大绘制，
        if (startX > endX) { // make it left−to−right
            std::swap(startX, endX);
            std::swap(startY, endY);
        }

        int dx = endX-startX;
        int dy = endY-startY;

        //每X像素上的Y增加量×dx×2,将所有delta和offset都×dx以消去分母，避免浮点运算
//        float deltaYPerPixel = dy/(float)dx;
        int deltaYPerPixelMultiDxMulti2 = std::abs(dy) * 2;
        int offsetMultiDxMulti2 = 0;//offset×2, 将 offset > 0.5 优化为 2*offset > 1;

        //y移动方向
        int moveDirY = endY > startY ? 1 : -1;

        int y = startY;
        for (int x=startX; x<=endX; x++) {
            SetColor(x, y, color);

            offsetMultiDxMulti2 += deltaYPerPixelMultiDxMulti2;
//            if(offset > 0.5)
            if(offsetMultiDxMulti2 > dx)
            {
                //移动y坐标
                y += moveDirY;
                offsetMultiDxMulti2 -= dx*2;
            }
        }
    }

}

void Game::DrawLine(Vector2Int startPos, Vector2Int endPos, Color color) {
    DrawLine(startPos.x, startPos.y,endPos.x,endPos.y, color);
}

void Game::DrawTriangle(Vector2Int pos1, Vector2Int pos2, Vector2Int pos3, Color color) {
    DrawLine(pos1,pos2,color);
    DrawLine(pos1,pos3,color);
    DrawLine(pos2,pos3,color);

    //填充颜色
}

Vector3 Game::GetBarycentricCoordinate(Vector2Int pos1, Vector2Int pos2, Vector2Int pos3, Vector2Int P) {
    // P = (1-u-v)A + uB + vC
    // P = 1A -uA - vA + uB + vC
    // P = 1A + uB -uA + vC - vA
    // P = A + u(B-A) + v(C-A)
    // P = A + u(AB) +v(AC)
    // 0 = A-P + u(AB) +v(AC)
    // 0 = PA + u(AB) +v(AC)
    // PA + u(AB) +v(AC) = 0
    // 即
    //① (PA)ₓ + u(AB)ₓ +v(AC)ₓ = 0
    //② (PA)ᵧ + u(AB)ᵧ +v(AC)ᵧ = 0
    //相当于向量(1,u,v)和((PA)ₓ,(AB)ₓ,(AC)ₓ) 垂直(叉乘为0);
    //且向量(1,u,v)和((PA)ᵧ,(AB)ᵧ,(AC)ᵧ) 垂直(叉乘为0);


    return Vector3();
}
