#ifndef ENTITY_H
#define ENTITY_H

struct Position {
    float x;
    float y;
    float a;
};

class Entity {
public:
    int health;
    Position pos;
};

#endif
