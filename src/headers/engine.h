#ifndef RENDERER_H
#define RENDERER_H

#include <Windows.h>
#include <iostream>

#include "entity.h"
#include "map.h"
#include "player.h"
#include "mobs.h"

// Ray step size, increase to increase performance at the cost of quality
#define F_RAY_STEP_SIZE 0.1

// ASCII Textures
#define H_TEXTURE_WALL_CLOSE 0xdb
#define H_TEXTURE_WALL_MEDIUM 0xb2
#define H_TEXTURE_WALL_FAR 0xb1
#define H_TEXTURE_WALL_VERY_FAR 0xb0
#define H_TEXTURE_FLOOR_CLOSE 0xf0
#define H_TEXTURE_FLOOR_MEDIUM 0xcd
#define H_TEXTURE_FLOOR_FAR 0xc4
#define H_TEXTURE_FLOOR_VERY_FAR 0xfa
#define H_TEXTURE_EMPTY 0xff



class Engine {
private:
    float fDepth;
    float fFOV;

    Map map;

    // Rendering related:
    unsigned int nScreenWidth;		// Console Screen Size X (columns)
    unsigned int nScreenHeight;		// Console Screen Size Y (rows)
    char* screen;
	HANDLE hConsole;
	DWORD dwBytesWritten;

    void _outputFrame();

public:
    float fElapsedTime;

    Engine(unsigned int nScreenWidth, unsigned int nScreenHeight, float fFOV, Map map);
    void render(Player player, Mob mobs);


    void capture_inputs(Player& player);

};

#endif
