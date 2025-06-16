#include <stdio.h>
#include <stdbool.h>
#include <SDL.h>
#include <SDL_timer.h>
#include <math.h>
#include "raycasting.h"

#define MAP_WIDTH 4
#define MAP_HEIGHT 4
#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

int main(void)
{
    int map[MAP_HEIGHT][MAP_WIDTH] = {{1, 1, 1, 1},
                     {1, 0, 0, 1},
                     {1, 0, 0, 1},
                     {1, 1, 1, 1}};

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER) != 0)
    {
        printf("error initializing SDL: %s\n", SDL_GetError());
        return 1;
    }

    // Create a window
    SDL_Window* window = SDL_CreateWindow("Rayc in C 🦉",
                                       SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED,
                                       WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    if (!window)
    {
        printf("error creating window: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }


    // Create a renderer for the window
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (!renderer)
    {
        printf("error creating renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Main loop
    bool running = true;
    while (running)
    {
        SDL_Event e;
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                running = false;
                break;
            }
        }
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Noir
        SDL_RenderClear(renderer);

        float player_x = 1.5f;
        float player_y = 2.0f;
        float player_angle = 0.0f;

        float distance = cast_ray(map, player_x, player_y, 0);

        printf("Distance between point and player found at: %f\n", distance);

        // RENDER PHASE
        // Find wall height
        float wall_height = (WINDOW_HEIGHT * 1.0) / distance;

        // Centre wall
        int wall_top = (WINDOW_HEIGHT - wall_height) / 2;
        int wall_bottom = wall_top + wall_height;

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDrawLine(renderer, WINDOW_WIDTH / 2, wall_top, WINDOW_WIDTH / 2, wall_bottom);

        SDL_RenderPresent(renderer);
    }

    // Clean up resources before exiting
    SDL_DestroyWindow(window);
    SDL_Quit();
}