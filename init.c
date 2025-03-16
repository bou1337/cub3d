
#include "cub3d.h"

static int	init_img(t_data *data)
{
	data->img.img = mlx_new_image(data->mlx,1900,1000);
	if (!data->img.img)
		return (1);
	data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bpp,
			&data->img.line, &data->img.endian);
	if (!data->img.addr)
		return (1);
	return (0);
}
static int	load_east_and_west_textures(t_data *data)
{
	data->textures.east.img = mlx_xpm_file_to_image(data->mlx,
			data->textures_path[EA], &data->textures.east.w,
			&data->textures.east.h);
	if (!data->textures.east.img)
		return (1);
	data->textures.east.addr = mlx_get_data_addr(data->textures.east.img,
			&data->textures.east.bpp, &data->textures.east.line,
			&data->textures.east.endian);
	data->textures.west.img = mlx_xpm_file_to_image(data->mlx,
			data->textures_path[WE], &data->textures.west.w,
			&data->textures.west.h);
	if (!data->textures.west.img)
		return (1);
	data->textures.west.addr = mlx_get_data_addr(data->textures.west.img,
			&data->textures.west.bpp, &data->textures.west.line,
			&data->textures.west.endian);
	return (0);
}

static int	load_all_textures(t_data *data)
{
	
	int	ret;

	data->textures.north.img = mlx_xpm_file_to_image(data->mlx,
			data->textures_path[NO], &data->textures.north.w,
			&data->textures.north.h);
	if (!data->textures.north.img)
		return (1);
	data->textures.north.addr = mlx_get_data_addr(data->textures.north.img,
			&data->textures.north.bpp, &data->textures.north.line,
			&data->textures.north.endian);
	data->textures.south.img = mlx_xpm_file_to_image(data->mlx,
			data->textures_path[SO], &data->textures.south.w,
			&data->textures.south.h);
	if (!data->textures.south.img)
		return (1);
	data->textures.south.addr = mlx_get_data_addr(data->textures.south.img,
			&data->textures.south.bpp, &data->textures.south.line,
			&data->textures.south.endian);
	ret = load_east_and_west_textures(data);
	return (ret);
}


int  init_data(t_data *data)
{
    data ->mlx = mlx_init() ;
    if(data->mlx == NULL)
    return 1 ;
    data ->win = mlx_new_window(data->mlx,1900,1000,"CUB3D") ;
    if(data->win ==NULL)
    return 1 ;
    init_img(data) ;
	load_all_textures(data) ;

    return 0;   
}