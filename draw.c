
#include "cub3d.h"


int	update_map(t_data *data)
{
	if (data->map.redraw)
	{
		if (data->rays)
			draw_map(data);
		data->map.redraw = 0;
	}
	return (0);
}

int	draw_map(t_data *data)
{
	//draw_mapp(data) ;
	cast_rays(data);
	mini_map(data) ;
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
	return (0);
}

int	draw_ray(t_data *data, int x)
{
	double	wall_h;

	data->rays[x].distance *= cos(normalize_angle(data->rays[x].ray_angle
				- data->player.angle)) + 0.1;
	data->rays[x].wall_h = ((1 / data->rays[x].distance) * data->screen.height
			* 13.0);
	wall_h = fmin(data->rays[x].wall_h, data->screen.height);
	data->rays[x].bottom_y = floor((data->screen.height / 2) + (wall_h / 2));
	data->rays[x].r_bottom_y = floor((data->screen.height / 2)
			+ (data->rays[x].wall_h / 2));
	data->rays[x].top_y = floor((data->screen.height / 2) - (wall_h / 2));
	data->rays[x].r_top_y = floor((data->screen.height / 2)
			- (data->rays[x].wall_h / 2));
	if (data->rays[x].bottom_y > data->screen.height)
		data->rays[x].bottom_y = data->screen.height;
	if (data->rays[x].top_y < 0)
		data->rays[x].top_y = 0;
   draw_column(data, x);
	return (0);
}


int	draw_column(t_data *data, int x)
{
	int	y;

	y = -1;
	while (++y <= data->rays[x].top_y)
		put_color_to_pixel(data, x, y, data->textures.ceil_color);
	while (y <= data->rays[x].bottom_y)
		put_pixel_to_pixel(data, get_img(data, x), x, y++);
	while (y < data->screen.height)
		put_color_to_pixel(data, x, y++, data->textures.floor_color);
	return (0);
}

int	put_color_to_pixel(t_data *data, int x, int y, int col)
{
	
	unsigned int	*pixel;
	pixel = (unsigned int *)(data->img.addr + (y * data->img.line + x
				* (data->img.bpp / 8)));
	*pixel = col;
	return (0);
}

int	put_pixel_to_pixel(t_data *data, t_img *img, int x, int y)
{
	unsigned int	*dest_pixel;
	unsigned int	*src_pixel;
	int				offset_x;
	int				offset_y;

	if (data->rays[x].hit_vertical)
		offset_x = (int)((data->rays[x].hit_y / data->screen.size) * img->w)
			% img->w;
	else
		offset_x = (int)((data->rays[x].hit_x / data->screen.size) * img->w)
			% img->w;
	offset_y = ((y - data->rays[x].r_top_y) * img->h) / data->rays[x].wall_h;
	offset_y = offset_y % img->h;
	dest_pixel = (unsigned int *)(data->img.addr + (y * data->img.line + x
				* (data->img.bpp / 8)));
	src_pixel = (unsigned int *)(img->addr + (offset_y * img->line
				+ offset_x * (img->bpp / 8)));
	*dest_pixel = *src_pixel;
	return (0);
}


t_img	*get_img(t_data *data, int i)
{
	t_img	*img;

	if (data->rays[i].hit_vertical)
	{
		if (data->rays[i].is_facing_right)
			img = &data->textures.west;
		else
			img = &data->textures.east;
	}
	else
	{
		if (data->rays[i].is_facing_up)
			img = &data->textures.south;
		else
			img = &data->textures.north;
	}
	return (img);
}


int pixel_inside_map(t_data *data, double x, double y)
{
    int i;
    int j;

    if (x < 0 || y < 0)
        return (0);
    j = (int)(x / data->screen.size);
    i = (int)(y / data->screen.size);
    if (i < 0 || i >= data->map.height)
        return (0);
    if (j < 0 || j >= data->map.width)
        return (0);
    return (1);
}



int	ft_strlen(const char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}
