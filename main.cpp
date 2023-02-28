#include <iostream>
#include "tgaimage.h"
#include "Game.h"

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
#include <string>
#include <SDL_log.h>

//error LNK2019: 无法解析的外部符号 SDL_main
//int main()
int main(int argc, char* argv[]) {


    Game game;
    printf("哈哈");
    SDL_Log("哈哈sdl");
    bool success = game.Initialize();
    if (success)
    {
        game.Loop();
    }
    game.Shutdown();

    return 0;
}