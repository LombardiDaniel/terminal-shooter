#include <Windows.h>
#include <iostream>
#include <chrono>
#include "math.h"


#include "headers/entity.h"
#include "headers/engine.h"
#include "headers/player.h"
#include "headers/mobs.h"
#include "headers/utils.h"


Player::Player() {
    this->logger = utils::Logger("Player", "logs/player.log", utils::Logger::Debug);

    this->fHealth = 10;
    this->nAmmoCount = 2;
    this->timings.shooting = -1;
    this->timings.reloading = -1;

    // default ammo - replace by list inicializer
    this->aCurrentAmmo.baseDamage = 10;
    this->aCurrentAmmo.symbol = 'i';
    this->fMovSpeed = 8;

    // this->aCurrentAmmo.damage = 5;
    // this->aCurrentAmmo.symbol = 'I';

    this->_HUD += "                                                                                                                        ";
    this->_HUD += "                                                                                                                        ";
    this->_HUD += "                                                                                                                        ";
    this->_HUD += "                                                                                                                        ";
    this->_HUD += "                                                                                                                        ";
    this->_HUD += "                                                                                                                        ";
    this->_HUD += "                                                                                                                        ";
    this->_HUD += "                                                                                                                        ";
    this->_HUD += "                                                                                                                        ";
    this->_HUD += "                                                                                                                        ";
    this->_HUD += "                                                                                                                        ";
    this->_HUD += "                                                                                                                        ";
    this->_HUD += "                                                                                                                        ";
    this->_HUD += "                                                                                                                        ";
    this->_HUD += "                                                                                                                        ";
    this->_HUD += "                                                                                                                        ";
    this->_HUD += "                                                                                                                        ";
    this->_HUD += "                                                                                                                        ";
    this->_HUD += "                                                                                                                        ";
    this->_HUD += "                                                           +                                                            ";
    this->_HUD += "                                                                                                                        ";
    this->_HUD += "                                                                                                                        ";
    this->_HUD += "                                                                                                                        ";
    this->_HUD += "                                                                                                                        ";
    this->_HUD += "                                                                                                                        ";
    this->_HUD += "                                                                                                                        ";
    this->_HUD += "                                                                                                                        ";
    this->_HUD += "                                                                                                                        ";
    this->_HUD += "                                                                                                                        ";
    this->_HUD += "                                                                                                                        ";
    this->_HUD += "                                                                                                                        ";
    this->_HUD += "                                                                                                                        ";
    this->_HUD += "                                                                                                                        ";
    this->_HUD += "                                                                                                                        ";
    this->_HUD += "                                                                                                                        ";
    this->_HUD += "______________________________________________________.                                                                 ";
    this->_HUD += "PLAYER.1..............................................\\.                                                                ";
    this->_HUD += "..HEALTH.[..............................].00/10........\\.                                                               ";
    this->_HUD += "..AMMO...[..].2/2.......................................\\.                                                              ";
    this->_HUD += "..SCORE..................................................\\.                                                             ";

    this->_gun += "                                                                                                                        ";
    this->_gun += "                                                                                                                        ";
    this->_gun += "                                                                                                                        ";
    this->_gun += "                                                                                                                        ";
    this->_gun += "                                                                                                                        ";
    this->_gun += "                                                                                                                        ";
    this->_gun += "                                                                                                                        ";
    this->_gun += "                                                                                                                        ";
    this->_gun += "                                                                                                                        ";
    this->_gun += "                                                                                                                        ";
    this->_gun += "                                                                                                                        ";
    this->_gun += "                                                                                                                        ";
    this->_gun += "                                                                                                                        ";
    this->_gun += "                                                                                                                        ";
    this->_gun += "                                                                                                                        ";
    this->_gun += "                                                                                                                        ";
    this->_gun += "                                                                                                                        ";
    this->_gun += "                                                                                                                        ";
    this->_gun += "                                                                                                                        ";
    this->_gun += "                                                                                                                        ";
    this->_gun += "                                                                                                                        ";
    this->_gun += "                                                                                                                        ";
    this->_gun += "                                                                                                                        ";
    this->_gun += "                                                                                                                        ";
    this->_gun += "                                                                                                                        ";
    this->_gun += "                                                                                                                        ";
    this->_gun += "                                                                                                                        ";
    this->_gun += "                                                                                                                        ";
    this->_gun += "                                                      .___ww___.                                                        ";
    this->_gun += "                                                     ./...||...\\.                                                       ";
    this->_gun += "                                                    ./....||....\\.                                                      ";
    this->_gun += "                                                   ./....|..|....\\.                                                     ";
    this->_gun += "                                                  ./.....|__|.....\\.                                                    ";
    this->_gun += "                                                 .|_____|....|_____|.                                                   ";
    this->_gun += "                                                 ./.....\\./\\./.....\\.                                                   ";
    this->_gun += "                                                .|.......|..|.......|.                                                  ";
    this->_gun += "                                                 .\\_____/....\\_____/.                                                  ";
    this->_gun += "                                                     \\............/                                                     ";
    this->_gun += "                                                      \\........../                                                      ";
    this->_gun += "                                                       |........|                                                       ";
}

