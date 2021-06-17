#include <Windows.h>
#include <iostream>
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
    this->_createMobsHealthBars();

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

void Engine::render(Player player) {

    for (size_t x = 0; x < this->nScreenWidth; x++) {
        float fRayAngle = (player.pos.a - this->fFOV / 2.f) + ((float) x / (float) this->nScreenWidth) * this->fFOV;

        float fDistanceToWall = 0.0f;

        // Unit-Vectors
        float fEyeX = sinf(fRayAngle);
        float fEyeY = cosf(fRayAngle);

        bool bHitWall = false;
        bool bHitMob = false;

        while(!bHitWall && !bHitMob &&fDistanceToWall < this->fDepth) {
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
                else if (this->map.smobs[nTestY * this->map.nMapWidth + nTestX] == 'X')
                    bHitMob = true;
            }
        }

        // 3D illusion
        int nCeiling = (float)(this->nScreenHeight / 2.0) - this->nScreenHeight / ((float)fDistanceToWall);
        if (bHitMob && !bHitWall)
            nCeiling -= 5;
        int nFloor = this->nScreenHeight - nCeiling;

        // Shading
        for (int y = 0; y < (int) this->nScreenHeight; y++) {
            if (y <= nCeiling)
                this->screen[y * this->nScreenWidth + x] = ' ';
            else if (y > nCeiling && y <= nFloor) {
                if (bHitMob && !bHitWall)
                    this->screen[y * nScreenWidth + x] = '$'; // Aqui ta renderizando mob AO INVES da parede, colocar o mob em cima da parede
                else if (!bHitMob && bHitWall) {
                    if (fDistanceToWall <= this->fDepth / 4)            this->screen[y * nScreenWidth + x] = H_TEXTURE_WALL_CLOSE;
                    else if (fDistanceToWall <= this->fDepth / 3)       this->screen[y * nScreenWidth + x] = H_TEXTURE_WALL_MEDIUM;
                    else if (fDistanceToWall <= this->fDepth / 2)       this->screen[y * nScreenWidth + x] = H_TEXTURE_WALL_FAR;
                    else                                                this->screen[y * nScreenWidth + x] = H_TEXTURE_WALL_VERY_FAR;
                }
            } else {
                float b = 1.0f - (((float) y - this->nScreenHeight/2.0f) / ((float) this->nScreenHeight / 2.0f));
                if (b < 0.4)		                                    this->screen[y * nScreenWidth + x] = H_TEXTURE_FLOOR_CLOSE;
                else if (b < 0.45)	                                    this->screen[y * nScreenWidth + x] = H_TEXTURE_FLOOR_MEDIUM;
                else if (b < 0.7)	                                    this->screen[y * nScreenWidth + x] = H_TEXTURE_FLOOR_FAR;
                else if (b < 0.9)	                                    this->screen[y * nScreenWidth + x] = H_TEXTURE_FLOOR_VERY_FAR;
                else				                                    this->screen[y * nScreenWidth + x] = H_TEXTURE_EMPTY;
            }
        }
    }

    this->_overlayGun(player.getgun(), player.reloading(this->fElapsedTimeMilliSeconds));
    this->_overlayHUD(player.getHUD());
    this->_overlayMap(player.pos);
    this->_outputFrame();
}

void Engine::updateMobs() {

    for (size_t i = 0; i < this->currentWave.nCount; i++) {
        const int nMapHeight = this->map.nMapHeight;
        const int coord = (int) this->currentWave.mobsObj[i].pos.y * nMapHeight + this->currentWave.mobsObj[i].pos.x;
        if (this->currentWave.mobsObj[i].nHealth > 0)
            this->map.smobs[coord] = 'X';
        else
            this->map.smobs[coord] = '.';

    }
}

