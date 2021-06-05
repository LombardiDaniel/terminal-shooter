#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>

#include "entity.h"

class Player : public Entity {
private:
    std::string _HUD;

public:
    Player();
    std::string getHUD();
};

#endif
