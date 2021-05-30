#include <Windows.h>
#include <chrono>
#include "math.h"

#include "headers/entity.h"
#include "headers/engine.h"
#include "headers/player.h"
#include "headers/mobs.h"


Engine::Engine(unsigned int nScreenWidth, unsigned int nScreenHeight, float fFOV, Map map) {
    this->nScreenWidth = nScreenWidth;
    this->nScreenHeight = nScreenHeight;
    this->map = map;
    this->fFOV = fFOV;

    if (map.nMapWidth > map.nMapHeight)
        this->fDepth = map.nMapWidth;
    else
        this->fDepth = map.nMapHeight;

    // Create Screen Buffer
	this->screen = new char[this->nScreenWidth*this->nScreenHeight];
	this->hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(this->hConsole);
	this->dwBytesWritten = 0;
}


void Engine::render(Player player, Mob mobs) {

    for (size_t x = 0; x < this->nScreenWidth; x++) {
        float fRayAngle = (player.pos.a - this->fFOV / 2.f) + ((float) x / (float) this->nScreenWidth) * this->fFOV;

        float fDistanceToWall = 0.0f;

        // Unit-Vectors
        float fEyeX = sinf(fRayAngle);
        float fEyeY = cosf(fRayAngle);

        bool bHitWall = false;

        while(!bHitWall && fDistanceToWall < this->fDepth) {
            fDistanceToWall += F_RAY_STEP_SIZE;

            int nTestX = (int)(player.pos.x + fEyeX * fDistanceToWall);
            int nTestY = (int)(player.pos.y + fEyeY * fDistanceToWall);

            // Ray out of bounds
            if (nTestX < 0 || nTestX >= this->map.nMapWidth || nTestY < 0 || nTestY >= this->map.nMapHeight) {
                // bHitWall = true;
                fDistanceToWall = this->fDepth;
            } else {
                // Ray inbounds
                if (this->map.map[nTestY * this->map.nMapWidth + nTestX] == '#')
                    bHitWall = true;
            }
        }

        // 3D illusion
        int nCeiling = (float)(this->nScreenHeight / 2.0) - this->nScreenHeight / ((float)fDistanceToWall);
		int nFloor = this->nScreenHeight - nCeiling;

        // Shading
        for (int y = 0; y < (int) this->nScreenHeight; y++) {
            if (y <= nCeiling)
                this->screen[y * this->nScreenWidth + x] = ' ';
            else if (y > nCeiling && y <= nFloor)
                this->screen[y * this->nScreenWidth + x] = '#';
            else
                this->screen[y * this->nScreenWidth + x] = '.';
        }
    }

    this->_outputFrame();

}

void Engine::_outputFrame() {

    this->screen[this->nScreenWidth * this->nScreenHeight - 1] = '\0';
    WriteConsoleOutputCharacter(
        this->hConsole,
        (char*) this->screen,
        this->nScreenWidth * this->nScreenHeight,
        {0,0},
        &this->dwBytesWritten
    );

}

void Engine::capture_inputs(Player& player) {

    float fSpeed = 5.0f;

    if (GetAsyncKeyState((unsigned short)'A') & 0x8000)
		player.pos.a -= (fSpeed * 0.75f) * this->fElapsedTime;


	if (GetAsyncKeyState((unsigned short)'D') & 0x8000)
		player.pos.a += (fSpeed * 0.75f) * this->fElapsedTime;


    // // Handle Left movement & collision
	// if (GetAsyncKeyState((unsigned short)'A') & 0x8000)
	// {
	// 	player.pos.a += sinf(player.pos.a) * fSpeed * this->fElapsedTime;
	// 	player.pos.a += cosf(player.pos.a) * fSpeed * this->fElapsedTime;
	// 	if (this->map.map[(int)player.pos.x * this->map.nMapWidth + (int)player.pos.y] == '#')
	// 	{
	// 		player.pos.x -= sinf(player.pos.a) * fSpeed * this->fElapsedTime;
	// 		player.pos.y -= cosf(player.pos.a) * fSpeed * this->fElapsedTime;
	// 	}
	// }


	// Handle Forwards movement & collision
	if (GetAsyncKeyState((unsigned short)'W') & 0x8000) {
		player.pos.x += sinf(player.pos.a) * fSpeed * this->fElapsedTime;
		player.pos.y += cosf(player.pos.a) * fSpeed * this->fElapsedTime;
		if (this->map.map[(int)player.pos.x * this->map.nMapWidth + (int)player.pos.y] == '#') {
			player.pos.x -= sinf(player.pos.a) * fSpeed * this->fElapsedTime;
			player.pos.y -= cosf(player.pos.a) * fSpeed * this->fElapsedTime;
		}
	}

	// Handle backwards movement & collision
	if (GetAsyncKeyState((unsigned short)'S') & 0x8000) {
		player.pos.x -= sinf(player.pos.a) * fSpeed * this->fElapsedTime;
		player.pos.y -= cosf(player.pos.a) * fSpeed * this->fElapsedTime;
		if (this->map.map[(int)player.pos.x * this->map.nMapWidth + (int)player.pos.y] == '#') {
			player.pos.x += sinf(player.pos.a) * fSpeed * this->fElapsedTime;
			player.pos.y += cosf(player.pos.a) * fSpeed * this->fElapsedTime;
		}
	}

}
