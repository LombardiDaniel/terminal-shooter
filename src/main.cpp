#include <iostream>
#include <chrono>
#include <Windows.h>
#include <mmsystem.h>

#include "headers/entity.h"
#include "headers/player.h"
#include "headers/engine.h"
#include "headers/utils.h"


int main(int argc, char const *argv[]) {

    PlaySound(TEXT("track.wav"), NULL, SND_LOOP | SND_ASYNC); // Background music

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
    mob1.nHealth = 20;
    mob1.nMaxHealth = 20;
    mob1.pos.x = 2;
    mob1.pos.y = 2;

    Mob mob2;
    mob2.nHealth = 20;
    mob2.nMaxHealth = 20;
    mob2.pos.x = 11;
    mob2.pos.y = 5;

    Mob mob3;
    mob3.nHealth = 5;
    mob3.nMaxHealth = 20;
    mob3.pos.x = 9;
    mob3.pos.y = 5;

    Mob mob_lst[3];
    mob_lst[0] = mob1;
    mob_lst[1] = mob2;
    mob_lst[2] = mob3;
    MobsWave wave = MobsWave(3, mob_lst);


    // MAIN()
    Engine engine = Engine(nScreenW, nScreenH, fFov, map);
    engine.currentWave = wave;

    auto tp1 = std::chrono::system_clock::now();
	auto tp2 = std::chrono::system_clock::now();


    while (true) {

        tp2 = std::chrono::system_clock::now();
		std::chrono::duration<float> elapsedTime = tp2 - tp1;

        engine.fElapsedTimeMilliSeconds = std::chrono::duration_cast<std::chrono::milliseconds>(tp2 - tp1).count();

        if (engine.fElapsedTimeMilliSeconds <= 1000 / GAME_TICK_RATE)
            continue;

        // Game-tick:
		tp1 = tp2;

        engine.updateMobs();
        // Precisa gerar uma wave nova
        // if (engine.currentWave.ended())
        //     engine.currentWave = waveQueue.pop();

        engine.captureInputs(player);

        engine.render(player);
    }

    return 0;
}
