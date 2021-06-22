#include <Windows.h>
#include <iostream>
#include <random>
#include "math.h"

#include "headers/entity.h"
#include "headers/engine.h"
#include "headers/player.h"
#include "headers/mobs.h"
#include "headers/utils.h"

MobsWave::MobsWave() {

}

MobsWave::MobsWave(int nCount, Mob* mobs) {

    this->nCount = nCount;
    for (int i = 0; i < nCount; i++)
        this->mobsObj[i] = mobs[i];

}

bool MobsWave::ended() {
    for (size_t i = 0; i < this->nCount; i++)
        if (this->mobsObj[i].nHealth > 0)
            return false;

    return true;
}

MobsWave MobsWave::generateNewWave(int difficulty, Map map) {

    Mob mobs[3];
    unsigned int nMobsAmmount = rand() % 3 + 1;
    for (size_t i = 0; i < nMobsAmmount; i++) {
        std::default_random_engine generator;
        std::normal_distribution<float> distribution(20 + 10/nMobsAmmount, 3);

        // Health Power
        Mob tmpMob;
        tmpMob.nMaxHealth = (int) distribution(generator) * log(2 * difficulty + 1);
        tmpMob.nHealth = tmpMob.nMaxHealth;

        // Spawn Position
        int tmpY, tmpX;
        size_t counter = 0;
        do {
            tmpX = rand() % map.nMapWidth;
            tmpY = rand() % map.nMapHeight;
            counter++;
        } while (map.smap[tmpY * map.nMapWidth + tmpX] == '.' ||
            counter < N_MAX_MOB_SPAWN_ATTEMPT);

        if (counter >= N_MAX_MOB_SPAWN_ATTEMPT) {
            tmpX = 8;
            tmpY = 6;
        }

        tmpMob.pos.x = tmpX;
        tmpMob.pos.y = tmpY;

        mobs[i] = tmpMob;
    }

    MobsWave newWave = MobsWave(nMobsAmmount, mobs);

    return newWave;
}


WaveQueue::WaveQueue(Map map) {
    dificulty = 0;
    this->map = map;

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

    Mob mobLst[3];
    mobLst[0] = mob1;
    mobLst[1] = mob2;
    mobLst[2] = mob3;
    this->push(MobsWave(3, mobLst));
}

bool WaveQueue::pop(MobsWave& wave) {
    bool bTmp = utils::Queue<MobsWave>::pop(wave);

    wave = MobsWave::generateNewWave(++this->dificulty, this->map);

    return bTmp;
}
