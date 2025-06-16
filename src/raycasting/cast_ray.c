#include <math.h>
#include "raycasting.h"

float cast_ray(int map[4][4], float pos_x, float pos_y, float ray_angle) {
    // Calculate direction of ray
    float ray_dx = cos(ray_angle);
    float ray_dy = sin(ray_angle);

    // Rayon start position
    float ray_x = pos_x;
    float ray_y = pos_y;

    while (distance < MAX_DISTANCE) {

        // Move the rayon forward
        ray_x += ray_dx * STEP_SIZE;
        ray_y += ray_dy * STEP_SIZE;

        // Convert into map position
        int grid_x = (int)ray_x;
        int grid_y = (int)ray_y;

        // Check if it's out of bounderies
        if (grid_x < 0 || grid_x >= 4 || grid_y < 0 || grid_y >= 4) return MAX_DISTANCE;

        // Check if ray touch a wall
        if (map[grid_y][grid_x] == 1) {
            return sqrt(pow(ray_x - pos_x, 2) + pow(ray_y - pos_y, 2));
        }

    }
}