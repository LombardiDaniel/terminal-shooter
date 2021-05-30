
// mapa declarado aqui, passa pra render engine
#include <iostream>
#include <chrono>


#include "headers/entity.h"
#include "headers/player.h"
#include "headers/engine.h"
#include "headers/utils.h"


int main(int argc, char const *argv[]) {

    Map map;

    map.nMapWidth = 16;
    map.nMapHeight = 16;
    map.map += "################";
    map.map += "#..............#";
    map.map += "#..............#";
    map.map += "#..............#";
    map.map += "#..............#";
    map.map += "#..............#";
    map.map += "#..............#";
    map.map += "#..............#";
    map.map += "#..............#";
    map.map += "#..............#";
    map.map += "#..............#";
    map.map += "#..............#";
    map.map += "#..............#";
    map.map += "#..............#";
    map.map += "#..............#";
    map.map += "################";

    Player player;

    player.pos.a = 0.f;
    player.pos.x = 8.f;
    player.pos.y = 8.f;

    float fFov = utils::PI / 4.0;

    int nScreenW = 120;
    int nScreenH = 40;

    Mob mob;

    Engine engine = Engine(nScreenW, nScreenH, fFov, map);

    auto tp1 = std::chrono::system_clock::now();
	auto tp2 = std::chrono::system_clock::now();

    while (true) {

        tp2 = std::chrono::system_clock::now();
		std::chrono::duration<float> elapsedTime = tp2 - tp1;
		tp1 = tp2;

        engine.fElapsedTime = elapsedTime.count();

        engine.capture_inputs(player);

        engine.render(player, mob);
    }

    return 0;
}