void Engine::_overlayGun(std::string gun, bool reloading) {

    short movAmmountX = 0;
    short movAmmountY = 1;

    switch (this->lastMov) {
        case C_WALK_FORWARD:
            movAmmountY++;
            break;
        case C_WALK_BACKWARD:
            movAmmountY--;
            break;
        case C_WALK_LEFT:
            movAmmountX++;
            break;
        case C_WALK_RIGHT:
            movAmmountX--;
            break;
    }

    for (unsigned short int x = 0; x < this->nScreenWidth; x++)
        for (unsigned short int y = 0; y < this->nScreenHeight; y++)
            if (!reloading) {
                if (gun[y * this->nScreenWidth + x] != ' ')
                    this->screen[(y + movAmmountY) * this->nScreenWidth + (x + movAmmountX)] = gun[y * this->nScreenWidth + x];
                if (gun[y * this->nScreenWidth + x] == '.')
                    this->screen[(y + movAmmountY) * this->nScreenWidth + (x + movAmmountX)] = ' ';
            } else {

            }

}

void Engine::_overlayHUD(std::string hud) {

    for (unsigned short int x = 0; x < this->nScreenWidth; x++)
        for (unsigned short int y = 0; y < this->nScreenHeight; y++) {
            if (hud[y * this->nScreenWidth + x] == '.')
                this->screen[y * this->nScreenWidth + x] = ' ';
            else if (hud[y * this->nScreenWidth + x] != ' ')
                this->screen[y * this->nScreenWidth + x] = hud[y * this->nScreenWidth + x];
        }

    // Health bar dos mobs - falta um switch-case pra 1, 2, ou 3 mobs
    std::string mobsHealthBarList;
    switch (this->currentWave.nCount) {
        case 1:
            mobsHealthBarList = this->_1mobsHealthBar;
            break;
        case 2:
            mobsHealthBarList = this->_2mobsHealthBar;
            break;
        case 3:
            mobsHealthBarList = this->_3mobsHealthBar;
            break;
    }

    for (unsigned short int x = 0; x < this->nScreenWidth; x++)
        for (unsigned short int y = 0; y < this->nScreenHeight; y++) {
            if (mobsHealthBarList[y * this->nScreenWidth + x] == '.')
                this->screen[y * this->nScreenWidth + x] = ' ';
            else if (mobsHealthBarList[y * this->nScreenWidth + x] != ' ')
                this->screen[y * this->nScreenWidth + x] = mobsHealthBarList[y * this->nScreenWidth + x];
        }

    unsigned short int tmpSize;
    switch (this->currentWave.nCount) {
        case 1:
            for (unsigned short int i = 0; i < 57; i++) {
                this->screen[140 * 0 + 31 + i] = ' ';
                this->screen[140 * 1 + 31 + i - 20] = ' ';
            }
            if (this->currentWave.mobsObj[0].nHealth > 0) {
                tmpSize = 57 * this->currentWave.mobsObj[0].nHealth / this->currentWave.mobsObj[0].nMaxHealth;
                if (tmpSize < 1 && tmpSize > -1) tmpSize = 1;
                for (unsigned short int i = 0; i < tmpSize; i++) {
                    this->screen[140 * 0 + 31 + i] = '#';
                    this->screen[140 * 1 + 31 + i - 20] = '#';
                }
            }
            break;

        case 2:
            for (unsigned short int i = 0; i < 24; i++) {
                this->screen[140 * 0 + 21 + i] = ' ';
                this->screen[140 * 1 + 21 + i - 20] = ' ';

                this->screen[140 * 0 + 71 + i] = ' ';
                this->screen[140 * 1 + 71 + i - 20] = ' ';
            }

            if (this->currentWave.mobsObj[0].nHealth > 0) {
                tmpSize = 24 * this->currentWave.mobsObj[0].nHealth / this->currentWave.mobsObj[0].nMaxHealth;
                if (tmpSize < 1 && tmpSize > -1) tmpSize = 1;
                for (unsigned short int i = 0; i < tmpSize; i++) {
                    this->screen[140 * 0 + 21 + i] = '#';
                    this->screen[140 * 1 + 21 + i - 20] = '#';
                }
            }

            if (this->currentWave.mobsObj[1].nHealth > 0) {
                tmpSize = 24 * this->currentWave.mobsObj[1].nHealth / this->currentWave.mobsObj[1].nMaxHealth;
                if (tmpSize < 1 && tmpSize > -1) tmpSize = 1;
                for (unsigned short int i = 0; i < tmpSize; i++) {
                    this->screen[140 * 0 + 71 + i] = '#';
                    this->screen[140 * 1 + 71 + i - 20] = '#';
                }
            }
            break;

        case 3:
            for (unsigned short int i = 0; i < 24; i++) {
                this->screen[140 * 0 + 19 + i] = ' ';
                this->screen[140 * 1 + 19 + i - 20] = ' ';

                this->screen[140 * 0 + 54 + i] = ' ';
                this->screen[140 * 1 + 54 + i - 20] = ' ';

                this->screen[140 * 0 + 88 + i] = ' ';
                this->screen[140 * 1 + 88 + i - 20] = ' ';
            }

            if (this->currentWave.mobsObj[0].nHealth > 0) {
                tmpSize = 19 * this->currentWave.mobsObj[0].nHealth / this->currentWave.mobsObj[0].nMaxHealth;
                if (tmpSize < 1 && tmpSize > -1) tmpSize = 1;
                for (unsigned short int i = 0; i < tmpSize; i++) {
                    this->screen[140 * 0 + 19 + i] = '#';
                    this->screen[140 * 1 + 19 + i - 20] = '#';
                }
            }

            if (this->currentWave.mobsObj[1].nHealth > 0) {
                tmpSize = 19 * this->currentWave.mobsObj[1].nHealth / this->currentWave.mobsObj[1].nMaxHealth;
                if (tmpSize < 1 && tmpSize > -1) tmpSize = 1;
                for (unsigned short int i = 0; i < tmpSize; i++) {
                    this->screen[140 * 0 + 54 + i] = '#';
                    this->screen[140 * 1 + 54 + i - 20] = '#';
                }
            }

            if (this->currentWave.mobsObj[2].nHealth > 0) {
                tmpSize = 19 * this->currentWave.mobsObj[2].nHealth / this->currentWave.mobsObj[2].nMaxHealth;
                if (tmpSize < 1 && tmpSize > -1) tmpSize = 1;
                for (unsigned short int i = 0; i < tmpSize; i++) {
                    this->screen[140 * 0 + 88 + i] = '#';
                    this->screen[140 * 1 + 88 + i - 20] = '#';
                }
            }
            break;
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

void Engine::captureInputs(Player& player) {

    float fSpeed = 0.01f * player.fMovSpeed;

    if ((GetAsyncKeyState((unsigned short) C_FIRE_WEAPON) & 0x8000) ||
        (GetAsyncKeyState((unsigned short) C_FIRE_WEAPON_ALT) & 0x8000))
		this->shootFromPlayer(player);

    if (GetAsyncKeyState((unsigned short) C_LOOK_LEFT) & 0x8000)
		player.pos.a -= (fSpeed * C_LOOK_SENSI);

	if (GetAsyncKeyState((unsigned short) C_LOOK_RIGHT) & 0x8000)
		player.pos.a += (fSpeed * C_LOOK_SENSI);

	// Handle Forwards movement & collision
	if (GetAsyncKeyState((unsigned short) C_WALK_FORWARD) & 0x8000) {
        this->lastMov = C_WALK_FORWARD;
		player.pos.x += sinf(player.pos.a) * fSpeed;
		player.pos.y += cosf(player.pos.a) * fSpeed;
		if (this->map.smap[(int)player.pos.y * this->map.nMapWidth + (int)player.pos.x] == '#') {
			player.pos.x -= sinf(player.pos.a) * fSpeed;
			player.pos.y -= cosf(player.pos.a) * fSpeed;
		}
	}

    // Handle Right movement & collision
	if (GetAsyncKeyState((unsigned short) C_WALK_RIGHT) & 0x8000) {
        this->lastMov = C_WALK_RIGHT;
		player.pos.x += sinf(player.pos.a + utils::PI/2) * fSpeed;
		player.pos.y += cosf(player.pos.a + utils::PI/2) * fSpeed;
		if (this->map.smap[(int)player.pos.y * this->map.nMapWidth + (int)player.pos.x] == '#') {
			player.pos.x -= sinf(player.pos.a + utils::PI/2) * fSpeed;
			player.pos.y -= cosf(player.pos.a + utils::PI/2) * fSpeed;
		}
	}

    // Handle Left movement & collision
	if (GetAsyncKeyState((unsigned short) C_WALK_LEFT) & 0x8000) {
        this->lastMov = C_WALK_LEFT;
		player.pos.x += sinf(player.pos.a - utils::PI/2) * fSpeed;
		player.pos.y += cosf(player.pos.a - utils::PI/2) * fSpeed;
		if (this->map.smap[(int)player.pos.y * this->map.nMapWidth + (int)player.pos.x] == '#') {
			player.pos.x -= sinf(player.pos.a - utils::PI/2) * fSpeed;
			player.pos.y -= cosf(player.pos.a - utils::PI/2) * fSpeed;
		}
	}

	// Handle backwards movement & collision
	if (GetAsyncKeyState((unsigned short) C_WALK_BACKWARD) & 0x8000) {
        this->lastMov = C_WALK_BACKWARD;
		player.pos.x -= sinf(player.pos.a) * fSpeed;
		player.pos.y -= cosf(player.pos.a) * fSpeed;
		if (this->map.smap[(int)player.pos.y * this->map.nMapWidth + (int)player.pos.x] == '#') {
			player.pos.x += sinf(player.pos.a) * fSpeed;
			player.pos.y += cosf(player.pos.a) * fSpeed;
		}
	}

}

void Engine::shootFromPlayer(Player& player) {
    // Hit-Scan
    if (!player.reloading(this->fElapsedTimeMilliSeconds) &&
        player.nAmmoCount > 0 && !player.shooting(this->fElapsedTimeMilliSeconds)) {

        player.shoot(this->fElapsedTimeMilliSeconds);
        float fEyeX = sinf(player.pos.a);
        float fEyeY = cosf(player.pos.a);

        bool bHitMob = false;
        float fDistance = 0;
        int nTestX;
        int nTestY;

        while (!bHitMob && fDistance < this->fDepth) {
            fDistance += F_RAY_STEP_SIZE;

            nTestX = (int)(player.pos.x + fEyeX * fDistance);
            nTestY = (int)(player.pos.y + fEyeY * fDistance);

            if (nTestX < 0 || nTestX >= fDepth || nTestY < 0 || nTestY >= fDepth)
                fDistance = this->fDepth;
            else
                if (this->map.smobs[nTestY * this->map.nMapWidth + nTestX] == 'X') {
                    bHitMob = true;
                } else if (this->map.smap[nTestY * this->map.nMapWidth + nTestX] == '#') {
                    fDistance = this->fDepth;
                }
        }

        if (bHitMob) {
            for (size_t i = 0; i < this->currentWave.nCount; i++)
                if ((int) this->currentWave.mobsObj[i].pos.x == (int) nTestX &&
                    (int) this->currentWave.mobsObj[i].pos.y == (int) nTestY) {
                    this->currentWave.mobsObj[i].nHealth -= player.aCurrentAmmo.damage;
                    break;
                }
        }
    }
}

void Engine::_createMobsHealthBars() {
    this->_1mobsHealthBar += "                              |.........................................................|                               ";
    this->_1mobsHealthBar += "                              |.........................................................|                               ";
    this->_1mobsHealthBar += "                                                                                                                        ";
    this->_1mobsHealthBar += "                                                                                                                        ";
    this->_1mobsHealthBar += "                                                                                                                        ";
    this->_1mobsHealthBar += "                                                                                                                        ";
    this->_1mobsHealthBar += "                                                                                                                        ";
    this->_1mobsHealthBar += "                                                                                                                        ";
    this->_1mobsHealthBar += "                                                                                                                        ";
    this->_1mobsHealthBar += "                                                                                                                        ";
    this->_1mobsHealthBar += "                                                                                                                        ";
    this->_1mobsHealthBar += "                                                                                                                        ";
    this->_1mobsHealthBar += "                                                                                                                        ";
    this->_1mobsHealthBar += "                                                                                                                        ";
    this->_1mobsHealthBar += "                                                                                                                        ";
    this->_1mobsHealthBar += "                                                                                                                        ";
    this->_1mobsHealthBar += "                                                                                                                        ";
    this->_1mobsHealthBar += "                                                                                                                        ";
    this->_1mobsHealthBar += "                                                                                                                        ";
    this->_1mobsHealthBar += "                                                                                                                        ";
    this->_1mobsHealthBar += "                                                                                                                        ";
    this->_1mobsHealthBar += "                                                                                                                        ";
    this->_1mobsHealthBar += "                                                                                                                        ";
    this->_1mobsHealthBar += "                                                                                                                        ";
    this->_1mobsHealthBar += "                                                                                                                        ";
    this->_1mobsHealthBar += "                                                                                                                        ";
    this->_1mobsHealthBar += "                                                                                                                        ";
    this->_1mobsHealthBar += "                                                                                                                        ";
    this->_1mobsHealthBar += "                                                                                                                        ";
    this->_1mobsHealthBar += "                                                                                                                        ";
    this->_1mobsHealthBar += "                                                                                                                        ";
    this->_1mobsHealthBar += "                                                                                                                        ";
    this->_1mobsHealthBar += "                                                                                                                        ";
    this->_1mobsHealthBar += "                                                                                                                        ";
    this->_1mobsHealthBar += "                                                                                                                        ";
    this->_1mobsHealthBar += "                                                                                                                        ";
    this->_1mobsHealthBar += "                                                                                                                        ";
    this->_1mobsHealthBar += "                                                                                                                        ";
    this->_1mobsHealthBar += "                                                                                                                        ";
    this->_1mobsHealthBar += "                                                                                                                        ";

    this->_2mobsHealthBar += "                    |........................|                        |........................|                        ";
    this->_2mobsHealthBar += "                    |........................|                        |........................|                        ";
    this->_2mobsHealthBar += "                                                                                                                        ";
    this->_2mobsHealthBar += "                                                                                                                        ";
    this->_2mobsHealthBar += "                                                                                                                        ";
    this->_2mobsHealthBar += "                                                                                                                        ";
    this->_2mobsHealthBar += "                                                                                                                        ";
    this->_2mobsHealthBar += "                                                                                                                        ";
    this->_2mobsHealthBar += "                                                                                                                        ";
    this->_2mobsHealthBar += "                                                                                                                        ";
    this->_2mobsHealthBar += "                                                                                                                        ";
    this->_2mobsHealthBar += "                                                                                                                        ";
    this->_2mobsHealthBar += "                                                                                                                        ";
    this->_2mobsHealthBar += "                                                                                                                        ";
    this->_2mobsHealthBar += "                                                                                                                        ";
    this->_2mobsHealthBar += "                                                                                                                        ";
    this->_2mobsHealthBar += "                                                                                                                        ";
    this->_2mobsHealthBar += "                                                                                                                        ";
    this->_2mobsHealthBar += "                                                                                                                        ";
    this->_2mobsHealthBar += "                                                                                                                        ";
    this->_2mobsHealthBar += "                                                                                                                        ";
    this->_2mobsHealthBar += "                                                                                                                        ";
    this->_2mobsHealthBar += "                                                                                                                        ";
    this->_2mobsHealthBar += "                                                                                                                        ";
    this->_2mobsHealthBar += "                                                                                                                        ";
    this->_2mobsHealthBar += "                                                                                                                        ";
    this->_2mobsHealthBar += "                                                                                                                        ";
    this->_2mobsHealthBar += "                                                                                                                        ";
    this->_2mobsHealthBar += "                                                                                                                        ";
    this->_2mobsHealthBar += "                                                                                                                        ";
    this->_2mobsHealthBar += "                                                                                                                        ";
    this->_2mobsHealthBar += "                                                                                                                        ";
    this->_2mobsHealthBar += "                                                                                                                        ";
    this->_2mobsHealthBar += "                                                                                                                        ";
    this->_2mobsHealthBar += "                                                                                                                        ";
    this->_2mobsHealthBar += "                                                                                                                        ";
    this->_2mobsHealthBar += "                                                                                                                        ";
    this->_2mobsHealthBar += "                                                                                                                        ";
    this->_2mobsHealthBar += "                                                                                                                        ";
    this->_2mobsHealthBar += "                                                                                                                        ";

    this->_3mobsHealthBar += "                  |........................|         |........................|        |........................|       ";
    this->_3mobsHealthBar += "                  |........................|         |........................|        |........................|       ";
    this->_3mobsHealthBar += "                                                                                                                        ";
    this->_3mobsHealthBar += "                                                                                                                        ";
    this->_3mobsHealthBar += "                                                                                                                        ";
    this->_3mobsHealthBar += "                                                                                                                        ";
    this->_3mobsHealthBar += "                                                                                                                        ";
    this->_3mobsHealthBar += "                                                                                                                        ";
    this->_3mobsHealthBar += "                                                                                                                        ";
    this->_3mobsHealthBar += "                                                                                                                        ";
    this->_3mobsHealthBar += "                                                                                                                        ";
    this->_3mobsHealthBar += "                                                                                                                        ";
    this->_3mobsHealthBar += "                                                                                                                        ";
    this->_3mobsHealthBar += "                                                                                                                        ";
    this->_3mobsHealthBar += "                                                                                                                        ";
    this->_3mobsHealthBar += "                                                                                                                        ";
    this->_3mobsHealthBar += "                                                                                                                        ";
    this->_3mobsHealthBar += "                                                                                                                        ";
    this->_3mobsHealthBar += "                                                                                                                        ";
    this->_3mobsHealthBar += "                                                                                                                        ";
    this->_3mobsHealthBar += "                                                                                                                        ";
    this->_3mobsHealthBar += "                                                                                                                        ";
    this->_3mobsHealthBar += "                                                                                                                        ";
    this->_3mobsHealthBar += "                                                                                                                        ";
    this->_3mobsHealthBar += "                                                                                                                        ";
    this->_3mobsHealthBar += "                                                                                                                        ";
    this->_3mobsHealthBar += "                                                                                                                        ";
    this->_3mobsHealthBar += "                                                                                                                        ";
    this->_3mobsHealthBar += "                                                                                                                        ";
    this->_3mobsHealthBar += "                                                                                                                        ";
    this->_3mobsHealthBar += "                                                                                                                        ";
    this->_3mobsHealthBar += "                                                                                                                        ";
    this->_3mobsHealthBar += "                                                                                                                        ";
    this->_3mobsHealthBar += "                                                                                                                        ";
    this->_3mobsHealthBar += "                                                                                                                        ";
    this->_3mobsHealthBar += "                                                                                                                        ";
    this->_3mobsHealthBar += "                                                                                                                        ";
    this->_3mobsHealthBar += "                                                                                                                        ";
    this->_3mobsHealthBar += "                                                                                                                        ";
    this->_3mobsHealthBar += "                                                                                                                        ";
    this->_3mobsHealthBar += "                                                                                                                        ";
    this->_3mobsHealthBar += "                                                                                                                        ";
}
