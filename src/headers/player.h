#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>

#include "entity.h"

#define N_SHOOTING_TIME_MS 500
#define N_RELOADING_TIME_MS 1500


struct Ammo { // recarrega por fila
    int damage;
    char symbol;
};

struct TimingsMs {
    int reloading;
    int shooting;
};

class Player : public Entity {
private:
    std::string _HUD;
    std::string _gun;

public:
    TimingsMs timings;
    bool reloading(float fMoment);
    bool shooting(float fMoment);
    int nAmmoCount;
    Ammo aCurrentAmmo;

    Player();
    void shoot(float fMoment);
    std::string getHUD();
    std::string getgun();
};

#endif