std::string Player::getHUD() {

    // Dynamic HUD
    // HP:
    if (this->fHealth == 10) {
        this->_HUD[120 * 37 + 42] = '1';
        this->_HUD[120 * 37 + 43] = '0';
    } else {
        std::string sTmp = std::to_string(this->fHealth);
        this->_HUD[120 * 37 + 42] = '0';
        this->_HUD[120 * 37 + 43] = sTmp[0];
    }

    for (unsigned short int i = 0; i < 30; i++)
        this->_HUD[120 * 37 + 10 + i] = '.';

    for (unsigned short int i = 0; i < 3 * this->fHealth; i++)
        this->_HUD[120 * 37 + 10 + i] = '#';


    // AMMO:
    std::string sTmp = std::to_string(this->nAmmoCount);
    this->_HUD[120 * 38 + 14] = sTmp[0];

    for (unsigned short int i = 0; i < 2; i++)
        this->_HUD[120 * 38 + 10 + i] = '.';

    for (unsigned short int i = 0; i < this->nAmmoCount; i++)
        this->_HUD[120 * 38 + 10 + i] = this->aCurrentAmmo.symbol;


    return this->_HUD;
}

std::string Player::getgun() {
    return this->_gun;
}

void Player::shoot(float fMoment) {
    this->nAmmoCount--;
    this->timings.shooting += (int) fMoment;
}

bool Player::shooting(float fMoment) {

    if (this->timings.shooting == -1)
        return false;

    // Acumula o tempo dos ticks ate a hora certa
    this->timings.shooting += fMoment;

    if (this->timings.shooting >= N_SHOOTING_TIME_MS)
        this->timings.shooting = -1;

    return true;
}

void Player::reload(float fMoment) {
    this->timings.reloading += (int) fMoment;
    this->nAmmoCount = 2;
    this->logger.debug("Player started reload, fMoment = %.2f", fMoment);
}

bool Player::reloading(float fMoment) {

    if (this->timings.reloading == -1)
        return false;

    // Acumula o tempo dos ticks ate a hora certa
    this->timings.reloading += fMoment;

    if (this->timings.reloading >= N_RELOADING_TIME_MS)
        this->timings.reloading = -1;

    return true;
}

int Ammo::damage(float range) {
    if (range <= 5)
        return this->baseDamage;

    else if (range > 5 && range <= 8)
        return (int) this->baseDamage / 1.2;

    else if (range > 8 && range <= 10)
        return (int) this->baseDamage / 1.5;

    else if (range > 10)
        return (int) this->baseDamage / 2.2;

    return 2;
}
