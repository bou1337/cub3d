#include "cub3d.h"

t_intr	find_horizontal_wall_intersection(t_data *data, int i)
{
	t_intr	h_inter;
	t_incr			incr;
	int				pixel;

	incr.y = 8;
	incr.x = incr.y / tan(data->rays[i].ray_angle);
	if (data->rays[i].is_facing_up)
		incr.y *= -1;
	if ((data->rays[i].is_facing_right && incr.x < 0)
		|| (!data->rays[i].is_facing_right && incr.x > 0))
		incr.x *= -1;
	h_inter.y = floor(data->player.pos_y /8)
		*8;
	pixel = inter_check(data, i, &h_inter.y, 1);
	h_inter.x = data->player.pos_x + ((h_inter.y - data->player.pos_y)
			/ tan(data->rays[i].ray_angle));
	while (player_inside_map(data, h_inter.x, h_inter.y + pixel))
	{
		h_inter.x += incr.x;
		h_inter.y += incr.y;
	}
	h_inter.distance = get_distance_between(data->player.pos_x,
			data->player.pos_y, h_inter.x, h_inter.y);
	return (h_inter);
}

t_intr	find_vertical_wall_intersection(t_data *data, int i) 
{
    t_intr	h_inter;
	t_incr			incr;
	int				pixel;

	incr.y = 8;
	incr.x = incr.y / tan(data->rays[i].ray_angle);
	if (data->rays[i].is_facing_up)
		incr.y *= -1;
	if ((data->rays[i].is_facing_right && incr.x < 0)
		|| (!data->rays[i].is_facing_right && incr.x > 0))
		incr.x *= -1;
	h_inter.y = floor(data->player.pos_y /8)
		* 8;
	pixel = inter_check(data, i, &h_inter.y, 1);
	h_inter.x = data->player.pos_x + ((h_inter.y - data->player.pos_y)
			/ tan(data->rays[i].ray_angle));
	while (player_inside_map(data, h_inter.x, h_inter.y + pixel))
	{
		h_inter.x += incr.x;
		h_inter.y += incr.y;
	}
	h_inter.distance = get_distance_between(data->player.pos_x,
			data->player.pos_y, h_inter.x, h_inter.y);
	return (h_inter);
}




int	inter_check(t_data *data, int idx, double *inter, int is_horizon)
{
	if (is_horizon)
	{
		if (!data->rays[idx].is_facing_up)
		{
			*inter += 8;
			return (1);
		}
	}
	else
	{
		if (data->rays[idx].is_facing_right)
		{
			*inter += 8;
			return (1);
		}
	}
	return (-1);
}

int	pixel_in_screen(t_data *data, double x, double y)
{
	if (x < 0 || y < 0)
		return (0);
	if (x > 1900 || y > 1000)
		return (0);
	return (1);
}

int	player_inside_map(t_data *data, double player_x, double player_y)
{
	int	i;
	int	j;

	if (!pixel_inside_map(data, player_x, player_y))
		return (0);
	i = (int)(player_y /8);
	j = (int)(player_x /8);
	return (data->map.map[i][j] != '1');
}


double	get_distance_between(double x1, double y1, double x2, double y2)
{
	double	distance;

	distance = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
	return (distance);
}