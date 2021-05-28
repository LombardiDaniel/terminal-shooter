#ifndef RENDERER_H
#define RENDERER_H

#include <Windows.h>
#include <iostream>

#include "entity.h"
#include "map.h"
#include "player.h"
#include "mobs.h"

#define F_RAY_STEP_SIZE 0.1

class Renderer {
private:
    unsigned int nScreenWidth;		// Console Screen Size X (columns)
    unsigned int nScreenHeight;		// Console Screen Size Y (rows)

    float fDepth;
    float fFOV;
    
    Map map;

    wchar_t* screen;
	HANDLE hConsole;
	DWORD dwBytesWritten;

    void _outputFrame();

public:
    Renderer(unsigned int nScreenWidth, unsigned int nScreenHeight, float fFOV, Map map);
    void render(Player player, Mob mobs);


};

#endif
