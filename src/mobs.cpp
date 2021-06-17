#include <Windows.h>
#include <iostream>
#include <chrono>
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
