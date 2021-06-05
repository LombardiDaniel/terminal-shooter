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
    this->_HUD += "______________________________________________________.                                                                  ";
    this->_HUD += "PLAYER.1..............................................\\.                                                                ";
    this->_HUD += "..HEALTH.[#########################........].8/10......\\.                                                               ";
    this->_HUD += "..AMMO...[||].2/2.......................................\\.                                                              ";
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
    return this->_HUD;
}

std::string Player::getgun() {
    return this->_gun;
}

// 217 192
