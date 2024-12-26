#include "cub3d.h"

char *map_string = 
        "11111111111111111111\n"
        "10000000000000000001\n"
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
        "10000000000000000001\n"
        "10000000000111111111\n"
        "10000000000000000001\n"
        "11111111111100000001\n"
        "10000000000000000001\n"
        "11111111111111111111\n";

int main(void)
{
    t_data data;
    int **tab ;
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
    data.player_x = 1*SIZE ;
    data.player_y = 1*SIZE ;

    draw_map(&data);
    mlx_key_hook(data.win, key_code, &data);
    mlx_loop(data.mlx);
    return (0);
}
