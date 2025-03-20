
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
static int load_texture(void *mlx, t_img *texture, char *path)
{
    texture->img = mlx_xpm_file_to_image(mlx, path, &texture->w, &texture->h);
    if (!texture->img)
    {
        fprintf(stderr, "Error: Failed to load texture %s\n", path);
        return (1);
    }
    texture->addr = mlx_get_data_addr(texture->img, &texture->bpp, &texture->line, &texture->endian);
    return (0);
}

static void free_texture(void *mlx, t_img *texture)
{
    if (texture->img)
        mlx_destroy_image(mlx, texture->img);
}

int load_all_textures(t_data *data)
{
    if (load_texture(data->mlx, &data->textures.north, data->textures_path[0])) // NO
        return (1);

    if (load_texture(data->mlx, &data->textures.south, data->textures_path[1])) // SO
    {
        free_texture(data->mlx, &data->textures.north);
        return (1);
    }

    if (load_texture(data->mlx, &data->textures.east, data->textures_path[2])) // EA
    {
        free_texture(data->mlx, &data->textures.north);
        free_texture(data->mlx, &data->textures.south);
        return (1);
    }

    if (load_texture(data->mlx, &data->textures.west, data->textures_path[3])) // WE
    {
        free_texture(data->mlx, &data->textures.north);
        free_texture(data->mlx, &data->textures.south);
        free_texture(data->mlx, &data->textures.east);
        return (1);
    }

    return (0);
}

void free_all_textures(t_data *data)
{
    free_texture(data->mlx, &data->textures.north);
    free_texture(data->mlx, &data->textures.south);
    free_texture(data->mlx, &data->textures.east);
    free_texture(data->mlx, &data->textures.west);
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