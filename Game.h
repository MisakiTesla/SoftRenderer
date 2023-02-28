//
// Created by 61923 on 2023/2/28.
//

#ifndef SOFTRENDERER_GAME_H
#define SOFTRENDERER_GAME_H


#include <SDL_video.h>

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

    SDL_Window *_window;
};


#endif //SOFTRENDERER_GAME_H
