#include <math.h>
#include "raycasting.h"

float cast_ray(int map[4][4], float pos_x, float pos_y, float ray_angle) {
    // Direction du rayon
    float ray_dx = cos(ray_angle);
    float ray_dy = sin(ray_angle);
    
    // Position actuelle dans la grille
    int map_x = (int)pos_x;
    int map_y = (int)pos_y;
    
    // Distance jusqu'aux prochaines lignes de grille
    float delta_dist_x = fabs(1.0f / ray_dx);
    float delta_dist_y = fabs(1.0f / ray_dy);
    
    // Direction du pas et distance initiale
    float side_dist_x, side_dist_y;
    int step_x, step_y;
    
    if (ray_dx < 0) {
        step_x = -1;
        side_dist_x = (pos_x - map_x) * delta_dist_x;
    } else {
        step_x = 1;
        side_dist_x = (map_x + 1.0f - pos_x) * delta_dist_x;
    }
    
    if (ray_dy < 0) {
        step_y = -1;
        side_dist_y = (pos_y - map_y) * delta_dist_y;
    } else {
        step_y = 1;
        side_dist_y = (map_y + 1.0f - pos_y) * delta_dist_y;
    }
    
    // Algorithme DDA
    int hit = 0;
    float perp_wall_dist;
    
    while (hit == 0) {
        // Aller à la prochaine intersection de grille
        if (side_dist_x < side_dist_y) {
            side_dist_x += delta_dist_x;
            map_x += step_x;
            perp_wall_dist = (map_x - pos_x + (1 - step_x) / 2) / ray_dx;
        } else {
            side_dist_y += delta_dist_y;
            map_y += step_y;
            perp_wall_dist = (map_y - pos_y + (1 - step_y) / 2) / ray_dy;
        }
        
        // Vérifier les limites
        if (map_x < 0 || map_x >= 4 || map_y < 0 || map_y >= 4) {
            return MAX_DISTANCE;
        }
        
        // Vérifier si on touche un mur
        if (map[map_y][map_x] == 1) {
            hit = 1;
        }
    }
    
    return fabs(perp_wall_dist);
}