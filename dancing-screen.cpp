#include <Windows.h>
#include <iostream>
#include <ctime>

int main() {
    srand(static_cast<unsigned int>(time(0)));

    while (1) {
        HDC hdc = GetDC(0);

        int screenWidth = GetSystemMetrics(SM_CXSCREEN);
        int screenHeight = GetSystemMetrics(SM_CYSCREEN);

        int chunkWidth = screenWidth / 4;
        int chunkHeight = screenHeight / 4;

        int sourceX = rand() % (screenWidth - chunkWidth);
        int sourceY = rand() % (screenHeight - chunkHeight);

        int offsetX = (rand() % 7) - 3; // Random value from -3 to 3
        int offsetY = (rand() % 7) - 3; // Random value from -3 to 3

        int destX = sourceX + offsetX;
        int destY = sourceY + offsetY;

        // Ensure the destination stays within the screen bounds
        if (destX < 0) destX = 0;
        if (destY < 0) destY = 0;
        if (destX + chunkWidth > screenWidth) destX = screenWidth - chunkWidth;
        if (destY + chunkHeight > screenHeight) destY = screenHeight - chunkHeight;

        BitBlt(hdc, destX, destY, chunkWidth, chunkHeight, hdc, sourceX, sourceY, SRCCOPY);
        ReleaseDC(0, hdc);
    }
    return 0;
}
