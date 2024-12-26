#include "cub3d.h"

int    pixel_inside(t_data *data, int x, int y)
{
    int i;
    int j;

    j = ( x) / SIZE;
    i = ( y) / SIZE;
    if (data->map[i][j] == '1')
        return (0);
    return (1);
}
int key_code(int keycode, t_data *data)
{
    char **map = data->map;
    int new_x = data->player_x;
    int new_y = data->player_y;

    if (keycode == XK_Escape)
        exit(0);
    else if (keycode == XK_Left)// && map[data->player_y/SIZE][data->player_x/SIZE - 1] != '1')
        new_x -= 1;
    else if (keycode == XK_Right)// && map[data->player_y/SIZE][data->player_x/SIZE + 1] != '1')
        new_x += 1;
    else if (keycode == XK_Up)// && map[data->player_y/SIZE - 1][data->player_x/SIZE] != '1')
        new_y -= 1;
    else if (keycode == XK_Down)// && map[data->player_y/SIZE + 1][data->player_x/SIZE] != '1')
        new_y += 1;
    printf("%d %d\n", new_x, new_y);
    if (pixel_inside(data, new_x, new_y))
    {
        data->player_x = new_x;
        data->player_y = new_y;
    }
    mlx_clear_window(data->mlx, data->win);
    draw_map(data);
    mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);

    return (0);
}
