//
// Created by 61923 on 2023/3/3.
//

#ifndef SOFTRENDERER_TIMER_H
#define SOFTRENDERER_TIMER_H


class Timer {
public:
    // 增量时间
    static float deltaTime;
    // 总共经过的时间
    static unsigned int frameCount;
};

#endif //SOFTRENDERER_TIMER_H
