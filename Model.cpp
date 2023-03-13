//
// Created by 61923 on 2023/3/12.
//

#include "Model.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <SDL_log.h>
#include "model.h"
#include <direct.h>
Model::Model(const char *filename) : verts_(), faces_() {
    std::ifstream in;
    char dir[1000];
    getcwd(dir, 1000);
    SDL_Log(dir);
    in.open (filename, std::ifstream::in);
    if (in.fail())
    {
        SDL_Log("未找到文件 %s", filename);
    }

    if (in.fail()) return;
    std::string line;
    while (!in.eof()) {
        std::getline(in, line);
        std::istringstream iss(line.c_str());
        char trash;
        if (!line.compare(0, 2, "v ")) {
            iss >> trash;
            Vector3 v;
//            for (int i=0;i<3;i++) iss >> v.raw[i];
            iss >> v.x;
            iss >> v.y;
            iss >> v.z;
            verts_.push_back(v);
        } else if (!line.compare(0, 2, "f ")) {
            std::vector<int> f;
            int itrash, idx;
            iss >> trash;
            while (iss >> idx >> trash >> itrash >> trash >> itrash) {
                idx--; // in wavefront obj all indices start at 1, not zero
                f.push_back(idx);
            }
            faces_.push_back(f);
        }
    }
    std::cerr << "# v# " << verts_.size() << " f# "  << faces_.size() << std::endl;
}

Model::~Model() {
}

int Model::nverts() {
    return (int)verts_.size();
}

int Model::nfaces() {
    return (int)faces_.size();
}

std::vector<int> Model::face(int idx) {
    return faces_[idx];
}

Vector3 Model::vert(int i) {
    return verts_[i];
}