#ifndef RENDERER_H
#define RENDERER_H

#include "entity.h"
#include "map.h"
#include "player.h"
#include "mobs.h"

#include <Windows.h>
#include <iostream>

class Renderer {
private:
    int nScreenWidth;		// Console Screen Size X (columns)
    int nScreenHeight;		// Console Screen Size Y (rows)
    int fDepth;
    float fFOV;
    // std::wstring map;
    Map map;

    wchar_t *screen;
	HANDLE hConsole;
	DWORD dwBytesWritten;

public:
    Renderer(int nScreenWidth, int nScreenHeight, float fFOV, Map map);
    void render(Player player, Mob mobs);


};

#endif
