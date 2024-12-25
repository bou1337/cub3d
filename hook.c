#include  "cub3d.h"



int key_code(int keycode, t_data *data)
{
    char **map = data->map;

    int new_x = data->player_x;
    int new_y = data->player_y;

    if (keycode == XK_Escape)
    {
        exit(0); 
    }
    else if (keycode == XK_Left)
    {
        new_x -= speed; 
    }
    else if (keycode == XK_Right)
    {
        new_x += speed; 
    }
    else if (keycode == XK_Up)
    {
        new_y -= speed; 
    }
    else if (keycode == XK_Down)
    {
        new_y += speed;
    }

    if (map[new_y] && map[new_y][new_x] != '1' && new_x >= 0 && new_y >= 0)
    {
        data->map[data->player_y][data->player_x] = '0';  
        data->map[new_y][new_x] = 'P';                   
        data->player_x = new_x;                    
        data->player_y = new_y;                     
    }
    mlx_clear_window(data->mlx, data->win) ;
    draw_map(data); 
    mlx_put_image_to_window(data->mlx, data->win, data->img, 0 , 0) ;
   

    return (0);
}