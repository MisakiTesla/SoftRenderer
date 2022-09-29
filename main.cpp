#include <iostream>
#include "tgaimage.h"

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red   = TGAColor(255, 0,   0,   255);

//int main() {
//    std::cout << "Hello, World!哈哈" << std::endl;
//    TGAImage image(100, 100, TGAImage::RGB);
//    image.set(52, 41, red);
//    image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
//    image.write_tga_file("output.tga");
////    CreateWindowExA()
//    return 0;
//}

#include <iostream>
#include <SDL.h>

//error LNK2019: 无法解析的外部符号 SDL_main
//int main()
int main(int argc, char* argv[])
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("SDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);

    SDL_Delay(2000);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
    std::cout << "Hello World!阿松大\n";
}