#include <stdio.h>
#include <stdbool.h>
#include <SDL.h>
#include <SDL_timer.h>
#include <math.h>

#define MAP_WIDTH 4
#define MAP_HEIGHT 4

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
                                       640, 480, 0);
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
    // RAYCASTING TEST

    // Player position
    float player_x = 1.5f;
    float player_y = 2.5f;
    float player_angle = 0.0f;

    // Cast a rayon
    float ray_angle = M_PI / 4; // 45 degrés
    float ray_dx = cos(ray_angle);
    float ray_dy = sin(ray_angle);

    // Start of rayon
    float ray_x = player_x;
    float ray_y = player_y;

    // Send rayon
    float step_size = 0.1f;

    while (1) {
        // Move the rayon forward
        ray_x += ray_dx * step_size;
        ray_y += ray_dy * step_size;

        // Convert float position into array position
        int grid_x = (int)ray_x;
        int grid_y = (int)ray_y;

        // Did we step out of boundaries ?
        if (grid_x < 0 || grid_x >= MAP_WIDTH || grid_y < 0 || grid_y >= MAP_HEIGHT) {
            break;
        }

        // If we found a wall in the array position then
        if (map[grid_y][grid_x] == 1) {
            // We calculate the distance between the wall and the player
            float distance = sqrt(pow(ray_x - player_x, 2) + pow(ray_y - player_y, 2));
            printf("Distance between point and player found at: %f", distance);
            break;
        }
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

        // Draw test line
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDrawLine(renderer, 10, 10, 500, 500);

        SDL_RenderPresent(renderer);
    }

    // Clean up resources before exiting
    SDL_DestroyWindow(window);
    SDL_Quit();
}