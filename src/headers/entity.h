#ifndef ENTITY_H
#define ENTITY_H

struct Position {
    float x;
    float y;
    float a;
};

class Entity {
public:
    float fHealth;
    int nMaxHealth;
    Position pos;
    float fMovSpeed;
};

#endif
