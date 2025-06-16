#include <SDL.h>

#ifndef RAYCASTING_H
#define RAYCASTING_H

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480
#define STEP_SIZE 0.2f
#define MAX_DISTANCE 100.0f

float cast_ray(int map[4][4], float pos_x, float pos_y, float ray_angle);
void render_ray(SDL_Renderer* renderer, int screen_x, float distance);

#endif