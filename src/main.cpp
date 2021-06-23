#include <iostream>
#include <chrono>
#include <Windows.h>
#include <mmsystem.h>

#include "headers/entity.h"
#include "headers/player.h"
#include "headers/engine.h"
#include "headers/utils.h"


int main(int argc, char const *argv[]) {

    if (utils::fileExists("track.wav"))
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

    // MAIN()
    Engine engine = Engine(nScreenW, nScreenH, fFov, map);

    auto tp1 = std::chrono::system_clock::now();
	auto tp2 = std::chrono::system_clock::now();

    WaveQueue waveQueue(map);
    waveQueue.pop(engine.currentWave);


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
        if (engine.currentWave.ended())
            waveQueue.pop(engine.currentWave);

        engine.captureInputs(player);

        engine.render(player);
    }

    return 0;
}
