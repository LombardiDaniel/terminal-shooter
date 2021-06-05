#include <Windows.h>
#include <chrono>
#include "math.h"

#include "headers/entity.h"
#include "headers/engine.h"
#include "headers/player.h"
#include "headers/mobs.h"
#include "headers/utils.h"


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
                if (this->map.smap[nTestY * this->map.nMapWidth + nTestX] == '#')
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
                if (fDistanceToWall <= this->fDepth / 4)            this->screen[y * nScreenWidth + x] = H_TEXTURE_WALL_CLOSE;
                else if (fDistanceToWall <= this->fDepth / 3)       this->screen[y * nScreenWidth + x] = H_TEXTURE_WALL_MEDIUM;
                else if (fDistanceToWall <= this->fDepth / 2)       this->screen[y * nScreenWidth + x] = H_TEXTURE_WALL_FAR;
                else                                                this->screen[y * nScreenWidth + x] = H_TEXTURE_WALL_VERY_FAR;
            else {
                float b = 1.0f - (((float)y - this->nScreenHeight/2.0f) / ((float) this->nScreenHeight / 2.0f));
                if (b < 0.4)		                                this->screen[y * nScreenWidth + x] = H_TEXTURE_FLOOR_CLOSE;
                else if (b < 0.45)	                                this->screen[y * nScreenWidth + x] = H_TEXTURE_FLOOR_MEDIUM;
                else if (b < 0.7)	                                this->screen[y * nScreenWidth + x] = H_TEXTURE_FLOOR_FAR;
                else if (b < 0.9)	                                this->screen[y * nScreenWidth + x] = H_TEXTURE_FLOOR_VERY_FAR;
                else				                                this->screen[y * nScreenWidth + x] = H_TEXTURE_EMPTY;
            }
        }
    }

    // this->_overlayFPS();
    this->_overlayHUD(player.getHUD());
    this->_overlayMap(player.pos);
    this->_outputFrame();

}

void Engine::_overlayFPS() {
    std::snprintf(this->screen, 10, "FPS=%5.2f", 1.0f/this->fElapsedTime);
}

void Engine::_overlayHUD(std::string hud) {

    for (unsigned short int x = 0; x < this->nScreenWidth; x++)
        for (unsigned short int y = 0; y < this->nScreenHeight; y++) {
            if (hud[y * this->nScreenWidth + x] != ' ')
                this->screen[y * this->nScreenWidth + x] = hud[y * this->nScreenWidth + x];
            if (hud[y * this->nScreenWidth + x] == '.')
                this->screen[y * this->nScreenWidth + x] = ' ';
        }


}

void Engine::_overlayMap(Position playerPos) {

    for (unsigned short int x = 0; x < this->map.nMapWidth; x++)
        for (unsigned short int y = 0; y < this->map.nMapHeight; y++)
            this->screen[y * this->nScreenWidth + x] = this->map.smap[(this->map.nMapHeight - y - 1) * this->map.nMapWidth + x];

    this->screen[(int)(this->map.nMapHeight - playerPos.y) * this->nScreenWidth + (int) playerPos.x] = 'P';

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

    if (GetAsyncKeyState((unsigned short) C_LOOK_LEFT) & 0x8000)
		player.pos.a -= (fSpeed * C_LOOK_SENSI) * this->fElapsedTime;


	if (GetAsyncKeyState((unsigned short) C_LOOK_RIGHT) & 0x8000)
		player.pos.a += (fSpeed * C_LOOK_SENSI) * this->fElapsedTime;

	// Handle Forwards movement & collision
	if (GetAsyncKeyState((unsigned short) C_WALK_FORWARD) & 0x8000) {
		player.pos.x += sinf(player.pos.a) * fSpeed * this->fElapsedTime;
		player.pos.y += cosf(player.pos.a) * fSpeed * this->fElapsedTime;
		if (this->map.smap[(int)player.pos.y * this->map.nMapWidth + (int)player.pos.x] == '#') {
			player.pos.x -= sinf(player.pos.a) * fSpeed * this->fElapsedTime;
			player.pos.y -= cosf(player.pos.a) * fSpeed * this->fElapsedTime;
		}
	}

    // Handle Right movement & collision
	if (GetAsyncKeyState((unsigned short) C_WALK_RIGHT) & 0x8000) {
		player.pos.x += sinf(player.pos.a + utils::PI/2) * fSpeed * this->fElapsedTime;
		player.pos.y += cosf(player.pos.a + utils::PI/2) * fSpeed * this->fElapsedTime;
		if (this->map.smap[(int)player.pos.y * this->map.nMapWidth + (int)player.pos.x] == '#') {
			player.pos.x -= sinf(player.pos.a + utils::PI/2) * fSpeed * this->fElapsedTime;
			player.pos.y -= cosf(player.pos.a + utils::PI/2) * fSpeed * this->fElapsedTime;
		}
	}

    // Handle Left movement & collision
	if (GetAsyncKeyState((unsigned short) C_WALK_LEFT) & 0x8000) {
		player.pos.x += sinf(player.pos.a - utils::PI/2) * fSpeed * this->fElapsedTime;
		player.pos.y += cosf(player.pos.a - utils::PI/2) * fSpeed * this->fElapsedTime;
		if (this->map.smap[(int)player.pos.y * this->map.nMapWidth + (int)player.pos.x] == '#') {
			player.pos.x -= sinf(player.pos.a - utils::PI/2) * fSpeed * this->fElapsedTime;
			player.pos.y -= cosf(player.pos.a - utils::PI/2) * fSpeed * this->fElapsedTime;
		}
	}

	// Handle backwards movement & collision
	if (GetAsyncKeyState((unsigned short) C_WALK_BACKWARD) & 0x8000) {
		player.pos.x -= sinf(player.pos.a) * fSpeed * this->fElapsedTime;
		player.pos.y -= cosf(player.pos.a) * fSpeed * this->fElapsedTime;
		if (this->map.smap[(int)player.pos.y * this->map.nMapWidth + (int)player.pos.x] == '#') {
			player.pos.x += sinf(player.pos.a) * fSpeed * this->fElapsedTime;
			player.pos.y += cosf(player.pos.a) * fSpeed * this->fElapsedTime;
		}
	}

}
