//
// Created by 61923 on 2023/2/28.
//

#ifndef SOFTRENDERER_GAME_H
#define SOFTRENDERER_GAME_H


#include <SDL_video.h>
#include <SDL_render.h>
#include <cmath>


//typedef struct Color{
struct Color{
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
};

const Color COLOR_WHITE{255,255,255,255};
const Color COLOR_RED{255,0,0,255};
const Color COLOR_BLACK{0,0,0,255};

struct Vector2Int{
    int x,y;
};

struct Vector3{
    float x,y,z;
public:
    static Vector3 Cross(Vector3 a, Vector3 b)
    {
        return Vector3{a.y*b.z-a.z*b.y, a.z*b.x-a.x*b.z, a.x*b.y-a.y*b.x};
    }
    static float Dot(Vector3 a, Vector3 b)
    {
        return a.x*b.x + a.y*b.y + a.z*b.z;
    }
    inline Vector3 operator +(const Vector3 &v) const { return Vector3{x+v.x, y+v.y, z+v.z}; }
    inline Vector3 operator -(const Vector3 &v) const { return Vector3{x-v.x, y-v.y, z-v.z}; }
    inline Vector3 operator *(float f)          const { return Vector3{x*f, y*f, z*f}; }
    float norm () const { return std::sqrt(x*x+y*y+z*z); }
    Vector3 & Normalize(float l=1) { *this = (*this) * (l / norm()); return *this; }
};

class Game {
public:
    //!	构造函数
    Game();

    //!	初始化
    bool	Initialize();
    //!	主循环
    void	Loop();
    //!	游戏结束
    void	Shutdown();
    bool	isRunning;		//!<	运行状态

private:
    //!	处理事件
    void	Event();
    //!	更新各种状态
    void	Update();
    //!	渲染
    void	Draw();

    SDL_Renderer* _renderer;//error C2143: 语法错误: 缺少“;”(在“*”的前面) 解决方法=> #include <SDL_render.h>
    SDL_Window* _window;
    int width,height;
    bool flipY;
    SDL_Texture* _texture;
    Color *_pixels;//_texture 的所有像素数据 大小为width*height
    float *_zBuffer;//ZBuffer 大小为width*height
    float fpsUpdateInterval;//fps显示更新间隔
    float fpsUpdateTimer;//fps显示更新间隔
    int lastFrameMouseX = 0,lastFrameMouseY = 0;//上一帧鼠标位置
    Vector2Int lastClickPosInTexture{0,0};//上一帧鼠标位置

    void DrawLine(int startX, int startY, int endX, int endY, Color color);
    void DrawLine(Vector2Int startPos, Vector2Int endPos, Color color);
    void DrawTriangleScreenSpace(Vector2Int pos1, Vector2Int pos2, Vector2Int pos3, Color color);
    void DrawTriangle(Vector3 pos1, Vector3 pos2, Vector3 pos3, Color color);
    Vector3 GetBarycentricCoordinate(Vector2Int A, Vector2Int B, Vector2Int C, Vector2Int P);
    Vector3 GetBarycentricCoordinate(Vector3 A, Vector3 B, Vector3 C, Vector3 P);

    void CreateTexture(int width, int height);

    void DrawTexture(SDL_Texture *texture, int posX = 0, int posY = 0);

    void SetColor(int x, int y, Color color);
    void SetZBuffer(int x, int y, float z);
    float GetZBuffer(int x, int y);
    Vector3 World2screen(Vector3 v) {
        //return Vector3{(float )((v.x+1.)*(float )width/2.+.5), (float )((v.y+1.)*(float )height/2.+.5), v.z};
        //                     👇这里强转为int避免接缝
        return Vector3{(float )(int)((v.x+1.)*(float )width/2.+.5), (float )(int )((v.y+1.)*(float )height/2.+.5), v.z};
    }

};


#endif //SOFTRENDERER_GAME_H
