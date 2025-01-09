

#include "cub3d.h"

void dir_r(t_rays *ray, double angl) {
    // Determine if the ray is moving downwards (angle between pi/2 and 3pi/2)
    ray->down = (angl < M_PI) ? 1 : 0;
    
    // Determine if the ray is moving rightwards (angle between -pi/2 and pi/2)
    ray->right = (angl > M_PI / 2 && angl < 3 * M_PI / 2) ? 0 : 1;
}
