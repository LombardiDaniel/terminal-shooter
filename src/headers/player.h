#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>

#include "entity.h"
#include "utils.h"

#define N_SHOOTING_TIME_MS 500
#define N_RELOADING_TIME_MS 1500


struct Ammo {
    int baseDamage;
    int damage(float range);
    char symbol;
};

struct TimingsMs { // if the timing is -1, means it is not happening
    int reloading;
    int shooting;
};

class Player : public Entity {
private:
    utils::Logger logger;

    std::string _HUD;
    std::string _gun;

public:
    TimingsMs timings;
    bool reloading(float fMoment);
    bool shooting(float fMoment);
    int nAmmoCount;
    Ammo aCurrentAmmo;
    int damageIndicator;

    Player();
    void shoot(float fMoment); // inicializes the timing.shooting and reduces ammo
    void reload(float fMoment); // identical to shoot
    std::string getHUD();
    std::string getgun();
};

#endif
