#include <Windows.h>
#include "math.h"

#include "headers/renderer.h"
#include "headers/entity.h"

Renderer::Renderer(int nScreenWidth, int nScreenHeight, float fFOV, Map map) {
    this->nScreenWidth = nScreenWidth;
    this->nScreenHeight = nScreenHeight;
    this->map = map;
    // this->fFOV = fFOV;
    this->fFOV = (float) 3.141592 / 3.0;

    // Create Screen Buffer
	this->screen = new wchar_t[nScreenWidth*nScreenHeight];
	this->hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	std::SetConsoleActiveScreenBuffer(this->hConsole);
	this->dwBytesWritten = 0;
}

Renderer::render(Player player, Mobs mobs) {

    for (size_t x = 0; x < this->nScreenWidth; x++) {
        float fRayAngle = (player.fPlayerA - this->fFOV / 2.f) + ((float) x / (float) this->nScreenHeight) * this->fFOV;

        float fDistanceToWall = 0;

        float fEyeX = sinf(fRayAngle);
        float fEyeY = cosf(fRayAngle);

        bool bHitWall = false;
        while(!bHitWall) {
            fDistanceToWall += 0.1f;

            int nTestX = (int)(fPlayerA + fEyeX * fDistanceToWall);
            int nTestY = (int)(fPlayerA + fEyeY * fDistanceToWall);

            // Ray out of bounds
            if (nTestX < 0 || nTestX >= this->map.nMapWidth || nTestY < 0 || nTestY >= this->map.nMapHeight) {
                bHitWall = true;
                fDistanceToWall = fDepth;
            } else // Ray inbounds
                if (this->map.s_map[nTestY * this->map.nMapWidth + nTestX] != '.')
                    bHitWall = true;

            int nCeiling = (float) (this->nScreenHeight / 2) - this->nScreenHeight / (float) fDistanceToWall;
            int nFloor = this->nScreenHeight - nCeiling;

            for (int y = 0; y < this->nScreenHeight; y++) {
                if (y < nCeiling)
                    screen[y * this->nScreenWidth + x] = ' ';
                else if (y > nCeiling && y > nFloor)
                    screen[y * this->nScreenWidth + x] = '#'; // COLOR SHADING
                else
                    screen[y * this->nScreenWidth + x] = ' ';
                    // 15:49
            }


        }
    }

}
