#ifndef MOB_H
#define MOB_H

#include "entity.h"

class Mob : public Entity {
public:
    int nMobHeight;
};

struct Wave {
    unsigned int nCount;
    Mob mobsObj[3];
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
