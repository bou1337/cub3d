#include "cub3d.h"

int cast_rays(t_data *data)
{
    double	angle;
	int		i;

	angle = data->player.angle - (0.5 * data->player.fov);
	i = -1;
	
	while (data->rays && ++i < data->screen.width)
	{
		angle = normalize_angle(angle);
		data->rays[i].ray_angle = angle;
		data->rays[i].is_facing_up = angle >= PI;
		data->rays[i].is_facing_right = angle < (0.5 * PI) || angle > (1.5
				* PI);
		determine_ray_intersection(data, i);
		//draw_line(data ,data->player.pos_x,data->player.pos_y,data->rays[i].hit_x,data->rays[i].hit_y) ;
		draw_ray(data, i);
		angle += data->player.fov / data->screen.width;
	}
	return (0);
}


int	determine_ray_intersection(t_data *data, int i)
{
	t_intr	h;
	t_intr	v;

	h = find_horizontal_wall_intersection(data, i);
	v = find_vertical_wall_intersection(data, i) ;
	if (h.distance < v.distance)
	{
		data->rays[i].distance = h.distance;
		data->rays[i].hit_x = h.x;
		data->rays[i].hit_y = h.y;
		data->rays[i].hit_vertical = 0;
	}
	else
	{
		data->rays[i].distance = v.distance;
		data->rays[i].hit_x = v.x;
		data->rays[i].hit_y = v.y;
		data->rays[i].hit_vertical = 1;
	}
	return (0);
}

