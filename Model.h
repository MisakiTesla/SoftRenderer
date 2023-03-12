//
// Created by 61923 on 2023/3/12.
//

#ifndef SOFTRENDERER_MODEL_H
#define SOFTRENDERER_MODEL_H


#include <vector>
#include "Game.h"

class Model {
private:
    std::vector<Vector3> verts_;
    std::vector<std::vector<int> > faces_;
public:
    Model(const char *filename);
    ~Model();
    int nverts();
    int nfaces();
    Vector3 vert(int i);
    std::vector<int> face(int idx);
};


#endif //SOFTRENDERER_MODEL_H
