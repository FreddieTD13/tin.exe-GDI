#include <windows.h>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <thread>
#include <chrono>

void DrawRandomIcons() {
// Get device context for the screen
HDC hdc = GetDC(NULL);
if (!hdc) return;

// Get screen width and height
int screenWidth = GetSystemMetrics(SM_CXSCREEN);
int screenHeight = GetSystemMetrics(SM_CYSCREEN);

// Randomly choose the position
int x = rand() % screenWidth;
int y = rand() % screenHeight;

// Randomly choose an icon: ERROR, WARNING, INFORMATION, or APPLICATION
HICON hIcon;
int iconChoice = rand() % 4;

switch (iconChoice) {
case 0:
hIcon = LoadIcon(NULL, IDI_ERROR); // Error icon
break;
case 1:
hIcon = LoadIcon(NULL, IDI_WARNING); // Warning icon
break;
case 2:
hIcon = LoadIcon(NULL, IDI_INFORMATION); // Information icon
break;
case 3:
hIcon = LoadIcon(NULL, IDI_APPLICATION); // Application icon
break;
default:
hIcon = LoadIcon(NULL, IDI_ERROR); // Default to error icon
break;
}

// If the icon is loaded, draw it on the screen
if (hIcon) {
DrawIcon(hdc, x, y, hIcon);
}

// Release device context
ReleaseDC(NULL, hdc);
}

void MoveRandomScreenChunks() {
while (true) {
HDC hdc = GetDC(0);

int screenWidth = GetSystemMetrics(SM_CXSCREEN);
int screenHeight = GetSystemMetrics(SM_CYSCREEN);

int chunkWidth = screenWidth / 2;
int chunkHeight = screenHeight / 2;

int sourceX = rand() % (screenWidth - chunkWidth);
int sourceY = rand() % (screenHeight - chunkHeight);

int offsetX = (rand() % 11) - 5; // Random value from -5 to 5
int offsetY = (rand() % 11) - 5; // Random value from -5 to 5

int destX = sourceX + offsetX;
int destY = sourceY + offsetY;

if (destX < 0) destX = 0;
if (destY < 0) destY = 0;
if (destX + chunkWidth > screenWidth) destX = screenWidth - chunkWidth;
if (destY + chunkHeight > screenHeight) destY = screenHeight - chunkHeight;

BitBlt(hdc, destX, destY, chunkWidth, chunkHeight, hdc, sourceX, sourceY, SRCCOPY);
ReleaseDC(0, hdc);

std::this_thread::sleep_for(std::chrono::milliseconds(0)); // Delay for visual effect
}
}

int main() {
srand(static_cast<unsigned int>(time(0)));

// Start threads to move screen chunks and draw random icons
std::thread moveChunksThread(MoveRandomScreenChunks);
std::thread drawIconsThread([]() {
while (true) {
DrawRandomIcons(); // Call to draw random icon at random positions
std::this_thread::sleep_for(std::chrono::milliseconds(50)); // Wait for 500ms before drawing another icon
}
});

// Detach the threads so they can run concurrently
moveChunksThread.detach();
drawIconsThread.detach();

// Keep the main thread running to let other threads do their work
std::cin.get();

return 0;
}
