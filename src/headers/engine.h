#ifndef RENDERER_H
#define RENDERER_H

#include <Windows.h>
#include <iostream>

#include "entity.h"
#include "map.h"
#include "player.h"
#include "mobs.h"

#define F_RAY_STEP_SIZE 0.1

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
