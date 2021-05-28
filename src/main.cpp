
// mapa declarado aqui, passa pra render engine
#include <iostream>
#include "headers/entity.h"
#include "headers/player.h"
#include "headers/renderer.h"


int main(int argc, char const *argv[]) {

    std::wstring map;

    map += L"################";
    map += L"#..............#";
    map += L"#.......########";
    map += L"#..............#";
    map += L"#......##......#";
    map += L"#......##......#";
    map += L"#..............#";
    map += L"###............#";
    map += L"##.............#";
    map += L"#......####..###";
    map += L"#......#.......#";
    map += L"#......#.......#";
    map += L"#..............#";
    map += L"#......#########";
    map += L"#..............#";
    map += L"################";



    return 0;
}
