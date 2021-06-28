#ifndef ENGINE_H
#define ENGINE_H

#include <Windows.h>
#include <iostream>

#include "entity.h"
#include "map.h"
#include "player.h"
#include "mobs.h"
#include "utils.h"

// Game loop "frequency"
#define GAME_TICK_RATE                  0b1000000

// Ray step size, increase to increase performance at the cost of quality
#define F_RAY_STEP_SIZE                 0.1

// ASCII Textures
#define H_TEXTURE_WALL_CLOSE            0xdb
#define H_TEXTURE_WALL_MEDIUM           0xb2
#define H_TEXTURE_WALL_FAR              0xb1
#define H_TEXTURE_WALL_VERY_FAR         0xb0
#define H_TEXTURE_FLOOR_CLOSE           0xf0
#define H_TEXTURE_FLOOR_MEDIUM          0xcd
#define H_TEXTURE_FLOOR_FAR             0xc4
#define H_TEXTURE_FLOOR_VERY_FAR        0xfa
#define H_TEXTURE_EMPTY                 0xff

// Commands
#define C_WALK_FORWARD                  0x57           // 'W'
#define C_WALK_BACKWARD                 0x53           // 'S'
#define C_WALK_LEFT                     0x41           // 'A'
#define C_WALK_RIGHT                    0x44           // 'D'
#define C_RELOAD_WEAPON                 0x52           // 'R'
#define C_LOOK_LEFT                     VK_LEFT        // 0x25
#define C_LOOK_RIGHT                    VK_RIGHT       // 0x27
#define C_FIRE_WEAPON                   VK_DOWN        // 0x28
#define C_FIRE_WEAPON_ALT               VK_SPACE       // 0x20
#define C_LOOK_SENSI                    0.5            // default: 0.5

// ASCII EndScreen
#define H_ENDSCREEN_CHAR_A              0xb1
#define H_ENDSCREEN_CHAR_B              0xdb
#define H_ENDSCREEN_CHAR_C              0xb2
#define H_ENDSCREEN_CHAR_D              0xdf
#define H_ENDSCREEN_CHAR_E              0xdd
#define H_ENDSCREEN_CHAR_F              0xb0
#define H_ENDSCREEN_CHAR_G              0xde
#define H_ENDSCREEN_CHAR_DEFAULT        0xff



class Engine {
private:
    utils::Logger logger;

    float fDepth;
    float fFOV;

    Map map;

    std::string _1mobsHealthBar;
    std::string _2mobsHealthBar;
    std::string _3mobsHealthBar;

    // Rendering related:
    unsigned int nScreenWidth;		// Console Screen Size X (columns)
    unsigned int nScreenHeight;		// Console Screen Size Y (rows)
    char* screen;
	HANDLE hConsole;
	DWORD dwBytesWritten;

    unsigned short lastMov;

    void _outputFrame();
    void _overlayGun(std::string gun, bool reloading);
    void _overlayHUD(std::string hud, const int damageIndicator, const int score);
    void _overlayMap(Position pos);
    void _createMobsHealthBars();
    std::string _createDeathScreen();
    std::string _getNumASCII(const unsigned short int num);

public:
    float fElapsedTimeMilliSeconds;
    MobsWave currentWave;

    Engine(unsigned int nScreenWidth, unsigned int nScreenHeight, float fFOV, Map map);

    void render(Player& player);
    void checkForDamage(Player& player);
    void updateMobs();
    void captureInputs(Player& player);
    void shootFromPlayer(Player& player);
    void deathScreen(const unsigned int score);

};

#endif
