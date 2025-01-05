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
    double new_x = data->player_x;
    double new_y = data->player_y;

    if (keycode == XK_Escape)
        exit(0);
    else if (keycode == XK_Left)
         data->teta-= 0.1;
    else if (keycode == XK_Right)
        data->teta += 0.1;
    else if (keycode == W_KEY)
    {
        new_x = (data->player_x  +10*cos(data->teta)) ;
        new_y = (data->player_y +10*sin(data->teta)) ;
    }
    else if (keycode == S_KEY)
    {
        new_x = (data->player_x  -10*cos(data->teta)) ;
        new_y = (data->player_y  - 10*sin(data->teta)) ;
    }
     else if (keycode == A_KEY)
    {
        new_x = (data->player_x  +10*cos(data->teta+M_PI/2)) ;
        new_y = (data->player_y +10*sin(data->teta+M_PI/2)) ;
    }

    else if (keycode == D_KEY)
    {
        new_x = (data->player_x  -10*cos(data->teta+M_PI/2)) ;
        new_y = (data->player_y  - 10*sin(data->teta+ M_PI/2)) ;
    }
    if (pixel_inside(data, new_x, new_y))
    {
        data->player_x = new_x;
        data->player_y = new_y;
    }

    return (0);
}


int update_game(t_data *data)
{

     mlx_clear_window(data->mlx, data->win);
    draw_map(data);
    mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}


