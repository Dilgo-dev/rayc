#include <SDL.h>
#include "raycasting.h"

void render_ray(SDL_Renderer* renderer, int screen_x, float distance) {
    float wall_height = (WINDOW_HEIGHT * 1.0) / distance;

    float wall_top = (WINDOW_HEIGHT - wall_height) / 2;
    float wall_bottom = wall_top + wall_height;

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawLine(renderer, screen_x, wall_top, screen_x, wall_bottom);
    return;
}