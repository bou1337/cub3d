
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
    if (load_texture(data->mlx, &data->textures.north, data->textures_path[0])) 
        return (1);

    if (load_texture(data->mlx, &data->textures.south, data->textures_path[1]))
    {
        free_texture(data->mlx, &data->textures.north);
        return (1);
    }

    if (load_texture(data->mlx, &data->textures.east, data->textures_path[2])) 
    {
        free_texture(data->mlx, &data->textures.north);
        free_texture(data->mlx, &data->textures.south);
        return (1);
    }

    if (load_texture(data->mlx, &data->textures.west, data->textures_path[3]))
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

void Set_player_movement_state(t_data *data)
{
      data->player.move_forward = 0;  
            data->player.move_right = 0;
            data->player.turn_right = 0;    
            data->screen.height = 1000;
	        data->screen.width = 1900;
	        data->screen.size = 8;
            data->player.move_forward = 0;
	        data->player.move_right = 0;
	        data->player.turn_right = 0;
	        data->player.fov = M_PI/6;
	        data->player.move_speed = 1;
	        data->player.turn_speed = 1.4;
	        data->player.pos_x *= data->screen.size;
	        data->player.pos_y *= data->screen.size;
}

int  init_data(t_data *data)
{
    data ->mlx = mlx_init() ;
    if(data->mlx == NULL)
    return 1 ;
    data ->win = mlx_new_window(data->mlx,1900,1000,"CUB3D") ;
    if(data->win ==NULL)
    return 1 ;
    if(init_img(data))
    return 1 ; 
	if(load_all_textures(data)) 
    return 1 ;
    Set_player_movement_state(data) ;
    return 0;   
}

int alloc_data(t_data **data)
{
    *data = malloc(sizeof(t_data));
    if (!*data)
    {
        fprintf(stderr, "Error: Failed to allocate memory for t_data\n");
        return (1);
    }

    (*data)->rays = malloc(sizeof(t_ray) * 1900);
    if (!(*data)->rays)
    {
        fprintf(stderr, "Error: Failed to allocate memory for rays\n");
        free(*data);
        *data = NULL;
        return (1);
    }
    return (0);
}

int parsing_data(int argc, char *argv[], t_data **data)
{
    int     fd;
    char    **map;

    if (alloc_data(data) || inite_data(*data))
        return (1);
    if (!validate_args(argc, argv, &fd))
        return (1);
    map = read_cub_file(fd, *data, argv[1]);
    close(fd);
    if (map == NULL)
        return (1);
    (*data)->map.map = map;
    if (!check_config_data(*data) || !check_for_borders(map))
    {
        fprintf(stderr, "Invalid map format\n");
        cleanup(*data, map);
        return (1);
    }
    set_player_data(*data);
    map_size(*data);
    if (init_data(*data))
            return (1);
    return (0);
}
