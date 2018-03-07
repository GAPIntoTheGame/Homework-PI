#include "SDL/include/SDL.h"  // It only woks on x86
#include <iostream>
#include <cstdio>
using namespace std;

#pragma comment(lib, "SDL/libx86/SDL2.lib")
#pragma comment(lib, "SDL/libx86/SDL2main.lib")


const int SCREEN_WIDTH = 1620;
const int SCREEN_HEIGHT = 780;

SDL_Window* gWindow = nullptr;		// Window itself
SDL_Renderer* gRenderer = nullptr;   // What appears
SDL_Surface* gScreenSurface = nullptr;   // Background


void close()	// SDL shutdown function.
{
	SDL_FreeSurface(gScreenSurface);	// Deallocate surface.
	gScreenSurface = NULL;

	SDL_DestroyWindow(gWindow);		// Destroy window.
	gWindow = NULL;

	SDL_Quit();						// Quit SDL subsystems.
}

int main(int argc, char* argv[])
{

	SDL_Init(SDL_INIT_VIDEO); // passage of time

	gWindow = SDL_CreateWindow("Moving Red Square", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);	// Create window.

	gScreenSurface = SDL_GetWindowSurface(gWindow);	// Get window surface.	

	gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);	// Create renderer for window.

		unsigned int Blue = SDL_MapRGB(gScreenSurface->format, 65, 105, 255);	// Set the Blue Background (65,105,225)
		unsigned int Red = SDL_MapRGB(gScreenSurface->format, 255, 0, 0);		// Set Red color (255,0,0)

		SDL_Rect redSquare;
		redSquare.x = SCREEN_WIDTH / 2;
		redSquare.y = SCREEN_HEIGHT * (3 / 2);
		redSquare.w = 50;
		redSquare.h = 50;

		float xSpeed = 0, ySpeed = 0;
		float e = 1, g = 0.098, vy_1 = 0, vy_2 = 0, mu = 0.1;
		float x = redSquare.x, y = redSquare.y;
		int sign = 0, p = 0, t = 0, t_1 = 0, t_prima = 0;


		for (int i = 0; i < 300000; i++)
		{
			if (redSquare.y >= SCREEN_HEIGHT - 50 && p==0)
			{
				vy_1 = 2*g * t + ySpeed;
				p = 1;
			}

			
			if (redSquare.x <= 0)
			{
				xSpeed = abs(xSpeed);
				sign = -1;
				t_1 = 0;
				x = redSquare.x;
			}
			else if (redSquare.x >= SCREEN_WIDTH - 50)
			{
				xSpeed = -abs(xSpeed);
				sign = 1;
				t_1 = 0;
				x = redSquare.x;
			}
			else if (redSquare.y <= 0)
			{
				vy_2 = 2 * g*t + ySpeed * e;
				ySpeed = abs(vy_2);
				t = 1;
				y = redSquare.y;
			}
			else if (redSquare.y >= SCREEN_HEIGHT - 50)
			{
				vy_1 = abs(vy_1) *e;
				ySpeed = -abs(vy_1);
				y = redSquare.y;
				t = 1;
			}
			redSquare.x = xSpeed * t_1 + sign * mu*t_prima*t_prima + x;
			redSquare.y = ySpeed * t + g * t*t + y;
			
			if (redSquare.y >= SCREEN_HEIGHT - 50 && abs(vy_1) < 0.5)
			{
				t_prima++;
				if (abs(vy_1) == abs(mu*t_prima))
				{
					return 0;
				}
			}

			SDL_SetRenderDrawColor(gRenderer, 65, 105, 255, 255);
			SDL_RenderClear(gRenderer);

			SDL_SetRenderDrawColor(gRenderer, 255, 0, 0, 255);
			SDL_RenderFillRect(gRenderer, &redSquare);

			SDL_RenderPresent(gRenderer);

			SDL_Delay(10);
			t++;
			t_1++;
		}

		close();

		return 0;

	system("pasue");
	return 0;
}