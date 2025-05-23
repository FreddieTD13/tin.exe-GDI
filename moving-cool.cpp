#include <windows.h>
#include <stdlib.h> // For rand()
#include <time.h>   // For seeding rand()

int main() {
    HDC hdc;
    int w = GetSystemMetrics(SM_CXSCREEN); // Screen width
    int h = GetSystemMetrics(SM_CYSCREEN); // Screen height
    int y;
    int direction; // 0 for left-to-right, 1 for right-to-left

    srand(time(NULL)); // Seed the random number generator

    while (1) {
        hdc = GetDC(0);
        y = rand() % h; // Random Y position for the strip
        direction = rand() % 2; // Randomly choose direction (0 or 1)

        if (direction == 0) { // Move left-to-right
            BitBlt(hdc, 1, y, w, 1000, hdc, 0, y, SRCCOPY);
        }
        else { // Move right-to-left
            BitBlt(hdc, 0, y, w, 1000, hdc, 1, y, SRCCOPY);
        }
        Sleep(0);
        ReleaseDC(0, hdc);
    }
}
