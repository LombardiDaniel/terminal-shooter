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

    this->nHealth = 10;
    this->nAmmoCount = 2;

    // default ammo - replace by list inicializer
    this->aCurrentAmmo.damage = 2;
    this->aCurrentAmmo.symbol = 'i';

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
    this->_HUD += ".........................................................\\.                                                             ";

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
    if (this->nHealth == 10) {
        this->_HUD[120 * 37 + 42] = '1';
        this->_HUD[120 * 37 + 43] = '0';
    } else {
        std::string sTmp = std::to_string(this->nHealth);
        this->_HUD[120 * 37 + 42] = '0';
        this->_HUD[120 * 37 + 43] = sTmp[0];
    }

    for (unsigned short int i = 0; i < 30; i++)
        this->_HUD[120 * 37 + 10 + i] = '.';
        
    for (unsigned short int i = 0; i < 3 * this->nHealth; i++)
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

// 217 192
