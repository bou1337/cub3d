

#include "cub3d.h"


void dir_r(t_dir *dir, double angl) {
    dir->down = (angl < M_PI) ? 1 : -1;
    dir->right = (angl > M_PI / 2 && angl < 3 * M_PI / 2) ? -1 : 1;
}