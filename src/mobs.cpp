#include <Windows.h>
#include <iostream>
#include <stdlib.h>
#include "math.h"

#include "headers/entity.h"
#include "headers/engine.h"
#include "headers/player.h"
#include "headers/mobs.h"
#include "headers/utils.h"

MobsWave::MobsWave() {

}

MobsWave::MobsWave(int nCount, Mob* mobs) {
    this->logger = utils::Logger("MobsWave", "logs/mobswave.log", utils::Logger::Debug);

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

int WaveQueue::getDificulty() {
    return this->dificulty;
}

MobsWave MobsWave::generateNewWave(int difficulty, Map map) {

    Mob mobs[3];

    unsigned int nMobsAmmount = utils::ourDistribution(1, 4);
    for (size_t i = 0; i < nMobsAmmount; i++) {
        // Health Power
        Mob tmpMob;
        int nMin = 15 + 10 / nMobsAmmount;
        int nMax = 20 + 10 / nMobsAmmount;
        tmpMob.nMaxHealth = utils::ourDistribution(nMin, nMax) * log(2 * difficulty + 1);
        tmpMob.nHealth = tmpMob.nMaxHealth;
        tmpMob.nDamagePerSecond = 1;

        // Spawn Position
        int tmpY, tmpX;
        size_t counter = 0;
        do {
            tmpX = utils::ourDistribution(2, 15);
            tmpY = utils::ourDistribution(2, 15 - i);
            counter++;

            // Impede mesma posicao que os mobs anteriores
            if (i > 0) {
                if (tmpX == mobs[0].pos.x && tmpY == mobs[0].pos.y)
                    continue;
                if (i == 2)
                    if (tmpX == mobs[1].pos.x && tmpY == mobs[1].pos.y)
                        continue;
            }

        } while (map.smap[tmpY * map.nMapWidth + tmpX] != '.' &&
            counter < N_MAX_MOB_SPAWN_ATTEMPT);

        if (counter >= N_MAX_MOB_SPAWN_ATTEMPT) {
            tmpX = 8 + i;
            tmpY = 6;
        }

        tmpMob.pos.x = tmpX;
        tmpMob.pos.y = tmpY;

        mobs[i] = tmpMob;

        utils::Logger logger("generateNewWave", "logs/mobswave.log", utils::Logger::Debug);
        if (tmpX >= map.nMapWidth || tmpY >= map.nMapHeight)
            logger.error("MOB OUT OF BOUNDS - Mob[%d], posX = %d, posY = %d", i, tmpX, tmpY);
        else if (map.smap[tmpY * map.nMapWidth + tmpX] == '#')
            logger.error("MOB INSIDE WALL - Mob[%d], posX = %d, posY = %d", i, tmpX, tmpY);
        else
            logger.debug("Mob[%d], posX = %d, posY = %d", i, tmpX, tmpY);


    }

    MobsWave newWave = MobsWave(nMobsAmmount, mobs);

    return newWave;
}


WaveQueue::WaveQueue(Map map) {
    this->dificulty = 0;
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
    mob3.nHealth = 20;
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

    MobsWave newWave = MobsWave::generateNewWave(++this->dificulty, this->map);

    this->push(newWave);

    return bTmp;
}
