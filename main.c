#include "cub3d.h"



 char *map_string = 
        "11111111111111111111\n"
        "10000000000000000001\n"
        "10000000000000000001\n"
        "10000000P00000000001\n"
        "10000000000000000001\n"
        "10000000000000000001\n"
        "10000000000000000001\n"
        "10000000000000000001\n"
        "10000000000000000001\n"
        "10000000000000000001\n"
        "10000000000000000001\n"
        "10000000000000000001\n"
        "10000000000000000001\n"
        "10000000000000000001\n"
        "10000000000000000001\n"
        "10000000000000000001\n"
        "10000000000000000001\n"
        "10000000000000000001\n"
        "11111111111111111111";



int main(void)
{

    t_data data ;
    data.map = ft_split(map_string, '\n');
    data.mlx = mlx_init() ;
    data.win = mlx_new_window(data.mlx, X, Y,"CUB3D") ;
    data.img = mlx_new_image(data.mlx, X, Y) ;
    data.img_data = mlx_get_data_addr(data.img, &data.bpp,&data.line_len, &data.endian);
    draw_map(&data);
    mlx_key_hook(data.win, key_code,&data ) ;
    mlx_put_image_to_window(data.mlx, data.win, data.img, 0 , 0) ;

    mlx_loop(data.mlx) ;
}

