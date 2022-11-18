//
// Created by miha on 2022/11/18.
//

#ifndef SOFTRENDERER_GAME_H
#define SOFTRENDERER_GAME_H


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

private:
    //!	处理事件
    void	Event();
    //!	更新各种状态
    void	Update();
    //!	渲染
    void	Draw();

    class SDL_Window*	window;		//!<	窗口
    bool	isRunning;		//!<	运行状态
    float deltaTime;
};


#endif //SOFTRENDERER_GAME_H
