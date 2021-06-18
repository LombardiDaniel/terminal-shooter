#ifndef RENDERER_H
#define RENDERER_H

#include <Windows.h>
#include <iostream>

#include "entity.h"
#include "map.h"
#include "player.h"
#include "mobs.h"

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
#define C_LOOK_LEFT                     VK_LEFT        // 0x25
#define C_LOOK_RIGHT                    VK_RIGHT       // 0x27
#define C_FIRE_WEAPON                   VK_DOWN        // 0x28
#define C_FIRE_WEAPON_ALT               VK_SPACE       // 0x20
#define C_LOOK_SENSI                    0.5            // default: 0.5


class Engine {
private:
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
    void _overlayHUD(std::string hud, const int damageIndicator);
    void _overlayMap(Position pos);
    void _createMobsHealthBars();

public:
    float fElapsedTimeMilliSeconds;
    MobsWave currentWave;

    Engine(unsigned int nScreenWidth, unsigned int nScreenHeight, float fFOV, Map map);

    void render(Player player);
    void updateMobs();
    void captureInputs(Player& player);
    void shootFromPlayer(Player& player);

};

#endif
