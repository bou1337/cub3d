#include "cub3d.h"

char *map_string = 
        "11111111111111111111\n"
        "11000000000000000011\n"
        "10000000000000000001\n"
        "10000000P00000000001\n"
        "10000000011111111111\n"
        "10000000000000000001\n"
        "10000000000000000001\n"
        "10000000000000000001\n"
        "10000000000000000001\n"
        "10000000000000111111\n"
        "10000000000000000001\n"
        "10000000000000000001\n"
        "10000000000000000001\n"
        "10000000001000000001\n"
        "10000000000111111111\n"
        "10000000000000000001\n"
        "11111111111100000001\n"
        "11000000000000000011\n"
        "11000000000000000011\n"
        "11111111111111111111\n";


int main(void)
{
    t_data data;


    t_rays *ray=malloc(sizeof(t_rays)*Y) ;
    data.ray=ray ;
    data.map = ft_split(map_string, '\n');

    data.mlx = mlx_init();
    if (!data.mlx)
        return (1);
    data.win = mlx_new_window(data.mlx, X, Y, "CUB3D");
    if (!data.win)
        return (1);
    data.img = mlx_new_image(data.mlx, X, Y);
    if (!data.img)
        return (1);
    data.img_data = mlx_get_data_addr(data.img, &data.bpp, &data.line_len, &data.endian);
    data.player_x = 10*SIZE ;
    data.player_y = 10*SIZE ;
    data.planeX = 0.66 ;
    data.planeY = 0 ;
    data.dirX = -1 ;
    data.dirY = 0 ;
    data.teta = M_PI/2;
   // draw_map(&data);

     mlx_loop_hook(data.mlx , update_game ,&data) ;
    mlx_hook(data.win,3, 1L << 0, key_code, &data);
     mlx_hook(data.win,2, 1L << 0, key_code, &data);
   
    mlx_loop(data.mlx);
    return (0);
}
