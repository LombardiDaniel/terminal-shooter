#ifndef MOB_H
#define MOB_H

#include "entity.h"
#include "utils.h"
#include "map.h"

#define N_MAX_MOB_SPAWN_ATTEMPT     0xf00

class Mob : public Entity {
public:
    int nMobHeight;
};

class MobsWave {
private:
    utils::Logger logger;
public:
    unsigned int nCount;
    Mob mobsObj[3];

    MobsWave();
    MobsWave(int nCount, Mob* mobs);
    bool ended();

    static MobsWave generateNewWave(int difficulty, Map map);
};

class WaveQueue : public utils::Queue<MobsWave> {
private:
    MobsWave enemyWaves[5];
    int dificulty;
    Map map;

public:
    WaveQueue(Map map);
    bool pop(MobsWave& wave);
    int getDificulty();
};


#endif

// usar uma uniao pra resetar o atual
// assim da pra fazer A.reg = 0x00; que vai resetar td pra 0
// ex:
//
// union {
//     struct { // 8 bits = 1 byte
//         char unused : 1;
//         char sw2 : 1;
//         char sw1 : 1;
//         char state : 2;
//         char value : 3;
//     };
//     char reg; // 1 byte
// } MyBitField;
