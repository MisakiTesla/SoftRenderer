//
// Created by 61923 on 2023/2/28.
//

using namespace std;
#include <SDL_log.h>
#include <SDL.h>
#include <cmath>
#include <algorithm>
#include "Game.h"
#include "Timer.h"
#include "Model.h"

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

    _window = SDL_CreateWindow("SDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1024, 1024,
                                          SDL_WINDOW_SHOWN);
    if (!_window) {
        SDL_Log("SDL_Init:%d",SDL_GetError());
        return false;
    }

    // 最后一个参数为flag位，这里只用了SDL_RENDERER_ACCELERATED来使用硬件加速，
    // 假如想使用之前提到过的垂直同步也可以在这里用按位或运算符带上SDL_RENDERER_PRESENTVSYNC。
    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    width = 768;
    height = 768;

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

    //加载模型
    Model *model = NULL;
//    if (2 == argc) {
//        model = new Model(argv[1]);
//    }
//    else
    {
        model = new Model("../../res/lightning_obj01.obj");
//        model = new Model("../../res/african_head.obj");
    }
    //绘制模型
    SDL_Log("model faces %d", model->nfaces());
    for (int i=0; i<model->nfaces(); i++) {
        std::vector<int> face = model->face(i);
        for (int j=0; j<3; j++) {
            Vector3 v0 = model->vert(face[j]);
            Vector3 v1 = model->vert(face[(j+1)%3]);
            int x0 = (v0.x+1.)*width/2.;
            int y0 = (v0.y+1.)*height/2.;
            int x1 = (v1.x+1.)*width/2.;
            int y1 = (v1.y+1.)*height/2.;
//            DrawLine(x0, y0, x1, y1, COLOR_WHITE);
//flip Y axis
            DrawLine(x0, height - y0, x1, height - y1, COLOR_WHITE);
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
    //avoid overflow
    if(x < 0 || y < 0 || x >= width || y >= width)
    {
        return;
    }

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

    //填充颜色 bounding box
    Vector2Int bboxmin{width-1, height-1};
    Vector2Int bboxmax{0, 0};
    Vector2Int clamp{width-1, height-1};
    {
        bboxmin.x = std::max(0, std::min(bboxmin.x, pos1.x));
        bboxmin.y = std::max(0, std::min(bboxmin.y, pos1.y));

        bboxmax.x = std::min(clamp.x, std::max(bboxmax.x, pos1.x));
        bboxmax.y = std::min(clamp.y, std::max(bboxmax.y, pos1.y));

        bboxmin.x = std::max(0, std::min(bboxmin.x, pos2.x));
        bboxmin.y = std::max(0, std::min(bboxmin.y, pos2.y));

        bboxmax.x = std::min(clamp.x, std::max(bboxmax.x, pos2.x));
        bboxmax.y = std::min(clamp.y, std::max(bboxmax.y, pos2.y));

        bboxmin.x = std::max(0, std::min(bboxmin.x, pos3.x));
        bboxmin.y = std::max(0, std::min(bboxmin.y, pos3.y));

        bboxmax.x = std::min(clamp.x, std::max(bboxmax.x, pos3.x));
        bboxmax.y = std::min(clamp.y, std::max(bboxmax.y, pos3.y));
    }

    Vector2Int P;
    for (P.x=bboxmin.x; P.x<=bboxmax.x; P.x++) {
        for (P.y=bboxmin.y; P.y<=bboxmax.y; P.y++) {
            Vector3 bc_screen  = GetBarycentricCoordinate(pos1, pos2, pos3, P);
            SDL_Log("bc%f %f %f", bc_screen.x, bc_screen.y, bc_screen.z);
            //重心坐标任一小于0,则在三角形外
            if (bc_screen.x<0 || bc_screen.y<0 || bc_screen.z<0) continue;
            SetColor(P.x, P.y, color);
        }
    }
//    SDL_Log("bbox min x %d y %d", bboxmin.x, bboxmin.y);
//    SDL_Log("bbox max x %d y %d", bboxmax.x, bboxmax.y);
//
//    SetColor(bboxmin.x,bboxmin.y, COLOR_BLACK);
//    SetColor(bboxmax.x,bboxmax.y, COLOR_RED);

}

Vector3 Game::GetBarycentricCoordinate(Vector2Int A, Vector2Int B, Vector2Int C, Vector2Int P) {
    // P = (1-u-v)A + uB + vC
    // P = 1A -uA - vA + uB + vC
    // P = 1A + uB -uA + vC - vA
    // P = A + u(B-A) + v(C-A)
    // P = A + u(AB) +v(AC)
    // 0 = A-P + u(AB) +v(AC)
    // 0 = PA + u(AB) +v(AC)
    //  u(AB) +v(AC) + PA = 0
    // 即
    //① u(AB)ₓ +v(AC)ₓ + (PA)ₓ = 0
    //② u(AB)ᵧ +v(AC)ᵧ + (PA)ᵧ = 0
    //相当于向量(u,v,1)和((AB)ₓ,(AC)ₓ,(PA)ₓ) 垂直(点乘为0);
    //且向量(u,v,1)和((AB)ᵧ,(AC)ᵧ,(PA)ᵧ) 垂直(点乘为0);
    //即这意味着我们正在寻找一个同时与 （ABx，ACx，PAx） 和 （ABy，ACy，PAy） 正交的向量 （u，v，1）
    //所以向量(u,v,1) = ①和②的叉乘

    // pos1 pos2 pos3 P都是整数坐标 叉乘的结果c为|a||b|sinθ (必定垂直于xy平面，即(0,0,z)这种形式)
    // 又因为c的模即以a和b为两条边的平行四边形的面积,所以当c小于1时,pos1 pos2 pos3构成的是退化三角形
    // 原文:
    // `pts` and `P` has integer value as coordinates
    //  so `abs(u[2])` < 1 means `u[2]` is 0, that means
    //  triangle is degenerate, in this case return something with negative coordinates
    Vector3 vec = Vector3::Cross(Vector3{(float)(B.x-A.x), (float)(C.x-A.x), (float)(A.x - P.x)},
                                 Vector3{(float)(B.y-A.y), (float)(C.y-A.y), (float)(A.y - P.y)});
    if (std::abs(vec.z)<1) return Vector3{-1,1,1};
    return Vector3{1.f-(vec.x+vec.y)/vec.z, vec.x/vec.z, vec.y/vec.z};
}
