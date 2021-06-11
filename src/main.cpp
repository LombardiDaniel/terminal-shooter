
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


    Mob mob1;
    mob1.nHealth = 14;
    mob1.nMaxHealth = 20;
    mob1.pos.x = 10;
    mob1.pos.y = 4;

    Mob mob2;
    mob2.nHealth = 20;
    mob2.nMaxHealth = 20;
    mob2.pos.x = 11;
    mob2.pos.y = 5;

    Mob mob3;
    mob3.nHealth = 1;
    mob3.nMaxHealth = 20;
    mob3.pos.x = 9;
    mob3.pos.y = 5;

    Mob mob_lst[3];
    mob_lst[0] = mob1;
    mob_lst[1] = mob2;
    mob_lst[2] = mob3;
    MobsWave wave = MobsWave(3, mob_lst);


    Engine engine = Engine(nScreenW, nScreenH, fFov, map);

    auto tp1 = std::chrono::system_clock::now();
	auto tp2 = std::chrono::system_clock::now();

    while (true) {

        tp2 = std::chrono::system_clock::now();
		std::chrono::duration<float> elapsedTime = tp2 - tp1;
		tp1 = tp2;

        engine.fElapsedTime = elapsedTime.count();

        engine.updateMobs(wave);

        engine.captureInputs(player);

        engine.render(player, wave);
    }

    return 0;
}
