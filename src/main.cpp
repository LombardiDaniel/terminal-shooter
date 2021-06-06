
// mapa declarado aqui, passa pra render engine
#include <iostream>
#include <chrono>


#include "headers/entity.h"
#include "headers/player.h"
#include "headers/engine.h"
#include "headers/utils.h"


int main(int argc, char const *argv[]) {

    Map map;

    Player player;

    // Default spawn
    player.pos.a = - utils::PI / 2;
    player.pos.x = 14.f;
    player.pos.y = 14.5f;

    float fFov = utils::PI / 4.0;

    int nScreenW = 120;
    int nScreenH = 40;

    Wave mobsWave;
    Mob mob;
    mobsWave.nCount = 1;
    mob.nHealth = 14;
    mob.nMaxHealth = 20;
    for (size_t i = 0; i < mobsWave.nCount; i++)
        mobsWave.mobsObj[i] = mob;


    Engine engine = Engine(nScreenW, nScreenH, fFov, map);

    auto tp1 = std::chrono::system_clock::now();
	auto tp2 = std::chrono::system_clock::now();

    while (true) {

        tp2 = std::chrono::system_clock::now();
		std::chrono::duration<float> elapsedTime = tp2 - tp1;
		tp1 = tp2;

        engine.fElapsedTime = elapsedTime.count();

        engine.capture_inputs(player);

        engine.render(player, mobsWave);
    }

    return 0;
}
