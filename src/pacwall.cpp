//#include "game.h"
#include "game.cpp"
#include <string>

int main(void) {
    string tit = "PacWall";
    Game pacwall(1150,600,tit);
    pacwall.Run();
}