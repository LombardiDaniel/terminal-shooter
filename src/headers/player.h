#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>

#include "entity.h"

struct Ammo { // recarrega por fila
    int damage;
    char symbol;
};

class Player : public Entity {
private:
    std::string _HUD;
    std::string _gun;

public:
    bool reloading;
    int nAmmoCount;
    Ammo aCurrentAmmo;

    Player();
    std::string getHUD();
    std::string getgun();
};

#endif
