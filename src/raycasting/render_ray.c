#include <SDL.h>
#include "raycasting.h"

void render_ray(SDL_Renderer* renderer, int screen_x, float distance) {
    float wall_height = (WINDOW_HEIGHT * 1.0) / distance;

    float wall_top = (WINDOW_HEIGHT - wall_height) / 2;
    float wall_bottom = wall_top + wall_height;

    int brightness = 255 - (int)(distance * 50);
    if (brightness < 50) brightness = 50;
    if (brightness > 255) brightness = 255;

    SDL_SetRenderDrawColor(renderer, brightness, brightness, brightness, brightness);
    SDL_RenderDrawLine(renderer, screen_x, wall_top, screen_x, wall_bottom);
    return;
}