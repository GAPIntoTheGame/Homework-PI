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

bool init()
{
	bool success = true;

	SDL_Init(SDL_INIT_VIDEO); // passage of time

	if (SDL_Init(SDL_INIT_VIDEO) != 0) // test if above works
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		success = false;
	}

	else
	{
		gWindow = SDL_CreateWindow("Moving Red Square", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);	// Create window.

		if (gWindow == NULL)	// Check window initialization.
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			success = false;
		}

		else
		{
			gScreenSurface = SDL_GetWindowSurface(gWindow);	// Get window surface.	

			if (gScreenSurface == NULL)	// Check surface initialization.
			{
				printf("Surface could not be created! SDL_Error: %s\n", SDL_GetError());
				success = false;
			}

			else
			{
				gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);	// Create renderer for window.

				if (gRenderer == NULL)	// Check renderer initialization.
				{
					printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
					success = false;
				}
			}
		}
	}

	return success;
}

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
	init();	

	if (!init())
	{
		printf("Failed to initialize!\n");
	}

	else
	{
		unsigned int Blue = SDL_MapRGB(gScreenSurface->format, 65, 105, 255);	// Set the Blue Background (65,105,225)
		unsigned int Red = SDL_MapRGB(gScreenSurface->format, 255, 0, 0);		// Set Red color (255,0,0)

		SDL_Rect redSquare;
		redSquare.x = SCREEN_WIDTH / 6;
		redSquare.y = 1;
		redSquare.w = 50;
		redSquare.h = 50;

		float xSpeed = 5, ySpeed = 0, e = 1, g = 0.098, x = redSquare.x, y = redSquare.y, t_1 = 0, t = 0, vy = 0;;
		int sign = 0, p = 0;


		for (int i = 0; i < 300000; i++)
		{
			if (redSquare.y >= SCREEN_HEIGHT - 350 && p==0)
			{
				vy = 2*g * t + ySpeed;
				p = 1;
			}

			/*
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
			else*//* if (redSquare.y <= 0)
			{
				ySpeed = abs(g*t*t + ySpeed * t) * e;
				t = 0;
				y = redSquare.y;
			}
			else*/ if (redSquare.y >= SCREEN_HEIGHT - 50)
			{
				vy = abs(vy)*e;
				ySpeed = -abs(vy);
				y = redSquare.y;
				t = 1;
			}
			//redSquare.x = xSpeed*t_1 + sign * mu*t_prima + x;
			redSquare.y = ySpeed * t + g * t*t + y;
			
			SDL_SetRenderDrawColor(gRenderer, 65, 105, 255, 255);
			SDL_RenderClear(gRenderer);

			SDL_SetRenderDrawColor(gRenderer, 255, 0, 0, 255);
			SDL_RenderFillRect(gRenderer, &redSquare);

			SDL_RenderPresent(gRenderer);

			SDL_Delay(10);
			t++;
		}

		close();

		return 0;
	}


	system("pasue");
	return 0;
}