
// mapa declarado aqui, passa pra render engine
#include <iostream>
#include "headers/entity.h"
#include "headers/player.h"
#include "headers/renderer.h"


int main(int argc, char const *argv[]) {

    Map map;

    map.nMapWidth = 16;
    map.nMapHeight = 16;
    map.map += L"################";
    map.map += L"#..............#";
    map.map += L"#..............#";
    map.map += L"#..............#";
    map.map += L"#..............#";
    map.map += L"#..............#";
    map.map += L"#..............#";
    map.map += L"#..............#";
    map.map += L"#..............#";
    map.map += L"#..............#";
    map.map += L"#..............#";
    map.map += L"#..............#";
    map.map += L"#..............#";
    map.map += L"#..............#";
    map.map += L"#..............#";
    map.map += L"################";

    Player player;

    player.pos.a = 0.f;
    player.pos.x = 8.f;
    player.pos.y = 8.f;

    float fFov = 3.141592 / 4.0;

    int nScreenW = 120;
    int nScreenH = 40;

    Mob mob;

    Renderer renderer = Renderer(nScreenW, nScreenH, fFov, map);

    while (true)
        renderer.render(player, mob);


    return 0;
}
